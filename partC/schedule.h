#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include <vector>
#include <memory>
#include "date_wrap.h"
#include "event_container.h"

namespace mtm {

    class Schedule {
    private:
        std::vector<std::shared_ptr<BaseEvent>> events;
        void sortEvents();
        void printEvents(const std::vector<std::shared_ptr<BaseEvent>>& events_to_print);
        std::vector<std::shared_ptr<BaseEvent>>::iterator findEvent(const BaseEvent& event);
        std::vector<std::shared_ptr<BaseEvent>>::iterator findEvent(const DateWrap &event_date, const std::string &event_name);
        std::shared_ptr<BaseEvent> safeGetEvent(const std::vector<std::shared_ptr<BaseEvent>>::iterator& iterator);
    public:
        Schedule() = default;
        Schedule(const Schedule& other) = default;
        Schedule(Schedule&& other) noexcept = default;
        ~Schedule() = default;
        Schedule& operator=(const Schedule& other) = default;
        void addEvents(const EventContainer& container);
        void registerToEvent(const DateWrap& event_date, const std::string& event_name, int student);
        void unregisterFromEvent(const DateWrap& event_date, const std::string& event_name, int student);
        void printAllEvents();
        void printMonthEvents(int month, int year);
        template <class Predicate>
        void printSomeEvents(Predicate predicate, bool verbose = false);
        void printEventDetails(const DateWrap& event_date, const std::string& event_name);
    };

}

#endif