// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_THIRD_PARTY_ACCOUNT_LOGIN_DEFINE_H
#define RAIL_THIRD_PARTY_ACCOUNT_LOGIN_DEFINE_H

#include "rail/sdk/rail_player_define.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

struct RailThirdPartyAccountInfo {
    RailThirdPartyAccountInfo() {
        error_code = 0;
        token_expire_time = 0;
        real_name_auth = false;
    }

    uint32_t error_code;
    RailString error_msg;
    RailString open_id;
    RailString token;
    uint32_t token_expire_time;  // UTC time
    RailString channel;
    RailString pf;
    RailString user_name;
    bool real_name_auth;
};

struct RailThirdPartyAccountLoginOptions {
    RailThirdPartyAccountLoginOptions() {
        account_type = kRailPlayerAccountUnknow;
    }

    RailPlayerAccountType account_type;
    RailString code;
};

namespace rail_event {

struct RailThirdPartyAccountLoginResult
    : public RailEvent<kRailThirdPartyAccountLoginResult> {
    RailThirdPartyAccountLoginResult() {
    }

    RailThirdPartyAccountInfo account_info;
};

struct RailNotifyThirdPartyAccountQrCodeInfo
    : public RailEvent<kRailThirdPartyAccountLoginNotifyQrCodeInfo> {
    RailNotifyThirdPartyAccountQrCodeInfo() {
    }

    RailString qr_code_url;
};

}  // namespace rail_event

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_THIRD_PARTY_ACCOUNT_LOGIN_DEFINE_H
