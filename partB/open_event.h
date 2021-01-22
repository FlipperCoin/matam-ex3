#ifndef _OPEN_EVENT_H_
#define _OPEN_EVENT_H_

#include "base_event.h"

namespace mtm {
    class OpenEvent : public BaseEvent {

    public:
        OpenEvent(const DateWrap &date, const std::string& event_name);
        OpenEvent* clone() const override;
        ~OpenEvent() override = default;
        OpenEvent& operator=(const OpenEvent& other) = default;
        OpenEvent(const OpenEvent& other) = default;
    };
}

#endif