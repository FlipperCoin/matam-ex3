#ifndef _CUSTOM_EVENT_H_
#define _CUSTOM_EVENT_H_

#include "base_event.h"
#include "date_wrap.h"
#include "exceptions.h"

namespace mtm {
    template<typename CanRegister>
    class CustomEvent : public BaseEvent{
    private:
        CanRegister can_register;

    public:
        CustomEvent(const DateWrap& date, const string& event_name, CanRegister can_register):
                BaseEvent(date, event_name), can_register(can_register()){
        };

        CustomEvent(const CustomEvent &event) : BaseEvent(event), can_register(event.can_register){
        }

        CustomEvent* clone() const override{
            return (new CustomEvent(*this));
        };

        //virtual void registerParticipant(int student) override;
        //template<typename CanRegister>
        void registerParticipant(int student) override{
            if (findStudent(student) != -1) {
                throw AlreadyRegistered();
            }
            if (!can_register(student)){
                throw RegistrationBlocked();
            }

            if (participants_num == participants_max) {
                this->resizeListParticipants();
            }

            participants[participants_num++] = student;
            this->sortStudents();
        }
    };
}

#endif