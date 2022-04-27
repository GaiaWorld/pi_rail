#include "rail/sdk/rail_api.h"

// =========== rust


#ifdef __cplusplus
extern "C" {
#endif

// user_data 以0結尾的字符串
typedef void (*Handler)(size_t context, rail::RAIL_EVENT_ID event_id, uint64_t rail_id, uint64_t game_id, const char* user_data, rail::RailResult result);

class EventHandler : public rail::IRailEvent {
public:
	Handler callback;
	size_t context;
	
    virtual void OnRailEvent(rail::RAIL_EVENT_ID event_id, rail::EventBase* param) {
		this->callback(this->context, event_id, param->rail_id.get_id(), param->game_id.get_id(), param->user_data.c_str(), param->result);
    }
};

rail::IRailEvent* CreateEventHandler(size_t context, Handler handler) {
	EventHandler* r = new EventHandler();
	r -> callback = handler;
	r -> context = context;
	return r;
}

void* AsyncShowPaymentWindow(const char* order_id, const char* user_data) {
	rail::IRailFactory *factory = rail::RailFactory();

	rail::IRailInGameStorePurchaseHelper* helper = factory->RailInGameStorePurchaseHelper();
	helper->AsyncShowPaymentWindow(order_id, user_data);
}

void* NeedRestartAppForCheckingEnvironment(uint64_t order_id, int32_t argc, const char** argv) {
	rail::RailNeedRestartAppForCheckingEnvironment(order_id, argc, argv);
}

void* AsyncAcquireSessionTicket(const char* user_data) {
	rail::IRailFactory *factory = rail::RailFactory();

	rail::IRailPlayer* helper = factory->RailPlayer();
	helper->AsyncAcquireSessionTicket(user_data);
}

#ifdef __cplusplus
}
#endif