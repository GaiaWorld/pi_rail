// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_ZONE_SERVER_DEFINE_H
#define RAIL_SDK_RAIL_ZONE_SERVER_DEFINE_H

#include "rail/sdk/base/rail_define.h"
#include "rail/sdk/rail_event.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

namespace rail_event {

struct RailSwitchPlayerSelectedZoneResult :
    public RailEvent<kRailEventZoneServerSwitchPlayerSelectedZoneResult> {
    RailSwitchPlayerSelectedZoneResult() {
        result = kFailure;
    }
};

}  // namespace rail_event

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_ZONE_SERVER_DEFINE_H
