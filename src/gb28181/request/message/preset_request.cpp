#include "preset_request.h"

namespace GB28181 {

const std::string PresetRequest::make_manscdp_body() {
    std::stringstream manscdp;
    std::string       deviceID;

    if (m_channelId.empty()) {
        deviceID = get_device()->getDeviceId();
    } else {
        deviceID = m_channelId;
    }

    manscdp << "<?xml version=\"1.0\"?>\r\n"
            << "<Query>\r\n"
            << "<CmdType>PresetQuery</CmdType>\r\n"
            << "<SN>" << get_reqsn() << "</SN>\r\n"
            << "<DeviceID>" << deviceID << "</DeviceID>\r\n"
            << "</Query>\r\n";

    return manscdp.str();
}

}  // namespace GB28181