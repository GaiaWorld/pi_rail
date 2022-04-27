// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_PLAYER_H
#define RAIL_SDK_RAIL_PLAYER_H

#include "rail/sdk/rail_player_define.h"

namespace rail {

#pragma pack(push, RAIL_SDK_PACKING)

class IRailPlayer {
  public:
    // deprecated
    virtual bool AlreadyLoggedIn() = 0;

    virtual const RailID GetRailID() = 0;

    virtual RailResult GetPlayerDataPath(RailString* path) = 0;

    // trigger event AcquireSessionTicketResponse
    virtual RailResult AsyncAcquireSessionTicket(const RailString& user_data) = 0;

    // trigger event StartAuthSessionTicketResponse
    virtual RailResult AsyncStartSessionWithPlayer(const RailSessionTicket& player_ticket,
                        RailID player_rail_id,
                        const RailString& user_data) = 0;

    virtual void TerminateSessionOfPlayer(RailID player_rail_id) = 0;

    virtual void AbandonSessionTicket(const RailSessionTicket& session_ticket) = 0;

    virtual RailResult GetPlayerName(RailString* name) = 0;

    virtual EnumRailPlayerOwnershipType GetPlayerOwnershipType() = 0;

    // request get purchase key(such as cdkey) of yourself
    // event name: kRailEventPlayerGetGamePurchaseKey with data PlayerGetGamePurchaseKeyResult
    virtual RailResult AsyncGetGamePurchaseKey(const RailString& user_data) = 0;

    // deprecated
    // as the new anti-addiction rules no longer require reducing player's game revenue,
    // the IsGameRevenueLimited and GetRateOfGameRevenue interfaces no need to be used.
    // The IsGameRevenueLimited interface will always return false.
    virtual bool IsGameRevenueLimited() = 0;

    // deprecated
    // the GetRateOfGameRevenue interface will always return 1.0.
    virtual float GetRateOfGameRevenue() = 0;

    // query current player's banned status for anti cheat
    virtual RailResult AsyncQueryPlayerBannedStatus(const RailString& user_data) = 0;

    // get an authenticate URL for the specified URL.
    // Callback is GetAuthenticateURLResult.
    virtual RailResult AsyncGetAuthenticateURL(const RailGetAuthenticateURLOptions& options,
                        const RailString& user_data) = 0;

    // Callback is RailGetPlayerMetadataResult.
    virtual RailResult AsyncGetPlayerMetadata(const RailArray<RailString>& keys,
                        const RailString& user_data) = 0;

    // callback is RailGetEncryptedGameTicketResult
    virtual RailResult AsyncGetEncryptedGameTicket(const RailString& set_metadata,
                        const RailString& user_data) = 0;

    virtual RailPlayerAccountType GetPlayerAccountType() = 0;
};

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_PLAYER_H
