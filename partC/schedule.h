#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include <vector>
#include "date_wrap.h"
#include "event_container.h"

namespace mtm {

    class Schedule {
    private:
        std::vector<EventContainer> eventContainers;
    public:
        void addEvents(const EventContainer& container);
        void registerToEvent(const DateWrap& eventDate, const std::string& eventName, int student);
        void unregisterFromEvent(const DateWrap& eventDate, const std::string& eventName, int student);
        void printAllEvents();
        void printMonthEvents(int month, int year);
        template <class Predicate>
        void printSomeEvents(Predicate predicate, bool verbose = false);
        void printEventDetails(const DateWrap& eventDate, const std::string& eventName);
    };

}

#endif