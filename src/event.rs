//! 事件模块

use std::ffi::CString;

use crate::ffi::{CreateEventHandler, rail_RailResult, rail_RailRegisterEvent, rail_RailUnregisterEvent, rail_IRailEvent, rail_RailFireEvents, rail_RAILEventID};

pub type EventID = rail_RAILEventID;

pub type RailResult = rail_RailResult;
/// 添加事件处理器
pub fn register_event<F>(event_id: EventID, event_handler: F) -> Handle
where F: Fn(EventID, u64, u64, String, RailResult) + 'static{
	unsafe extern "C" fn callback (
		context: u64,
		event_id: EventID,
		rail_id: u64,
		game_id: u64,
		user_data: *const ::std::os::raw::c_char,
		result: RailResult,
	) {
		let handler = Box::from_raw(context as *mut EventHandler);
		let userdata = CString::from_raw(user_data as usize as *mut ::std::os::raw::c_char).into_string().expect("user_data parse fail!");
		(handler.f)(event_id, rail_id, game_id, userdata, result);
	
	}

	struct EventHandler {
		f: Box<dyn Fn(EventID, u64, u64, String, RailResult)>
	}

	let event_handler = Box::new(event_handler);

	let handler =  EventHandler {
		f: event_handler,
	};

	let handler = unsafe{ CreateEventHandler(
		Box::into_raw(Box::new(handler)) as u64, 
		Some(callback))};
	unsafe{rail_RailRegisterEvent(event_id, handler);}
	
	Handle {
		handle: handler
	}
}

/// 取消事件处理器
#[inline]
pub fn un_register_event<F>(event_id: EventID, handle: Handle) {
	unsafe { rail_RailUnregisterEvent(event_id, handle.handle)};
}

/// 驱动事件
/// 一帧或者数帧调用一次
#[inline]
pub fn fire_events() {
	unsafe { rail_RailFireEvents() }
}

#[derive(Clone)]
pub struct Handle {
	handle: *mut rail_IRailEvent
}



