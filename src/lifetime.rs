//! 生命周期模块

use std::ffi::{CString, c_void};
use crate::ffi::{rail_RailInitialize, rail_RailFinalize, NeedRestartAppForCheckingEnvironment};

///
pub fn need_restart_app_for_checking_environment(game_id: u64, argv: Vec<String>) {
	let len = argv.len();
	let s: Vec<CString> = argv.into_iter().map(|r| {
		CString::new(r).unwrap()
	}).collect::<Vec<CString>>();
	let ptr = s.as_ptr();
	unsafe { NeedRestartAppForCheckingEnvironment(game_id, len as i32, ptr as *mut c_void as *mut *const ::std::os::raw::c_char) };
}	

/// 初始化sdk
pub fn initialize() {
	unsafe { rail_RailInitialize() };
}

/// 处理强退逻辑
/// 释放sdk
/// 当不需要RailSDK或者即将结束游戏时，您需要结束RailSDK
pub fn finalize() {
	unsafe { rail_RailFinalize() };
}

// RAIL_API bool RAIL_CALLTYPE RailNeedRestartAppForCheckingEnvironment(RailGameID game_id,
// 	int32_t argc,
// 	const char** argv);
// RAIL_API bool RAIL_CALLTYPE RailInitialize();
// RAIL_API void RAIL_CALLTYPE RailFinalize();