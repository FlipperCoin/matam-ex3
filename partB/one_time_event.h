#include "event_container.h"
#include "closed_event.h"
#include "exceptions.h"

namespace mtm {
    template<class EventType>
    class OneTimeEvent : public EventContainer {
    private:
        EventType one_time_event;
    public:
        OneTimeEvent(const DateWrap date, const string& event_name) :
            one_time_event(date, event_name){
        }
        void add(const BaseEvent& event) override{
            throw NotSupported();
        }
    };

}