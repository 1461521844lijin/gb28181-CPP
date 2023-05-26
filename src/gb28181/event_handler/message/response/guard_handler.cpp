#include "guard_handler.h"
#include "Util/logger.h"
#include "utils/common.h"
#include "gb28181/request/requested_pool.h"
#include "gb28181/request/message/preset_request.h"


namespace GB28181
{

int GuardHandler::handle(SipEvent::ptr event, tinxml_doc_ptr& xml){
    // 打印xml
    // xml.Print();




    return 0;
}





}