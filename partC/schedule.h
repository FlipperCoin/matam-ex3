#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include <vector>
#include <memory>
#include <algorithm>
#include "date_wrap.h"
#include "event_container.h"

namespace mtm {
    class Schedule {
    private:
        std::ostream* output;
        std::vector<std::shared_ptr<BaseEvent>> events;
        void sortEvents();
        void printEvents(const std::vector<std::shared_ptr<BaseEvent>>& events_to_print, bool verbose = false) const;
        std::vector<std::shared_ptr<BaseEvent>>::const_iterator
        findEvent(const DateWrap &event_date, const std::string &event_name) const;
        static std::vector<std::shared_ptr<BaseEvent>>::const_iterator
        findEvent(const std::vector<std::shared_ptr<BaseEvent>>& events_container, const BaseEvent &event);
        std::shared_ptr<BaseEvent> safeGetEvent(const std::vector<std::shared_ptr<BaseEvent>>::const_iterator& iterator);
        std::shared_ptr<const BaseEvent> safeGetEvent(const std::vector<std::shared_ptr<BaseEvent>>::const_iterator& iterator) const;
    public:
        Schedule() : Schedule(&std::cout) {};
        explicit Schedule(std::ostream* output) : output(output) {};
        Schedule(const Schedule& other) = default;
        Schedule(Schedule&& other) noexcept = default;
        ~Schedule() = default;
        Schedule& operator=(const Schedule& other) = default;
        void addEvents(const EventContainer& container);
        void registerToEvent(const DateWrap& event_date, const std::string& event_name, int student);
        void unregisterFromEvent(const DateWrap& event_date, const std::string& event_name, int student);
        void printAllEvents() const;
        void printMonthEvents(int month, int year) const;

        template<typename Predicate>
        void printSomeEvents(Predicate predicate, bool verbose = false) const;
        void printEventDetails(const DateWrap& event_date, const std::string& event_name) const;
    };

    template<typename Predicate>
    void Schedule::printSomeEvents(Predicate predicate, bool verbose) const {
        std::vector<std::shared_ptr<BaseEvent>> some_events;
        std::copy_if(events.begin(),
                     events.end(),
                     std::back_inserter(some_events),
                     [&predicate](const std::shared_ptr<BaseEvent>& event) { return predicate(*event); });

        printEvents(some_events, verbose);
    }
}

#endif