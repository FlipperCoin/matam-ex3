#ifndef _RECURRING_EVENT_H_
#define _RECURRING_EVENT_H_

#include "event_container.h"
#include "vector.h"
#include "date_wrap.h"
#include "shared_pointer.h"
#include "exceptions.h"

namespace mtm {
    //typedef EventType OpenEvent;
    template<class EventType>
    class RecurringEvent : public EventContainer{
    private:
        DateWrap first_date;
        string event_name;
        int interval_days;
        int num_occurrences;
    public:
        RecurringEvent(const DateWrap& _first_date, const string& _event_name, int _interval_days, int _num_occurrences) :
        first_date(_first_date), interval_days(_interval_days), num_occurrences(_num_occurrences){
            if (interval_days < 0){
                throw InvalidInterval();
            }
            if (num_occurrences < 0){
                throw InvalidNumber();
            }
            DateWrap current_event_date = first_date;
            for (int i = 0; i < num_occurrences; ++i) {
                events.add(SharedPointer<BaseEvent>(new EventType(current_event_date, event_name)));
                current_event_date = current_event_date + interval_days; // += allowed??
            }
        };

        void add(const BaseEvent& event) override{
            throw NotSupported();
        }
    };

}

#endif