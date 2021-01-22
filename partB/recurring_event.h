#ifndef _RECURRING_EVENT_H_
#define _RECURRING_EVENT_H_

#include "event_container.h"
#include "vector.h"
#include "date_wrap.h"
#include "shared_pointer.h"
#include "exceptions.h"

namespace mtm {
    template<class EventType>
    class RecurringEvent : public EventContainer{
    private:
        DateWrap first_date;
        std::string event_name;
        int num_occurrences;
        int interval_days;
    public:
        RecurringEvent(const DateWrap& _first_date, const std::string& _event_name, int _num_occurrences, int _interval_days) :
        first_date(_first_date), event_name(_event_name), num_occurrences(_num_occurrences), interval_days(_interval_days){
            if (interval_days <= 0){
                throw InvalidInterval();
            }
            if (num_occurrences <= 0){
                throw InvalidNumber();
            }
            DateWrap current_event_date = first_date;
            for (int i = 0; i < num_occurrences; ++i) {
                events.add(SharedPointer<BaseEvent>(new EventType(current_event_date, event_name)));
                current_event_date += interval_days;
            }
        };

        void add(const BaseEvent& event) override{
            throw NotSupported();
        }
    };

}

#endif