#pragma once

#include "base_stream.h"
#include "utils/Singleton.h"
#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
namespace GB28181 {

class StreamProxy : public BaseStream {
public:
    typedef std::shared_ptr<StreamProxy> ptr;
    StreamProxy() = delete;
    StreamProxy(ZLM::ZlmServer::ptr mediaServer,
                const std::string  &app,
                const std::string  &streamId,
                STREAM_TYPE         type = STREAM_TYPE::STREAM_TYPE_PROXY);
};

class StreamPushed : public BaseStream {
public:
    typedef std::shared_ptr<StreamPushed> ptr;
    StreamPushed() = delete;
    StreamPushed(ZLM::ZlmServer::ptr mediaServer,
                 const std::string  &app,
                 const std::string  &streamId,
                 STREAM_TYPE         type = STREAM_TYPE::STREAM_TYPE_PUSH);
};

}  // namespace GB28181
