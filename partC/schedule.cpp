#include "schedule.h"
#include "exceptions.h"
#include <algorithm>
#include <memory>

// TODO: check if lambda is allowed
// TODO: make sure self-assignment is checked everywhere & tested
namespace mtm {

    void Schedule::addEvents(const EventContainer& container) {
        auto events_copy = events;
        for(const BaseEvent& event : container) {
            auto found = findEvent(event);

            if (found != events.end()) {
                throw EventAlreadyExists();
            }

            events_copy.push_back(std::shared_ptr<BaseEvent>(event.clone()));
        }

        events = events_copy;
    }

    void Schedule::registerToEvent(const DateWrap &event_date, const std::string &event_name, int student) {
        auto event = findEvent(event_date, event_name);

        (*safeGetEvent(event)).registerParticipant(student); // TODO: check with Zoe that it throws whatever is needed
    }

    void Schedule::unregisterFromEvent(const DateWrap &event_date, const std::string &event_name, int student) {
        auto event = findEvent(event_date, event_name);

        (*safeGetEvent(event)).unregisterParticipant(student); // TODO: check with Zoe
    }

    void Schedule::printAllEvents() {
        sortEvents();
        printEvents(events);
    }

    void Schedule::printMonthEvents(int month, int year) {
        if (month < 1 || month > 12 || year < 1) {
            throw Exception(); // TODO
        }

        std::vector<std::shared_ptr<BaseEvent>> month_events;
        std::copy_if(events.begin(),
                     events.end(),
                     std::back_inserter(month_events),
                     [month,year](const std::shared_ptr<BaseEvent>& event) {
                            auto event_date = event->getDate();
                            return event_date.month() == month && event_date.year() == year;
                        }
        );
        printEvents(month_events);
    }

    template<class Predicate>
    void Schedule::printSomeEvents(Predicate predicate, bool verbose) {
        // TODO
    }

    void Schedule::printEventDetails(const DateWrap &event_date, const std::string &event_name) {
        auto event = findEvent(event_date, event_name);

        safeGetEvent(event)->printLong(std::cout);
        std::cout << std::endl;
    }

    std::vector<std::shared_ptr<BaseEvent>>::iterator Schedule::findEvent(const BaseEvent &event) {
        auto found = std::find_if(events.begin(),
                                  events.end(),
                                  [&event](const std::shared_ptr<BaseEvent>& other_event) {
                                        return *other_event == event;
                                    });

        return found;
    }

    std::vector<std::shared_ptr<BaseEvent>>::iterator
    Schedule::findEvent(const DateWrap &event_date, const string &event_name) {
        return std::find_if(events.begin(),
                     events.end(),
                     [event_date,event_name](const std::shared_ptr<BaseEvent>& event) {
                           return event_name == event->getName() && event_date == event->getDate();
                        }
        );
    }

    void Schedule::sortEvents() {
        std::sort(events.begin(),
                  events.end(),
                  [](const std::shared_ptr<BaseEvent>& first, const std::shared_ptr<BaseEvent>& second) {
                        return first < second;
                    });
    }

    void Schedule::printEvents(const std::vector<std::shared_ptr<BaseEvent>> &events_to_print) {
        for (const auto& event : events_to_print) {
            event->printShort(std::cout);
            std::cout << std::endl;
        }
    }

    std::shared_ptr<BaseEvent>
    Schedule::safeGetEvent(const std::vector<std::shared_ptr<BaseEvent>>::iterator &iterator) {
        if (iterator == events.end()) {
            throw EventDoesNotExist();
        }

        return *iterator;
    }
}