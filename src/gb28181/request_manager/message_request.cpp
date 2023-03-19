/*
**	********************************************************************************
**
**	File		: message_request.cpp
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#include <glog/logging.h>
#include "message_request.h"


namespace GB28181 {

int KeepaliveRequest::HandleResponse(int statcode)
{
    LOG(INFO) << "Keepalive: "<<  m_reqid<<", statcode: " << statcode;
    m_statcode = statcode;
    onRequestFinished();

    return 0;
}

int KeepaliveRequest::GetStatCode()
{
    return m_statcode;
}

}
