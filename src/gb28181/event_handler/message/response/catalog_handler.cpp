#include "catalog_handler.h"
#include "gb28181/device/channel.h"
#include "gb28181/device/deviceManager.h"
#include "glog/logging.h"

namespace GB28181 {

/*
<?xml version="1.0" encoding="GB2312" standalone="yes" ?>
<Response>
    <CmdType>Catalog</CmdType>
    <SN>1</SN>
    <DeviceID>51000000001320000001</DeviceID>
    <SumNum>1</SumNum>
    <DeviceList Num="2">
        <Item>
            <DeviceID>23000000001310000002</DeviceID>
            <Name>���ز���</Name>
            <Manufacturer>Dahua</Manufacturer>
            <Model>IPC-HFW2433M-LED-V2</Model>
            <Owner>0</Owner>
            <CivilCode>510000</CivilCode>
            <Address>axy</Address>
            <Parental>0</Parental>
            <ParentID>51000000001320000001</ParentID>
            <RegisterWay>1</RegisterWay>
            <Secrecy>0</Secrecy>
            <StreamNum>2</StreamNum>
            <IPAddress>192.168.163.170</IPAddress>
            <Status>ON</Status>
            <Info>
                <PTZType>3</PTZType>
                <DownloadSpeed>1/2/4/8</DownloadSpeed>
            </Info>
        </Item>
        <Item>
            <DeviceID>23000000001310000002</DeviceID>
            <Name>���ز���</Name>
            <Manufacturer>Dahua</Manufacturer>
            <Model>IPC-HFW2433M-LED-V2</Model>
            <Owner>0</Owner>
            <CivilCode>510000</CivilCode>
            <Address>axy</Address>
            <Parental>0</Parental>
            <ParentID>51000000001320000001</ParentID>
            <RegisterWay>1</RegisterWay>
            <Secrecy>0</Secrecy>
            <StreamNum>2</StreamNum>
            <IPAddress>192.168.163.170</IPAddress>
            <Status>ON</Status>
            <Info>
                <PTZType>3</PTZType>
                <DownloadSpeed>1/2/4/8</DownloadSpeed>
            </Info>
        </Item>
    </DeviceList>
</Response>

*/

int CatalogHandler::handle(SipEvent::ptr event, tinyxml2::XMLDocument &xml) {
    Channel::ptr channel = std::make_shared<Channel>();

    tinyxml2::XMLElement *root     = xml.RootElement();
    std::string           deviceID = root->FirstChildElement("DeviceID")->GetText();

    tinyxml2::XMLElement *deviceList = root->FirstChildElement("DeviceList");
    if (deviceList == nullptr) {
        LOG(ERROR) << "CatalogHandler::handle deviceList is null";
        return -1;
    }
    tinyxml2::XMLElement *item = deviceList->FirstChildElement("Item");
    try {
         
        while (item != nullptr) {
            if(item->FirstChildElement("DeviceID") != nullptr){
                channel->setChannelId(item->FirstChildElement("DeviceID")->GetText());
            }
            if(item->FirstChildElement("Name") != nullptr){
                channel->setName(item->FirstChildElement("Name")->GetText());
            }
            if(item->FirstChildElement("Manufacturer") != nullptr){
                channel->setManufacturer(item->FirstChildElement("Manufacturer")->GetText());
            }
            if(item->FirstChildElement("Model") != nullptr){
                channel->setModel(item->FirstChildElement("Model")->GetText());
            }
            if(item->FirstChildElement("Owner") != nullptr){
                channel->setOwner(item->FirstChildElement("Owner")->GetText());
            }
            if(item->FirstChildElement("CivilCode") != nullptr){
                channel->setCivilCode(item->FirstChildElement("CivilCode")->GetText());
            }
            if(item->FirstChildElement("Address") != nullptr){
                channel->setAddress(item->FirstChildElement("Address")->GetText());
            }
            if(item->FirstChildElement("Parental") != nullptr){
                channel->setParental(item->FirstChildElement("Parental")->GetText());
            }
            if(item->FirstChildElement("ParentID") != nullptr){
                channel->setParentId(item->FirstChildElement("ParentID")->GetText());
            }
            if(item->FirstChildElement("RegisterWay") != nullptr){
                channel->setRegisterWay(item->FirstChildElement("RegisterWay")->GetText());
            }
            if(item->FirstChildElement("Secrecy") != nullptr){
                channel->setSecrety(item->FirstChildElement("Secrecy")->GetText());
            }
            if(item->FirstChildElement("StreamNum") != nullptr){
                channel->setStreamNum(item->FirstChildElement("StreamNum")->GetText());
            }
            if(item->FirstChildElement("IPAddress") != nullptr){
                channel->setIpAddress(item->FirstChildElement("IPAddress")->GetText());
            }
            if(item->FirstChildElement("Status") != nullptr){
                channel->setStatus(item->FirstChildElement("Status")->GetText());
            }
            if(item->FirstChildElement("Info") != nullptr){
                tinyxml2::XMLElement *info = item->FirstChildElement("Info");
                if(info->FirstChildElement("PTZType") != nullptr){
                    channel->setPtztype(info->FirstChildElement("PTZType")->GetText());
                }
                if(info->FirstChildElement("DownloadSpeed") != nullptr){
                    channel->setDownSpeed(info->FirstChildElement("DownloadSpeed")->GetText());
                }
            }

            

            auto device = g_deviceMgr::GetInstance()->getDevice(deviceID);
            if (!device->insertSubChannel(deviceID, channel->getChannelId(), channel)) {
                LOG(ERROR) << "CatalogHandler::handle insertSubChannel failed "
                           << "channelId:" << channel->getChannelId() << " parentID:" << channel->getParentId()
                           << " deviceID:" << deviceID;
            }else{
                LOG(INFO) << "CatalogHandler::handle insertSubChannel success "
                           << "channelId:" << channel->getChannelId() << " parentID:" << channel->getParentId()
                           << " deviceID:" << deviceID;

            };

            item = item->NextSiblingElement("Item");
        }
    } catch (const std::exception &e) { LOG(ERROR) << e.what() << '\n'; }

    return sendSimplyResp(deviceID.c_str(), event->excontext, event->exevent->tid, SIP_OK);
}

}  // namespace GB28181