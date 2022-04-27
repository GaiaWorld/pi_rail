//! 用户模块

use std::ffi::CString;
use crate::ffi::AsyncAcquireSessionTicket;

#[allow(temporary_cstring_as_ptr)]
pub fn async_acquire_session_ticket(user_data: &str) {
	unsafe { 
		AsyncAcquireSessionTicket(
			CString::new(user_data).expect(format!("Invalid user data").as_str()).as_ptr()
		)
	};
}