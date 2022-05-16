#include "rail/sdk/rail_api.h"
#include <stdio.h>
#include "iostream"

// =========== rust


#ifdef __cplusplus
extern "C" {
#endif

// user_data 以0結尾的字符串
// typedef void (*Handler)(size_t context, rail::RAIL_EVENT_ID event_id, uint64_t rail_id, uint64_t game_id, const char* user_data, rail::RailResult result);
typedef void (*Handler)(size_t context, rail::RAIL_EVENT_ID event_id, rail::RailResult result, rail::EventBase* param);

class EventHandler : public rail::IRailEvent {
public:
	Handler callback;
	size_t context;
	
    virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) {
		rail::RailResult result = param->result;
		this->callback(this->context, event_id, result, param);
    }
};

rail::IRailEvent* CreateEventHandler(size_t context, Handler handler) {
	EventHandler* r = new EventHandler();
	r -> callback = handler;
	r -> context = context;
	return r;
}

void AsyncShowPaymentWindow(const char* order_id, const char* user_data) {
	rail::IRailFactory *factory = rail::RailFactory();
	rail::IRailInGameStorePurchaseHelper* helper = factory->RailInGameStorePurchaseHelper();
	helper->AsyncShowPaymentWindow(order_id, user_data);
}

void NeedRestartAppForCheckingEnvironment(uint64_t order_id, int32_t argc, const char** argv) {
	rail::RailNeedRestartAppForCheckingEnvironment(order_id, argc, argv);
}

void AsyncAcquireSessionTicket(const char* user_data) {
	rail::IRailFactory *factory = rail::RailFactory();
	rail::IRailPlayer* helper = factory->RailPlayer();
	helper->AsyncAcquireSessionTicket(user_data);
}

#ifdef __cplusplus
}
#endif