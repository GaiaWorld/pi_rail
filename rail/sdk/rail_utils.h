// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_UTILS_H
#define RAIL_SDK_RAIL_UTILS_H

#include "rail/sdk/base/rail_define.h"
#include "rail/sdk/rail_utils_define.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

class IRailUtils {
  public:
    // deprecated
    virtual uint32_t GetTimeCountSinceGameLaunch() = 0;

    // deprecated
    virtual uint32_t GetTimeCountSinceComputerLaunch() = 0;

    // @desc Get Rail server time calculated as the number of seconds since Jan 1, 1970
    // @return The number of seconds elapsed since Jan 1, 1970
    virtual uint32_t GetTimeFromServer() = 0;

    // deprecated
    virtual RailResult AsyncGetImageData(const RailString& image_path,
                        uint32_t scale_to_width,   // 0 for no scale
                        uint32_t scale_to_height,  // 0 for no scale
                        const RailString& user_data) = 0;

    // deprecated
    virtual void GetErrorString(RailResult result, RailString* error_string) = 0;

    // @desc Filter out sensitive words for a string
    // The max length for 'words' is kRailCommonUtilsCheckDirtyWordsStringMaxLength
    // @param words The string to filter out sensitive words
    // @param replace_sensitive If true '*' will be used to replace sensitive words
    // @param check_result The result string after filtering
    // @return Returns kSuccess on success
    virtual RailResult DirtyWordsFilter(const RailString& words,
                        bool replace_sensitive,
                        RailDirtyWordsCheckResult* check_result) = 0;

    // deprecated
    virtual EnumRailPlatformType GetRailPlatformType() = 0;

    virtual RailResult GetLaunchAppParameters(EnumRailLaunchAppType app_type,
                        RailString* parameter) = 0;

    // @desc Return the language code of WeGame client. You can call
    // IRailGame::GetPlayerSelectedLanguageCode interface instead. This will be more proper.
    virtual RailResult GetPlatformLanguageCode(RailString* language_code) = 0;

    // deprecated
    virtual RailResult RegisterCrashCallback(
                        const RailUtilsCrashCallbackFunction callback_func) = 0;

    // deprecated
    virtual RailResult UnRegisterCrashCallback() = 0;

    // deprecated
    virtual RailResult SetWarningMessageCallback(RailWarningMessageCallbackFunction callback) = 0;

    // deprecated
    virtual RailResult GetCountryCodeOfCurrentLoggedInIP(RailString* country_code) = 0;
};

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_UTILS_H
