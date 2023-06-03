#pragma once

#include <utility>

#include "gb28181/request/base_request.h"

namespace GB28181 {

class PresetRequest : public MessageRequest {
public:
    typedef std::shared_ptr<PresetRequest> ptr;
    PresetRequest(Device::ptr device, std::string channelId)
        : MessageRequest(device), m_channelId(std::move(channelId)) {}

public:
    virtual const std::string make_manscdp_body() override;

    void insert_preset(const std::string &presetId, const std::string &presetName) {
        m_presetList.push_back(std::make_pair(presetId, presetName));
    }

    const std::vector<std::pair<std::string, std::string>> &get_preset_list() const {
        return m_presetList;
    }


private:
    std::string m_channelId = "";

    std::vector<std::pair<std::string, std::string>> m_presetList;
};

}  // namespace GB28181