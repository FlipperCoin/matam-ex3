#ifndef _CUSTOM_EVENT_H_
#define _CUSTOM_EVENT_H_

#include "base_event.h"
#include "date_wrap.h"
#include "exceptions.h"

namespace mtm {
    template<class CanRegister>
    class CustomEvent : public BaseEvent{
    private:
        CanRegister can_register;

    public:
        CustomEvent(const DateWrap& date, const std::string& event_name, CanRegister can_register):
                BaseEvent(date, event_name), can_register(can_register){
        };

// TODO: default copy
        CustomEvent(const CustomEvent &event) : BaseEvent(event), can_register(event.can_register){
        }
        ~CustomEvent() override = default;
        CustomEvent& operator=(const CustomEvent& other) = default;
        CustomEvent* clone() const override{
            return (new CustomEvent(*this));
        };

        void registerParticipant(int student) override{
            if (!isStudentNumberValid(student)) {
                throw InvalidStudent();
            }
            if (participants.find(student) != -1) {
                throw AlreadyRegistered();
            }
            if (!can_register(student)){
                throw RegistrationBlocked();
            }
            participants.add(student);
            participants.sort_int();
        }


    };
}

#endif