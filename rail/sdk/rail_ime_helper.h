// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_IME_HELPER_H
#define RAIL_SDK_RAIL_IME_HELPER_H

#include "rail/sdk/rail_ime_helper_define.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

// deprecated. This API will be removed in the future version.
class IRailIMEHelper {
  public:
    virtual RailResult EnableIMEHelperTextInputWindow(bool enable,
                        const RailTextInputImeWindowOption& option) = 0;

    virtual RailResult UpdateIMEHelperTextInputWindowPosition(
                        const RailWindowPosition& position) = 0;
};

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_IME_HELPER_H
