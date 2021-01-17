#ifndef _EVENT_CONTAINER_H_
#define _EVENT_CONTAINER_H_

#include "base_event.h"

namespace mtm {

    class EventContainer {
    protected:
        BaseEvent **events;
        int events_num;
        int events_max;
        void sort();
    public:
        struct EventIterator {
        private:
            BaseEvent **events;
            int events_num;
        public:
            EventIterator(BaseEvent **events) : events(events) {}
            EventIterator(const EventIterator& iter) : EventIterator(iter.events) {}
            EventIterator& operator=(const EventIterator& iter);
            BaseEvent& operator*();
            EventIterator& operator++();
            bool operator==(const EventIterator& iter);
            bool operator!=(const EventIterator& iter);
        };
        struct ConstEventIterator {
        private:
            EventIterator iterator;
        public:
            explicit ConstEventIterator(const EventIterator& iterator) : iterator(iterator) {}
            ConstEventIterator(const ConstEventIterator& const_iterator) : ConstEventIterator(const_iterator.iterator) {}
            ConstEventIterator& operator=(const ConstEventIterator& iter);
            const BaseEvent& operator*();
            ConstEventIterator& operator++();
            bool operator==(const ConstEventIterator& iter);
            bool operator!=(const ConstEventIterator& iter);
        };
        EventContainer() : events(new BaseEvent*[LIST_RESIZE]), events_num(0), events_max(LIST_RESIZE) {}
        virtual void add(const BaseEvent& event) = 0;
        EventIterator begin();
        EventIterator end();
        ConstEventIterator begin() const;
        ConstEventIterator end() const;
    };

    EventContainer::EventIterator begin(EventContainer& container);
    EventContainer::EventIterator end(EventContainer& container);
    EventContainer::ConstEventIterator begin(const EventContainer& container);
    EventContainer::ConstEventIterator end(const EventContainer& container);
}

#endif
