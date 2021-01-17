#include "event_container.h"
#include "base_event.h"

namespace mtm {

    void EventContainer::sort() {
        int i, j, min;
        BaseEvent *temp;
        for (i = 0; i < events_num - 1; i++) {
            min = i;
            for (j = i + 1; j < events_num; j++) {
                if (*(events[j]) < *(events[min])) {
                    min = j;
                }
            }
            temp = events[i];
            events[i] = events[min];
            events[min] = temp;
        }
    }

    EventContainer::EventIterator EventContainer::begin() {
        sort();
        return EventIterator(events);
    }

    EventContainer::EventIterator EventContainer::end() {
        sort();
        return EventIterator(events + events_num);
    }

    EventContainer::ConstEventIterator EventContainer::begin() const {
        return EventContainer::ConstEventIterator(EventContainer::EventIterator(events));
    }

    EventContainer::ConstEventIterator EventContainer::end() const {
        return EventContainer::ConstEventIterator(EventContainer::EventIterator(events + events_num));
    }

    EventContainer::EventIterator& EventContainer::EventIterator::operator=(const EventContainer::EventIterator &iter) {
        if (&iter == this) {
            return *this;
        }

        this->events = iter.events;
        return *this;
    }

    BaseEvent& EventContainer::EventIterator::operator*() {
        return **events;
    }

    EventContainer::EventIterator& EventContainer::EventIterator::operator++() {
        events++;
        return *this;
    }

    bool EventContainer::EventIterator::operator==(const EventContainer::EventIterator &iter) {
        return events == iter.events;
    }

    bool EventContainer::EventIterator::operator!=(const EventContainer::EventIterator &iter) {
        return !(*this == iter);
    }

    EventContainer::ConstEventIterator &
    EventContainer::ConstEventIterator::operator=(const EventContainer::ConstEventIterator &iter) {
        if (&iter == this) {
            return *this;
        }

        this->iterator = iter.iterator;
        return *this;
    }

    const BaseEvent &EventContainer::ConstEventIterator::operator*() {
        return *iterator;
    }

    EventContainer::ConstEventIterator &EventContainer::ConstEventIterator::operator++() {
        ++iterator;
        return *this;
    }

    bool EventContainer::ConstEventIterator::operator==(const EventContainer::ConstEventIterator &iter) {
        return this->iterator == iter.iterator;
    }

    bool EventContainer::ConstEventIterator::operator!=(const EventContainer::ConstEventIterator &iter) {
        return !(*this == iter);
    }
}