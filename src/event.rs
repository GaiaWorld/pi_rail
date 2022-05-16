//! 事件模块
use crate::ffi::{CreateEventHandler, rail_RailResult, rail_EventBase, rail_RailRegisterEvent, rail_RailUnregisterEvent, rail_IRailEvent, rail_RailFireEvents, rail_RAILEventID};

/// 添加事件处理器
pub fn register_event<F>(event_id: EventID, event_handler: F) -> Handle
where F: Fn(EventID, RailResult, *mut rail_EventBase) + 'static{
	unsafe extern "C" fn callback (
		context: u64,
		event_id: EventID,
		result: RailResult, // res 直接翻译到rust层，解析不出来，所以添加了一个参数
		event: *mut rail_EventBase,
	) {
		let handler= &mut * (context as *mut EventHandler);
		// let userdata = CString::from_raw(user_data as usize as *mut ::std::os::raw::c_char).into_string().expect("user_data parse fail!");
		(handler.f)(event_id, result, event);
		
	}

	struct EventHandler {
		f: Box<dyn Fn(EventID, RailResult, *mut rail_EventBase)>
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

pub type EventID = rail_RAILEventID;

pub type RailResult = rail_RailResult;
pub type RailID = u64;
pub type GameID = u64;
pub type UserData = String;



