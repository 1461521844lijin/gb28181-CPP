#pragma once
#include "application/dto/StatusDto.hpp"

namespace OP
{

// 参数	是否必选	释意
// secret	Y	api操作密钥(配置文件配置)，如果操作ip是127.0.0.1，则不需要此参数
// vhost	Y	流的虚拟主机名
// app	Y	流的应用名
// stream	Y	流的ID
// period	Y	流的录像日期，格式为2020-02-01,如果不是完整的日期，那么是搜索录像文件夹列表，否则搜索对应日期下的mp4文件列表

// 搜索录制文件列表
oatpp::Object<StatusDto> getMp4RecordFile(const std::string &  streamid, const std::string &  period);

// 开始录制
oatpp::Object<StatusDto> startRecord(const std::string &  streamid);

// 停止录制
oatpp::Object<StatusDto> stopRecord(const std::string &  streamid);

// 获取录制状态
oatpp::Object<StatusDto> getRecordStatus(const std::string &  streamid);

// 获取实时截图并返回
oatpp::Object<StatusDto> getSnapShot(const std::string &  streamid);



}