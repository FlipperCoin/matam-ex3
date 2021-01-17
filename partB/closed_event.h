#ifndef _CLOSED_EVENT_H_
#define _CLOSED_EVENT_H_

#include "base_event.h"
#include "date_wrap.h"
#include <iostream>

namespace mtm {
    class ClosedEvent : public BaseEvent{
    private:
        Vector<int> invitees;
    public:
        ClosedEvent(const DateWrap& date, const string& event_name):
                    BaseEvent(date, event_name), invitees(Vector<int>(10)){
        };
        ClosedEvent(const ClosedEvent &event) = default;
        ClosedEvent* clone() const override;
        void registerParticipant(int student) override;
        bool checkInvite(int student);
        void addInvitee(int student);
    };
}
#endif