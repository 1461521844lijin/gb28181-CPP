#include "homeposition_request.h"


namespace GB28181 {


const std::string HomePositionRequest::make_manscdp_body(){

    std::stringstream manscdp;
    manscdp << "<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n";
    manscdp << "<Control>\r\n";
    manscdp << "<CmdType>DeviceControl</CmdType>\r\n";
    manscdp << "<SN>" << get_reqsn() << "</SN>\r\n";
    manscdp << "<DeviceID>" << m_channelId << "</DeviceID>\r\n";
    manscdp << "<HomePosition>\r\n";
    manscdp << "<Enabled>" << m_enable << "</Enabled>\r\n";
    manscdp << "<PresetIndex>" << m_presetIndex << "</PresetIndex>\r\n";
    manscdp << "<ResetTime>" << m_resetTime << "</ResetTime>\r\n";
    manscdp << "</HomePosition>\r\n";
    manscdp << "</Control>\r\n";

    return manscdp.str();
}


}