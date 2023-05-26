#include "alarm_handler.h"
#include "Util/logger.h"
#include "utils/common.h"

namespace GB28181 {

/*
<?xml version="1.0" encoding="GB2312" standalone="yes" ?>
<Notify>
    <CmdType>Alarm</CmdType>
    <SN>3</SN>
    <DeviceID>62000000001320000011</DeviceID>
    <AlarmPriority>1</AlarmPriority>
    <AlarmMethod>5</AlarmMethod>
    <AlarmTime>2023-04-27T18:01:58</AlarmTime>
    <AlarmDescription>��Ƶ����</AlarmDescription>
    <AlarmInfo>11</AlarmInfo>
    <Info>
        <AlarmType>2</AlarmType>
        <AlarmTypeParam>
            <EventType>1</EventType>
        </AlarmTypeParam>
    </Info>
</Notify>
*/

int AlarmHandler::handle(SipEvent::ptr event, tinxml_doc_ptr &xml) {
    auto        root     = xml->RootElement();
    std::string DeviceID = root->FirstChildElement("DeviceID")->GetText();

    const char *gb2312_AlarmDescription = root->FirstChildElement("AlarmDescription")->GetText();
    std::string utf8_AlarmDescription =
        character_gb28181_to_utf8((char *)gb2312_AlarmDescription, strlen(gb2312_AlarmDescription));

    WarnL<< "收到告警：" << "DeviceID:" << DeviceID << " AlarmDescription:" << utf8_AlarmDescription;
}

}  // namespace GB28181
