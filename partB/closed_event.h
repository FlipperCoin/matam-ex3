#ifndef _CLOSED_EVENT_H_
#define _CLOSED_EVENT_H_

#include "base_event.h"
#include "date_wrap.h"
#include <iostream>

namespace mtm {
    class ClosedEvent : public BaseEvent{
    private:
        int *invitees;
        int invitees_num;
        int invitees_max;
    public:
        ClosedEvent(const DateWrap& date, const string& event_name):
                    BaseEvent(date, event_name), invitees_num(0), invitees(new int[LIST_RESIZE]), invitees_max(LIST_RESIZE){
        };

        ClosedEvent(const ClosedEvent &event) : BaseEvent(event), invitees_num(event.invitees_num),
                                                                invitees(new int[event.invitees_max]), invitees_max(event.invitees_max){
            for (int i = 0; i < event.invitees_num; i++) {
                this->invitees[i] = event.invitees[i];
            }
        }

        ClosedEvent* clone() const override{
            return (new ClosedEvent(*this));
        };

        void registerParticipant(int student) override;
        bool checkInvite(int student);
        void resizeListInvitees();
        ~ClosedEvent() override;
        void addInvitee(int student);


    };

}

#endif