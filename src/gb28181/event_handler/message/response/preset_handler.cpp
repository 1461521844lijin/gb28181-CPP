#include "preset_handler.h"

#include "glog/logging.h"
#include "utils/common.h"
#include "gb28181/request/requested_pool.h"
#include "gb28181/request/message/preset_request.h"


namespace GB28181
{

/*
<?xml version="1.0" encoding="GB2312" standalone="yes" ?>
<Response>
    <CmdType>PresetQuery</CmdType>
    <SN>2</SN>
    <DeviceID>62000000001320000002</DeviceID>
    <SumNum>2</SumNum>
    <PresetList  Num="2">
        <Item>
            <PresetID>1</PresetID>
            <PresetName>preset1</PresetName>
        </Item>
        <Item>
            <PresetID>2</PresetID>
            <PresetName>Ԥ�õ�2</PresetName>
        </Item>
    </PresetList>
</Response>
*/
int PresetQuireHandler::handle(SipEvent::ptr event, tinyxml2::XMLDocument& xml){

    


    // TODO 判断编码格式
    tinyxml2::XMLElement *root = xml.RootElement();
    std::string device_id = root->FirstChildElement("DeviceID")->GetText();
    std::string sn = root->FirstChildElement("SN")->GetText();
    
    auto req = g_RequestedPool::GetInstance()->GetMsgRequestBySn(sn);
    if(req == nullptr){
        LOG(ERROR) << "PresetQuireHandler::handle can not find request by sn:" << sn;
        return sendSimplyResp(device_id.c_str(), event->excontext, event->exevent->tid, SIP_INTERNAL_SERVER_ERROR);
    }
    // 转换子类
    auto preset_req = std::dynamic_pointer_cast<PresetRequest>(req);
    
    
    int sum_num = atoi(root->FirstChildElement("SumNum")->GetText());
    tinyxml2::XMLElement *preset_list = root->FirstChildElement("PresetList");
    int num = atoi(preset_list->Attribute("Num"));
    LOG(INFO) << "DeviceID:" << device_id << " SumNum:" << sum_num << " Num:" << num;
    tinyxml2::XMLElement *item = preset_list->FirstChildElement("Item");
    while (item != nullptr)
    {
        std::string preset_id = item->FirstChildElement("PresetID")->GetText();
        std::string gb2312_preset_name = item->FirstChildElement("PresetName")->GetText();
        std::string utf8_preset_name = character_gb28181_to_utf8(gb2312_preset_name.data(), gb2312_preset_name.length());
        LOG(INFO) << "PresetID:" << preset_id << " PresetName:" << utf8_preset_name;
        preset_req->insert_preset(preset_id, utf8_preset_name);
        item = item->NextSiblingElement("Item");
    }


    preset_req->onRequestFinished();    

    return sendSimplyResp(device_id.c_str(), event->excontext, event->exevent->tid, SIP_OK);

}









    
} // namespace GB28181













