#include "catalog_handler.h"
#include "gb28181/device_client/channel.h"
#include "gb28181/device_client/deviceManager.h"
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
        /* 

        while (item != nullptr) {
            std::string channelID    = item->FirstChildElement("DeviceID")->GetText();
            std::string name         = item->FirstChildElement("Name")->GetText();
            std::string manufacturer = item->FirstChildElement("Manufacturer")->GetText();
            std::string model        = item->FirstChildElement("Model")->GetText();
            std::string owner        = item->FirstChildElement("Owner")->GetText();
            std::string civilCode    = item->FirstChildElement("CivilCode")->GetText();
            std::string address      = item->FirstChildElement("Address")->GetText();
            std::string parental     = item->FirstChildElement("Parental")->GetText();
            std::string parentID     = item->FirstChildElement("ParentID")->GetText();
            std::string registerWay  = item->FirstChildElement("RegisterWay")->GetText();
            std::string secrecy      = item->FirstChildElement("Secrecy")->GetText();
            std::string streamNum    = item->FirstChildElement("StreamNum")->GetText();
            std::string iPAddress    = item->FirstChildElement("IPAddress")->GetText();
            std::string status       = item->FirstChildElement("Status")->GetText();

            auto        info          = item->FirstChildElement("Info");
            std::string pTZType       = info->FirstChildElement("PTZType")->GetText();
            std::string downloadSpeed = info->FirstChildElement("DownloadSpeed")->GetText();

            // channel->setChannelId(item->FirstChildElement("DeviceID")->GetText());
            channel->setChannelId(channelID);
            channel->setName(name);
            channel->setManufacturer(manufacturer);
            channel->setModel(model);
            channel->setOwner(owner);
            channel->setCivilCode(civilCode);
            channel->setAddress(address);
            channel->setParental(parental);
            channel->setParentId(parentID);
            channel->setRegisterWay(registerWay);
            channel->setSecrety(secrecy);
            channel->setStreamNum(streamNum);
            channel->setIpAddress(iPAddress);
            channel->setStatus(status);
            channel->setPtztype(pTZType);
            channel->setDownSpeed(downloadSpeed);

            LOG(INFO) << channel->toString();

            auto device = g_deviceMgr::GetInstance()->getDevice(deviceID);
            if (!device->insertSubChannel(parentID, channelID, channel)) {
                LOG(ERROR) << "CatalogHandler::handle insertSubChannel failed "
                           << "channelId:" << channelID << " parentID:" << parentID
                           << " deviceID:" << deviceID;
            };

            item = item->NextSiblingElement("Item");
        }


        */
    } catch (const std::exception &e) { LOG(ERROR) << e.what() << '\n'; }

    return sendSimplyResp(deviceID.c_str(), event->excontext, event->exevent->tid, SIP_OK);
}

}  // namespace GB28181