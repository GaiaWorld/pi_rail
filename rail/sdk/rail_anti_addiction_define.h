// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_ANTI_ADDICTION_DEFINE_H
#define RAIL_SDK_RAIL_ANTI_ADDICTION_DEFINE_H

#include "rail/sdk/base/rail_define.h"
#include "rail/sdk/rail_event.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

enum RailAntiAddictionActionType {
    kRailAntiAddictionActionUnknow = 0,
    kRailAntiAddictionActionShowTips = 1,
    kRailAntiAddictionActionHalt = 2,
};

namespace rail_event {

struct RailQueryGameOnlineTimeResult :
    public RailEvent<kRailEventAntiAddictionQueryGameOnlineTimeResult> {
    RailQueryGameOnlineTimeResult() {
        game_online_time_seconds = 0;
    }

    uint32_t game_online_time_seconds;  // game on-line time of the day.
};

struct RailCustomizeAntiAddictionActions :
    public RailEvent<kRailEventAntiAddictionCustomizeAntiAddictionActions> {
    RailCustomizeAntiAddictionActions() {
    }

    // The anti_addiction_actions parameter is a json value, the format is as follows,
    // {
    //     "actions": [
    //         {
    //             "action": {
    //                 "type": { "id": 1, "name": "kRailAntiAddictionActionShowTips" },
    //                 "title": "Notification",
    //                 "content": "According to anti-addiction system, because you are an underage
    //                            player, you can only play 1.5 hours on weekdays. You have been
    //                            playing for 1 hour today. Please take a rest.",
    //                 "display_duration_seconds": 60
    //             }
    //         },
    //         {
    //             "action": {
    //                 "type": { "id": 2, "name": "kRailAntiAddictionActionHalt" }
    //             }
    //         }
    //     ]
    // }
    //
    // The value of type parameter in action is defined in RailAntiAddictionActionType.
    // If the value of type is 1, the game client should pop up an anti addiction tips and display
    // the title and content information on the tips.
    // If the value of type is 2, the game client should exit after displaying the anti addiction
    // tips.
    RailString anti_addiction_actions;
};

}  // namespace rail_event

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_ANTI_ADDICTION_DEFINE_H
