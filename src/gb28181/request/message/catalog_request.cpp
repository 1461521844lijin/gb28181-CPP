#include "catalog_request.h"

#include <sstream>

namespace GB28181 {

const std::string &CatalogRequest::make_manscdp_body() {
    std::stringstream manscdp;
    manscdp << "<?xml version=\"1.0\"?>\r\n"
            << "<Query>\r\n"
            << "<CmdType>Catalog</CmdType>\r\n"
            << "<SN>" << get_reqsn() << "</SN>\r\n"
            << "<DeviceID>" << get_device()->getDeviceId() << "</DeviceID>\r\n"
            << "</Query>\r\n";

    return manscdp.str();
}

}  // namespace GB28181
