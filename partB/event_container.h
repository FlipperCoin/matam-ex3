#ifndef _EVENT_CONTAINER_H_
#define _EVENT_CONTAINER_H_

#include "base_event.h"

namespace mtm {

    class EventContainer {
    protected:
        struct EventIterator {
        private:
            BaseEvent **events;
            int events_num;
        public:
            EventIterator(BaseEvent **events, int events_num) : events(events), events_num(events_num) {}
            EventIterator(const EventIterator& iter) : EventIterator(iter.events, iter.events_num) {}
            EventIterator& operator=(const EventIterator& iter);
            BaseEvent& operator*();
            EventIterator& operator++();
            bool operator==(const EventIterator& iter);
            bool operator!=(const EventIterator& iter);
        };
        BaseEvent **events;
        int events_num;
        int events_max;
        void sort();
    public:
        EventContainer() : events(new BaseEvent*[LIST_RESIZE]), events_num(0), events_max(LIST_RESIZE) {}
        virtual void add(BaseEvent& event) = 0;
        EventIterator begin();
        EventIterator end();
    };

}

#endif
