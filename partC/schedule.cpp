#include "schedule.h"
#include "exceptions.h"
#include <algorithm>
#include <memory>

using std::string;

namespace mtm {

    void Schedule::addEvents(const EventContainer& container) {
        auto events_copy = events;
        for(const BaseEvent& event : container) {
            auto found = findEvent(events_copy, event);

            if (found != events_copy.end()) {
                throw EventAlreadyExists();
            }

            events_copy.push_back(std::shared_ptr<BaseEvent>(event.clone()));
        }

        events = events_copy;
        sortEvents();
    }

    void Schedule::registerToEvent(const DateWrap &event_date, const std::string &event_name, int student) {
        auto event = findEvent(event_date, event_name);

        (*safeGetEvent(event)).registerParticipant(student);
    }

    void Schedule::unregisterFromEvent(const DateWrap &event_date, const std::string &event_name, int student) {
        auto event = findEvent(event_date, event_name);

        (*safeGetEvent(event)).unregisterParticipant(student);
    }

    void Schedule::printAllEvents() const {
        printEvents(events);
    }

    void Schedule::printMonthEvents(int month, int year) const {
        if (month < 1 || month > 12) {
            throw InvalidNumber();
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

    void Schedule::printEventDetails(const DateWrap &event_date, const std::string &event_name) const {
        auto event = findEvent(event_date, event_name);

        safeGetEvent(event)->printLong(*output);
        *output << std::endl;
    }

    std::vector<std::shared_ptr<BaseEvent>>::const_iterator
    Schedule::findEvent(const std::vector<std::shared_ptr<BaseEvent>>& events_container, const BaseEvent &event) {
        return std::find_if(events_container.begin(),
                                  events_container.end(),
                                  [&event](const std::shared_ptr<BaseEvent>& other_event) {
                                        return *other_event == event;
                                    });
    }

    std::vector<std::shared_ptr<BaseEvent>>::const_iterator
    Schedule::findEvent(const DateWrap &event_date, const string &event_name) const {
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
                        return *first < *second;
                    });
    }

    void Schedule::printEvents(const std::vector<std::shared_ptr<BaseEvent>> &events_to_print, bool verbose) const {
        for (const auto& event : events_to_print) {
            if (verbose) {
                event->printLong(*output);
            } else {
                event->printShort(*output);
            }
            *output << std::endl;
        }
    }

    std::shared_ptr<BaseEvent>
    Schedule::safeGetEvent(const std::vector<std::shared_ptr<BaseEvent>>::const_iterator &iterator) {
        if (iterator == events.end()) {
            throw EventDoesNotExist();
        }

        return *iterator;
    }

    std::shared_ptr<const BaseEvent>
    Schedule::safeGetEvent(const std::vector<std::shared_ptr<BaseEvent>>::const_iterator &iterator) const {
        if (iterator == events.end()) {
            throw EventDoesNotExist();
        }

        return *iterator;
    }

    Schedule::Schedule(const Schedule &other) : output(other.output) {
        for (const auto& event : other.events) {
            events.push_back(std::shared_ptr<BaseEvent>(event->clone()));
        }
    }

    Schedule &Schedule::operator=(Schedule other) {
        events = other.events;
        output = other.output;
        return *this;
    }
}