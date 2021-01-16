#include "event_container.h"

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
        return EventIterator(events, events_num);
    }

    EventContainer::EventIterator EventContainer::end() {
        sort();
        return EventIterator(events + events_num, events_num);
    }

    EventContainer::EventIterator& EventContainer::EventIterator::operator=(const EventContainer::EventIterator &iter) {
        this->events = iter.events;
        this->events_num = iter.events_num;
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
}