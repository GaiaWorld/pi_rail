// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_THIRD_PARTY_ACCOUNT_LOGIN_H
#define RAIL_THIRD_PARTY_ACCOUNT_LOGIN_H

#include "rail/sdk/rail_third_party_account_login_define.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

class IRailThirdPartyAccountLoginHelper {
  public:
    virtual RailResult AsyncAutoLogin(const RailString& user_data) = 0;

    virtual RailResult AsyncLogin(const RailThirdPartyAccountLoginOptions& options,
                        const RailString& user_data) = 0;

    virtual RailResult GetAccountInfo(RailThirdPartyAccountInfo* account_info) = 0;
};

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_THIRD_PARTY_ACCOUNT_LOGIN_H
