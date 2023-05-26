#include "guard_request.h"
#include "Util/logger.h"
namespace GB28181 {

const std::string GuardRequest::make_manscdp_body() {
    std::stringstream manscdp;
    manscdp << "<?xml version=\"1.0\"?>\r\n"
            << "<Control>\r\n"
            << "<CmdType>DeviceControl</CmdType>\r\n"
            << "<SN>" << get_reqsn() << "</SN>\r\n"
            << "<DeviceID>" << get_device()->getDeviceId() << "</DeviceID>\r\n"
            << "<GuardCmd>" << m_guardcmd << "</GuardCmd>\r\n"
            << "</Control>\r\n";
    return manscdp.str();
}

int GuardRequest::HandleResponse(int statcode, tinxml_doc_ptr xml){

    if(statcode == -1){
        // WarnL << "超时清理";
        return -1;
    }

    tinyxml2::XMLElement *root = xml->RootElement();
    std::string           deviceID = root->FirstChildElement("DeviceID")->GetText();
    std::string    result = root->FirstChildElement("Result")->GetText();

    ErrorL << result;
    if (result == "OK"){
        // todo 对应业务逻辑
        
        
        
        onRequestFinished();
        return 0;
    }


    return -1;
}



}  // namespace GB28181