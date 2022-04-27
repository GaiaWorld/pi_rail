// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_IME_HELPER_DEFINE_H
#define RAIL_SDK_RAIL_IME_HELPER_DEFINE_H

#include "rail/sdk/rail_event.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

// deprecated
struct RailWindowPosition {
    RailWindowPosition() {
        position_left = 0;
        position_top = 0;
    }
    uint32_t position_left;  // x position relative to foreground window left
    uint32_t position_top;   // y position relative to foreground window top
};

// deprecated
struct RailTextInputImeWindowOption {
    RailTextInputImeWindowOption() {
        show_rail_ime_window = true;
    }
    RailWindowPosition position;
    bool show_rail_ime_window;
};

// deprecated
enum RailIMETextInputCompositionState {
    kTextInputCompositionStateNone = 0,
    kTextInputCompositionStateStart = 1,
    kTextInputCompositionStateUpdate = 2,
    kTextInputCompositionStateEnd = 3,
};

namespace rail_event {

// deprecated
struct RailIMEHelperTextInputCompositionState
    : public RailEvent<kRailEventIMEHelperTextInputCompositionStateChanged> {
    RailIMEHelperTextInputCompositionState() {
        result = kSuccess;
        composition_text = "";
        composition_state = kTextInputCompositionStateNone;
    }

    RailString composition_text;
    RailIMETextInputCompositionState composition_state;
};

// deprecated
struct RailIMEHelperTextInputSelectedResult
    : public RailEvent<kRailEventIMEHelperTextInputSelectedResult> {
    RailIMEHelperTextInputSelectedResult() {
        result = kFailure;
        user_data = "";
    }

    RailString content;
};

}  // namespace rail_event

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_IME_HELPER_DEFINE_H
