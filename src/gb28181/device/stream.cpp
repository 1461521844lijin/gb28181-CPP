#include "stream.h"

namespace GB28181 {

StreamProxy::StreamProxy(ZLM::ZlmServer::ptr mediaServer,
                         const std::string  &app,
                         const std::string  &streamId,
                         STREAM_TYPE         type)
    : BaseStream(mediaServer, app, streamId, type) {}

StreamPushed::StreamPushed(ZLM::ZlmServer::ptr mediaServer,
                           const std::string  &app,
                           const std::string  &streamId,
                           STREAM_TYPE         type)
    : BaseStream(mediaServer, app, streamId, type) {}

}  // namespace GB28181
