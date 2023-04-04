#include "preset_ctl_request.h"
#include <gb28181/ptz/ptz_cmd.h>
namespace GB28181
{

const std::string PresetCtlRequest::make_manscdp_body(){

    std::string ptzCmd =
    PtzCmd::cmdCode(m_byte4, m_byte5, m_byte6, m_byte7);
    std::stringstream manscdp;
    manscdp << "<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n";
    manscdp << "<Control>\r\n";
    manscdp << "<CmdType>DeviceControl</CmdType>\r\n";
    manscdp << "<SN>" << get_reqsn() << "</SN>\r\n";
    manscdp << "<DeviceID>" << get_device()->getDeviceId() << "</DeviceID>\r\n";
    manscdp << "<PTZCmd>" << ptzCmd << "</PTZCmd>\r\n";
    manscdp << "<Info>\r\n";
    manscdp << "<ControlPriority>5</ControlPriority>\r\n";
    manscdp << "</Info>\r\n";
    manscdp << "</Control>\r\n";
    return manscdp.str();

}













}