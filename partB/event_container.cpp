#include "event_container.h"
#include "base_event.h"

namespace mtm {

    void EventContainer::sort() {
        if (events.getCount() <= 0) return;

        int i, j, min;
        SharedPointer<BaseEvent> temp;
        for (i = 0; i < events.getCount() - 1; i++) {
            min = i;
            for (j = i + 1; j < events.getCount(); j++) {
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
        return EventIterator(events);
    }

    EventContainer::EventIterator EventContainer::end() {
        return EventIterator(events, events.getCount());
    }

    EventContainer::ConstEventIterator EventContainer::begin() const {
        return EventContainer::ConstEventIterator(events);
    }

    EventContainer::ConstEventIterator EventContainer::end() const {
        return EventContainer::ConstEventIterator(events, events.getCount());
    }

    EventContainer::EventIterator& EventContainer::EventIterator::operator=(const EventContainer::EventIterator &iter) {
        if (&iter == this) {
            return *this;
        }

        this->events = iter.events;
        this->index = iter.index;
        return *this;
    }

    BaseEvent& EventContainer::EventIterator::operator*() {
        return *((*events)[index]);
    }

    EventContainer::EventIterator& EventContainer::EventIterator::operator++() {
        index++;
        return *this;
    }

    bool EventContainer::EventIterator::operator==(const EventContainer::EventIterator &iter) {
        return events == iter.events && index == iter.index;
    }

    bool EventContainer::EventIterator::operator!=(const EventContainer::EventIterator &iter) {
        return !(*this == iter);
    }

    EventContainer::ConstEventIterator &
    EventContainer::ConstEventIterator::operator=(const EventContainer::ConstEventIterator &iter) {
        if (&iter == this) {
            return *this;
        }

        this->events = iter.events;
        this->index = iter.index;
        return *this;
    }

    const BaseEvent &EventContainer::ConstEventIterator::operator*() {
        return *((*events)[index]);
    }

    EventContainer::ConstEventIterator &EventContainer::ConstEventIterator::operator++() {
        this->index++;
        return *this;
    }

    bool EventContainer::ConstEventIterator::operator==(const EventContainer::ConstEventIterator &iter) {
        return this->events == iter.events && this->index == iter.index;
    }

    bool EventContainer::ConstEventIterator::operator!=(const EventContainer::ConstEventIterator &iter) {
        return !(*this == iter);
    }
}