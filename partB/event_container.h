#ifndef _EVENT_CONTAINER_H_
#define _EVENT_CONTAINER_H_

#include "base_event.h"
#include "vector.h"
#include "shared_pointer.h"

namespace mtm {

    class EventContainer {
    protected:
        Vector<SharedPointer<BaseEvent>> events;
        void sort();
        EventContainer(const EventContainer& other);
        EventContainer& operator=(const EventContainer& other);
    public:
        struct EventIterator {
        private:
            Vector<SharedPointer<BaseEvent>> *events;
            int index;
        public:
            explicit EventIterator(Vector<SharedPointer<BaseEvent>>& events, int index = 0) : events(&events), index(index) {}
            EventIterator(const EventIterator& iter) : EventIterator(*iter.events) {}
            EventIterator& operator=(const EventIterator& iter);
            BaseEvent& operator*();
            EventIterator& operator++();
            bool operator==(const EventIterator& iter);
            bool operator!=(const EventIterator& iter);
        };
        struct ConstEventIterator {
        private:
            const Vector<SharedPointer<BaseEvent>> *events;
            int index;
        public:
            explicit ConstEventIterator(const Vector<SharedPointer<BaseEvent>>& events, int index = 0) : events(&events), index(index) {}
            ConstEventIterator(const ConstEventIterator& const_iterator) : ConstEventIterator(*const_iterator.events,const_iterator.index) {}
            ConstEventIterator& operator=(const ConstEventIterator& iter);
            const BaseEvent& operator*();
            ConstEventIterator& operator++();
            bool operator==(const ConstEventIterator& iter);
            bool operator!=(const ConstEventIterator& iter);
        };
        EventContainer() = default;
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
