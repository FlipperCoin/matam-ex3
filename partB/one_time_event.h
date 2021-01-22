#include "event_container.h"
#include "closed_event.h"
#include "exceptions.h"

namespace mtm {
    template<class EventType>
    class OneTimeEvent : public EventContainer {
    public:
        OneTimeEvent(const DateWrap& date, const std::string& event_name) {
            events.add(SharedPointer<BaseEvent>(new EventType(date,event_name)));
        }
        void add(const BaseEvent& event) override{
            throw NotSupported();
        }
        ~OneTimeEvent() override = default;
        OneTimeEvent& operator=(const OneTimeEvent& other) = default;
        OneTimeEvent(const OneTimeEvent& other) = default;
    };

}