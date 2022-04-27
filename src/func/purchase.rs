//! 内购模块

// use std::os::raw::c_char;
use std::ffi::CString;

use crate::ffi::AsyncShowPaymentWindow;

/// 异步显示购买窗口
#[allow(temporary_cstring_as_ptr)]
pub fn async_show_payment_window(order_id: &str, user_data: &str) {
	unsafe { 
		AsyncShowPaymentWindow(
			CString::new(order_id).expect(format!("Invalid order ID").as_str()).as_ptr(), 
			CString::new(user_data).expect(format!("Invalid user data").as_str()).as_ptr()
		)
	};
}