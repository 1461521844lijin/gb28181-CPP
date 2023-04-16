#include "ptzcontrol_request.h"

#include <gb28181/ptz/ptz_cmd.h>

namespace GB28181 {

const std::string PtzControlRequest::make_manscdp_body() {
    std::string ptzCmd =
        PtzCmd::cmdString(m_leftRight, m_upDown, m_inOut, m_moveSpeed, m_zoomSpeed);
    std::stringstream manscdp;
    manscdp << "<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n";
    manscdp << "<Control>\r\n";
    manscdp << "<CmdType>DeviceControl</CmdType>\r\n";
    manscdp << "<SN>" << get_reqsn() << "</SN>\r\n";
    manscdp << "<DeviceID>" << m_channelId << "</DeviceID>\r\n";
    manscdp << "<PTZCmd>" << ptzCmd << "</PTZCmd>\r\n";
    manscdp << "</Control>\r\n";
    return manscdp.str();
}

}  // namespace GB28181
