#include "register_handler.h"

extern "C" {
#include "gb28181/auth/md5/HTTPDigest.h"
}
#include "glog/logging.h"
#include <cstring>
#include <string>

#include "application/dto/configs/SipConfigDto.hpp"
#include "oatpp/core/macro/component.hpp"

#include "gb28181/device/device.h"
#include "gb28181/device/deviceManager.h"
#include "gb28181/request/message/catalog_request.h"

#include "utils/CommonTools.h"

namespace GB28181 {

int Registerhandler::HandleIncomingReq(const SipEvent::ptr &e) {
    /* Todo:
         1 检查是否已经注册过，如果已经注册过，直接返回200 OK
         2 增加注销功能逻辑
    */

    osip_authorization_t *auth = nullptr;
    auto                  evtp = e->exevent;
    osip_message_get_authorization(evtp->request, 0, &auth);

    // 暂时只实现注册的逻辑，没有实现注销的业务逻辑
    if (auth && auth->username) {
        char *method       = NULL,  // REGISTER
             *algorithm    = NULL,  // MD5
             *username     = NULL,  // 340200000013200000024
             *realm        = NULL,  // sip服务器传给客户端，客户端携带并提交上来的sip服务域
             *nonce        = NULL,  // sip服务器传给客户端，客户端携带并提交上来的nonce
             *nonce_count  = NULL,
             *uri          = NULL;  // sip:34020000002000000001@3402000000

        osip_contact_t *contact = nullptr;
        osip_message_get_contact(evtp->request, 0, &contact);

        method = evtp->request->sip_method;
        char    calc_response[HASHHEXLEN];
        HASHHEX HA1, HA2 = "", Response;

#define SIP_STRDUP(field)                                                                          \
    if (auth->field)                                                                               \
    (field) = osip_strdup_without_quote(auth->field)

        SIP_STRDUP(algorithm);
        SIP_STRDUP(username);
        SIP_STRDUP(realm);
        SIP_STRDUP(nonce);
        SIP_STRDUP(nonce_count);
        SIP_STRDUP(uri);

        OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);

        // Config::local_sip_t localsipcfg;
        // Config::ConfigManager::instance()->GetLocalSip(localsipcfg);

        std::string sippass  = sipConfig->sipPassword;
        std::string siprealm = sipConfig->sipDimain;
        std::string mnonce   = sipConfig->sipNonce;

        DigestCalcHA1(algorithm, username, realm, sippass.c_str(), nonce, nonce_count, HA1);
        DigestCalcResponse(HA1, nonce, nonce_count, auth->cnonce, auth->message_qop, 0, method, uri,
                           HA2, Response);

        HASHHEX temp_HA1;
        HASHHEX temp_response;
        DigestCalcHA1("REGISTER", username, siprealm.c_str(), sippass.c_str(), mnonce.c_str(), NULL,
                      temp_HA1);
        DigestCalcResponse(temp_HA1, mnonce.c_str(), NULL, NULL, NULL, 0, method, uri, NULL,
                           temp_response);
        memcpy(calc_response, temp_response, HASHHEXLEN);

        if (!memcmp(calc_response, Response, HASHHEXLEN)) {
            sendSimplyResp(username, e->excontext, e->exevent->tid, SIP_OK);
            // LOG(INFO) << "Camera registration succee,ip=" << contact->url->host <<", port="<< contact->url->port<<", device="<<username;
            std::string clinet_host     = strdup(contact->url->host);
            std::string clinet_port     = strdup(contact->url->port);
            std::string clinet_deviceid = username;
            LOG(INFO) << "Camera registration succee,ip=" << clinet_host <<", port="<< clinet_port<<", device="<<clinet_deviceid;
            Device::ptr device =        std::make_shared<Device>(clinet_deviceid, clinet_host, clinet_port);
            device->setStatus(1);
            device->setRegiestTime(Time2Str());

            g_deviceMgr::GetInstance()->addDevice(device);
            
            // 向客户端发送catalog请求,将设备的通道和相关信息查询出来
            std::shared_ptr<CatalogRequest> catalogRequest = std::make_shared<CatalogRequest>(device);
            catalogRequest->send_message();

            
        } else {
            sendSimplyResp(username, e->excontext, e->exevent->tid, SIP_UNAUTHORIZED);
            LOG(INFO) << "Camera registration error, p=%s,port=%d,device=%s", contact->url->host, contact->url->port, username;
            std::string clinet_deviceid = strdup(auth->username);
            g_deviceMgr::GetInstance()->removeDevice(clinet_deviceid);
        }

        osip_free(algorithm);
        osip_free(username);
        osip_free(realm);
        osip_free(nonce);
        osip_free(nonce_count);
        osip_free(uri);
    } else {
        response_register_401unauthorized(e);
    }
}

void Registerhandler::response_register_401unauthorized(const SipEvent::ptr &e) {
    char                    *dest   = nullptr;
    osip_message_t          *reg    = nullptr;
    osip_www_authenticate_t *header = nullptr;

    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);

    std::string siprealm = sipConfig->sipDimain;  // 信息需要从全局配置获取
    std::string mnonce   = sipConfig->sipNonce;

    osip_www_authenticate_init(&header);
    osip_www_authenticate_set_auth_type(header, osip_strdup("Digest"));
    osip_www_authenticate_set_realm(header, osip_enquote(siprealm.c_str()));
    osip_www_authenticate_set_nonce(header, osip_enquote(mnonce.c_str()));
    osip_www_authenticate_to_str(header, &dest);
    int ret = eXosip_message_build_answer(e->excontext, e->exevent->tid, 401, &reg);
    if (ret == 0 && reg != nullptr) {
        osip_message_set_www_authenticate(reg, dest);
        osip_message_set_content_type(reg, "Application/MANSCDP+xml");
        eXosip_lock(e->excontext);
        eXosip_message_send_answer(e->excontext, e->exevent->tid, 401, reg);
        eXosip_unlock(e->excontext);
        LOG(INFO) << "response_register_401unauthorized success";
    } else {
        LOG(INFO) << "response_register_401unauthorized error";
    }

    osip_www_authenticate_free(header);
    osip_free(dest);
}

}  // namespace GB28181
