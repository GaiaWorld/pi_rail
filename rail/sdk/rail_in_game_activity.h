// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_IN_GAME_ACTIVITY_H
#define RAIL_SDK_RAIL_IN_GAME_ACTIVITY_H

#include "rail/sdk/rail_in_game_activity_define.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

class IRailInGameActivityHelper {
  public:
    virtual RailResult AsyncQueryGameActivity(const RailString& user_data) = 0;

    virtual RailResult AsyncOpenDefaultGameActivityWindow(const RailString& user_data) = 0;

    virtual RailResult AsyncOpenGameActivityWindow(uint64_t activity_id,
                        const RailString& user_data) = 0;
};

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_IN_GAME_ACTIVITY_H
