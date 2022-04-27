// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_GROUP_CHAT_H
#define RAIL_SDK_RAIL_GROUP_CHAT_H

#include "rail/sdk/base/rail_component.h"
#include "rail/sdk/rail_group_chat_define.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

// deprecated. This API will be removed in the future version.
class IRailGroupChat;
class IRailGroupChatHelper {
  public:
    virtual RailResult AsyncQueryGroupsInfo(const RailString& user_data) = 0;

    virtual IRailGroupChat* AsyncOpenGroupChat(const RailString& group_id,
                                const RailString& user_data) = 0;
};

// deprecated. This API will be removed in the future version.
class IRailGroupChat : public IRailComponent {
  public:
    virtual RailResult GetGroupInfo(RailGroupInfo* group_info) = 0;

    virtual RailResult OpenGroupWindow() = 0;
};

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_GROUP_CHAT_H
