// Copyright (C) 2021 Tencent. All rights reserved.

#ifndef RAIL_SDK_RAIL_USER_SPACE_H
#define RAIL_SDK_RAIL_USER_SPACE_H

#include "rail/sdk/base/rail_component.h"
#include "rail/sdk/rail_user_space_define.h"

namespace rail {
#pragma pack(push, RAIL_SDK_PACKING)

class IRailSpaceWork;
class IRailUserSpaceHelper {
  public:
    // asynchronously query spaceworks subscribed by myself.
    // If you set max_works parameter to zero, the callback event will return empty data.
    // Note, the value of max_works parameter cannot exceed kRailMaxQuerySpaceWorksLimit.
    // Callback event is AsyncGetMySubscribedWorksResult.
    virtual RailResult AsyncGetMySubscribedWorks(uint32_t offset,
                        uint32_t max_works,
                        EnumRailSpaceWorkType type,
                        const RailQueryWorkFileOptions& options = RailQueryWorkFileOptions(),
                        const RailString& user_data = "") = 0;

    // asynchronously query my favorite spaceworks.
    // If you set max_works parameter to zero, the callback event will return empty data.
    // Note, the value of max_works parameter cannot exceed kRailMaxQuerySpaceWorksLimit.
    // Callback event is AsyncGetMyFavoritesWorksResult.
    virtual RailResult AsyncGetMyFavoritesWorks(uint32_t offset,
                        uint32_t max_works,
                        EnumRailSpaceWorkType type,
                        const RailQueryWorkFileOptions& options = RailQueryWorkFileOptions(),
                        const RailString& user_data = "") = 0;

    // asynchronously query spaceworks.
    // If you set max_works parameter to zero, the callback event will return empty data.
    // Note, the value of max_works parameter cannot exceed kRailMaxQuerySpaceWorksLimit.
    // Callback event is AsyncQuerySpaceWorksResult.
    virtual RailResult AsyncQuerySpaceWorks(const RailSpaceWorkFilter& filter,
                        uint32_t offset,
                        uint32_t max_works,
                        EnumRailSpaceWorkOrderBy order_by = kRailSpaceWorkOrderByLastUpdateTime,
                        const RailQueryWorkFileOptions& options = RailQueryWorkFileOptions(),
                        const RailString& user_data = "") = 0;

    // asynchronously subscribe spaceworks.
    // Set subscribe parameter to true if you want to subscribe or false if you want to unsubscribe.
    // Callback event is AsyncSubscribeSpaceWorksResult.
    virtual RailResult AsyncSubscribeSpaceWorks(const RailArray<SpaceWorkID>& ids,
                        bool subscribe,
                        const RailString& user_data) = 0;

    // if current player is the owner of this spacework, the OpenSpaceWork interface will open the
    // spacework with read-write permission, otherwise open the spacework as read-only.
    virtual IRailSpaceWork* OpenSpaceWork(const SpaceWorkID& id) = 0;

    // create a brand new empty spacework.
    virtual IRailSpaceWork* CreateSpaceWork(EnumRailSpaceWorkType type) = 0;

    // synchronous version of AsyncGetMySubscribedWorks, only support return spacework id list.
    // This interface will block the caller's thread until it returns result.
    // Note, the value of max_works parameter cannot exceed kRailMaxQuerySpaceWorksLimit.
    virtual RailResult GetMySubscribedWorks(uint32_t offset,
                        uint32_t max_works,
                        EnumRailSpaceWorkType type,
                        QueryMySubscribedSpaceWorksResult* result) = 0;

    // synchronously get total count of my subscribed spacework.
    // This interface will block the caller's thread until it returns result.
    virtual uint32_t GetMySubscribedWorksCount(EnumRailSpaceWorkType type, RailResult* result) = 0;

    // asynchronously destroy the spacework owned by player.
    // Note, if this interface is called by other players not own the current spacework, it will
    // return an error.
    // Callback event is AsyncRemoveSpaceWorkResult.
    virtual RailResult AsyncRemoveSpaceWork(SpaceWorkID id, const RailString& user_data) = 0;

    // asynchronously add/delete my favorite spaceworks.
    // Callback event is AsyncModifyFavoritesWorksResult
    virtual RailResult AsyncModifyFavoritesWorks(const RailArray<SpaceWorkID>& ids,
                        EnumRailModifyFavoritesSpaceWorkType modify_flag,
                        const RailString& user_data) = 0;

    // deprecated, use AsyncRateSpaceWork instead
    virtual RailResult AsyncVoteSpaceWork(SpaceWorkID id,
                        EnumRailSpaceWorkVoteValue vote,
                        const RailString& user_data) = 0;

    // asynchronously search spaceworks.
    // Suggest to use kRailSpaceWorkOrderByBestMatch as default order.
    // Note, the value of max_works parameter cannot exceed kRailMaxQuerySpaceWorksLimit.
    // Callback event is AsyncSearchSpaceWorksResult
    virtual RailResult AsyncSearchSpaceWork(const RailSpaceWorkSearchFilter& filter,
                        const RailQueryWorkFileOptions& options,
                        const RailArray<EnumRailSpaceWorkType>& types,
                        uint32_t offset,
                        uint32_t max_works,
                        EnumRailSpaceWorkOrderBy order_by,
                        const RailString& user_data) = 0;

    // asynchronously rate a spacework.
    // Callback event is AsyncRateSpaceWorkResult
    virtual RailResult AsyncRateSpaceWork(const SpaceWorkID& id,
                        EnumRailSpaceWorkRateValue mark,
                        const RailString& user_data) = 0;

    // asynchronously query spaceworks information.
    // Note, the size of ids array cannot exceed kRailMaxQuerySpaceWorksLimit.
    // Callback event is AsyncQuerySpaceWorksInfoResult.
    virtual RailResult AsyncQuerySpaceWorksInfo(const RailArray<SpaceWorkID>& ids,
                        const RailString& user_data) = 0;
};

class IRailSpaceWork : public IRailComponent {
  public:
    // close this space work, all sync operation will be canceled
    // and will received SyncSpaceWorkResult if any sync had been canceled
    virtual void Close() = 0;
    // get spacework id
    // if the instance is created by CreateSpaceWork, the SpaceWorkID will be invalid
    // before call StartSync and received the success callback result
    virtual const SpaceWorkID& GetSpaceWorkID() = 0;
    // check whether current user is owner of this space work
    // if so, return true and also means current user can edit this space work
    // need call AsyncUpdateMetadata at least once
    virtual bool Editable() = 0;

    // start upload or download spacework.
    //
    // If the setters are used, calling StartSync will upload current spacework.
    // Otherwise it will download current spacework. If uploading spacework failed,
    // all setters will reset and you need to try again.
    //
    // In upload situation, the callback is SyncSpaceWorkResult.
    // In download situation, the callback is UserSpaceDownloadResult.
    virtual RailResult StartSync(const RailString& user_data) = 0;
    // get progress of synchronization
    virtual RailResult GetSyncProgress(RailSpaceWorkSyncProgress* progress) = 0;
    // cancel sync
    virtual RailResult CancelSync() = 0;
    // get local folder of file data
    // No need call AsyncUpdateMetadata first
    virtual RailResult GetWorkLocalFolder(RailString* path) = 0;

    // query metadata from server, call back rail event: AsyncUpdateMetadataResult
    virtual RailResult AsyncUpdateMetadata(const RailString& user_data) = 0;

    // how to use getters to get metadata of spacework:
    // step 1. call SetUpdateOptions to set data you want to return
    //         call AsyncUpdateMetadata to fetch data and wait the callback
    // step 2. call getters such as GetName and GetUrl to get data
    // notice: data get from getters maybe old, if you want the newest data,
    //         just repeat step 1 and 2

    // how to use setters to create or update a spacework's data
    // step 1. call OpenSpaceWork or CreateSpaceWork to get a IRailSpaceWork instance
    // step 2. call SetName or other setters to set the data
    // step 3. call StartSync to commit your update, if you create a spacework
    //         you will get a valid SpaceWorkID after sync success

    // need call AsyncUpdateMetadata at least once
    virtual RailResult GetName(RailString* name) = 0;  // name of space work
    // need call AsyncUpdateMetadata at least once, influenced by SetUpdateOptions
    virtual RailResult GetDescription(RailString* description) = 0;  // detail
    // need call AsyncUpdateMetadata at least once
    virtual RailResult GetUrl(RailString* url) = 0;  // detail web page url
    // need call AsyncUpdateMetadata at least once
    virtual uint32_t GetCreateTime() = 0;  // create time(Unix timestamp)
    // need call AsyncUpdateMetadata at least once
    virtual uint32_t GetLastUpdateTime() = 0;  // last update time(Unix timestamp)
    // need call AsyncUpdateMetadata at least once
    virtual uint64_t GetWorkFileSize() = 0;  // whole space work size in bytes
    // need call AsyncUpdateMetadata at least once
    virtual RailResult GetTags(RailArray<RailString>* tags) = 0;  // tags
    // need call AsyncUpdateMetadata at least once
    virtual RailResult GetPreviewImage(RailString* path) = 0;  // local path of preview image file
    // need call AsyncUpdateMetadata at least once
    virtual RailResult GetVersion(RailString* version) = 0;  // version, which is set by creator
    // need call AsyncUpdateMetadata at least once
    virtual uint64_t GetDownloadCount() = 0;  // download count
    // need call AsyncUpdateMetadata at least once
    virtual uint64_t GetSubscribedCount() = 0;  // subscribed count
    // need call AsyncUpdateMetadata at least once
    virtual EnumRailSpaceWorkShareLevel GetShareLevel() = 0;  // visible
    // need call AsyncUpdateMetadata at least once
    virtual uint64_t GetScore() = 0;  // deprecated, please use GetMyVote interface instead
    // user defined data
    // need call AsyncUpdateMetadata at least once, influenced by SetUpdateOptions
    virtual RailResult GetMetadata(const RailString& key, RailString* value) = 0;
    // need call AsyncUpdateMetadata at least once, influenced by SetUpdateOptions
    virtual EnumRailSpaceWorkRateValue GetMyVote() = 0;  // current user's vote for this space work
    // need call AsyncUpdateMetadata at least once, influenced by SetUpdateOptions
    virtual bool IsFavorite() = 0;  // whether this space work is current user's favorites
    // need call AsyncUpdateMetadata at least once, influenced by SetUpdateOptions
    virtual bool IsSubscribed() = 0;  // whether current user had subscribed this space work

    // set upload data, each set interface will override data last set
    // after set all data, call StartSync to upload it
    virtual RailResult SetName(const RailString& name) = 0;
    virtual RailResult SetDescription(const RailString& description) = 0;
    virtual RailResult SetTags(const RailArray<RailString>& tags) = 0;
    // size must under 1MB and only accept png, jpeg, jpg, bmp format
    // otherwise, StartSync will return 13018 error code when update/create this space work
    virtual RailResult SetPreviewImage(const RailString& path_filename) = 0;  // local path
    virtual RailResult SetVersion(const RailString& version) = 0;
    virtual RailResult SetShareLevel(
                        EnumRailSpaceWorkShareLevel level = kRailSpaceWorkShareLevelPublic) = 0;
    virtual RailResult SetMetadata(const RailString& key, const RailString& value) = 0;
    virtual RailResult SetContentFromFolder(const RailString& path) = 0;

    // more getter and setter
    // getter also need call AsyncUpdateMetadata first
    // need call AsyncUpdateMetadata at least once, influenced by SetUpdateOptions
    virtual RailResult GetAllMetadata(RailArray<RailKeyValue>* metadata) = 0;
    // remote urls
    // need call AsyncUpdateMetadata at least once, influenced by SetUpdateOptions
    virtual RailResult GetAdditionalPreviewUrls(RailArray<RailString>* preview_urls) = 0;
    // need call AsyncUpdateMetadata at least once
    virtual RailResult GetAssociatedSpaceWorks(RailArray<SpaceWorkID>* ids) = 0;
    // need call AsyncUpdateMetadata at least once, influenced by SetUpdateOptions
    virtual RailResult GetLanguages(RailArray<RailString>* languages) = 0;

    // setter have same function as setter above
    virtual RailResult RemoveMetadata(const RailString& key) = 0;
    // it should be 20 preview files at most, each one has the same limit to SetPreviewImage
    virtual RailResult SetAdditionalPreviews(const RailArray<RailString>& local_paths) = 0;
    virtual RailResult SetAssociatedSpaceWorks(const RailArray<SpaceWorkID>& ids) = 0;
    virtual RailResult SetLanguages(const RailArray<RailString>& languages) = 0;

    // need call AsyncUpdateMetadata at least once.
    // the value range of param 'scaling' is 1~100.
    virtual RailResult GetPreviewUrl(RailString* url, uint32_t scaling = 100) = 0;
    // need call AsyncUpdateMetadata at least once, influenced by SetUpdateOptions
    virtual RailResult GetVoteDetail(RailArray<RailSpaceWorkVoteDetail>* vote_details) = 0;
    // need call AsyncUpdateMetadata at least once
    virtual RailResult GetUploaderIDs(RailArray<RailID>* uploader_ids) = 0;
    // set RailSpaceWorkUpdateOptions for AsyncUpdateMetadata
    virtual RailResult SetUpdateOptions(const RailSpaceWorkUpdateOptions& options) = 0;
    // need call AsyncUpdateMetadata at least once
    virtual RailResult GetStatistic(EnumRailSpaceWorkStatistic stat_type, uint64_t* value) = 0;
    // remove preview set by SetPreviewImage and GetPreviewUrl will return empty
    virtual RailResult RemovePreviewImage() = 0;
    // get current spacework state, return enumerate value of EnumRailSpaceWorkState
    virtual uint32_t GetState() = 0;
    // add game (or dlc and so on) dependencies for spacework, need call StartSync to take effect
    virtual RailResult AddAssociatedGameIDs(const RailArray<RailGameID>& game_ids) = 0;
    // remove game (or dlc and so on) dependencies for spacework, need call StartSync to take effect
    virtual RailResult RemoveAssociatedGameIDs(const RailArray<RailGameID>& game_ids) = 0;
    // get game (or dlc and so on) dependencies for spacework, need call AsyncUpdateMetadata once
    virtual RailResult GetAssociatedGameIDs(RailArray<RailGameID>* game_ids) = 0;
    // get the local downloaded spacework's version string
    // return kFailure if spacework haven't been downloaded or corrupted
    virtual RailResult GetLocalVersion(RailString* version) = 0;
};

#pragma pack(pop)
}  // namespace rail

#endif  // RAIL_SDK_RAIL_USER_SPACE_H
