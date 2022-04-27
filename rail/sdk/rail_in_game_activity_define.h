// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_IN_GAME_ACTIVITY_DEFINE_H
#define RAIL_SDK_RAIL_IN_GAME_ACTIVITY_DEFINE_H

#include "rail/sdk/base/rail_define.h"
#include "rail/sdk/rail_event.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

struct RailGameActivityInfo {
    RailGameActivityInfo() {
        activity_id = 0;
        begin_time = 0;
        end_time = 0;
    }

    uint64_t activity_id;
    uint32_t begin_time;  // UTC time
    uint32_t end_time;  // UTC time
    RailString activity_name;
    RailString activity_description;
    RailArray<RailKeyValue> metadata_key_values;
};

namespace rail_event {

struct RailQueryGameActivityResult :
    public RailEvent<kRailEventInGameActivityQueryGameActivityResult> {
    RailQueryGameActivityResult() {
        result = kFailure;
    }

    RailArray<RailGameActivityInfo> game_activities;
};

struct RailOpenGameActivityWindowResult :
    public RailEvent<kRailEventInGameActivityOpenGameActivityWindowResult> {
    RailOpenGameActivityWindowResult() {
        result = kFailure;
        activity_id = 0;
        is_show = false;
    }

    uint64_t activity_id;
    bool is_show;
};

struct RailNotifyNewGameActivities :
    public RailEvent<kRailEventInGameActivityNotifyNewGameActivities> {
    RailNotifyNewGameActivities() {
        result = kFailure;
    }

    RailArray<RailGameActivityInfo> game_activities;
};

struct RailGameActivityPlayerEvent :
    public RailEvent<kRailEventInGameActivityGameActivityPlayerEvent> {
    RailGameActivityPlayerEvent() {
        result = kFailure;
        from_activity_id = 0;
    }

    uint64_t from_activity_id;
    RailString event_name;
    RailString event_value;
};

}  // namespace rail_event

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_IN_GAME_ACTIVITY_DEFINE_H
