#ifndef _OPEN_EVENT_H_
#define _OPEN_EVENT_H_

#include "base_event.h"

namespace mtm {
    class OpenEvent : public BaseEvent {

    public:
        OpenEvent(const DateWrap &date, const string& event_name)
                : BaseEvent(date,event_name) {
        };
        OpenEvent* clone() const override{
            return (new OpenEvent(*this));
        };
    };
}

#endif