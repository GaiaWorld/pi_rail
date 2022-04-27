// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_ANTI_ADDICTION_H
#define RAIL_SDK_RAIL_ANTI_ADDICTION_H

#include "rail/sdk/rail_anti_addiction_define.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

class IRailAntiAddictionHelper {
  public:
    virtual RailResult AsyncQueryGameOnlineTime(const RailString& user_data) = 0;
};

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_ANTI_ADDICTION_H
