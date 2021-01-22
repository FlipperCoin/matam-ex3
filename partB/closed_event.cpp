#include "closed_event.h"
#include "exceptions.h"

namespace mtm {

    void ClosedEvent::registerParticipant(int student) {
        if (!isStudentNumberValid(student)) {
            throw InvalidStudent();
        }
        if (participants.find(student) != -1) {
            throw AlreadyRegistered();
        }
        if (!checkInvite(student)){
            throw RegistrationBlocked();
        }
        participants.add(student);
        participants.sort_int();
    }

    bool ClosedEvent::checkInvite(int student){
        if (!isStudentNumberValid(student)) {
            throw InvalidStudent();
        }

        if(invitees.find(student) != -1){
            return true;
        }
        return false;
    }

    void ClosedEvent::addInvitee(int student){
        if (!isStudentNumberValid(student)) {
            throw InvalidStudent();
        }

        if(checkInvite(student)){
            throw AlreadyInvited();
        }
        invitees.add(student);
        invitees.sort_int();
    }

    ClosedEvent *ClosedEvent::clone() const {
        return (new ClosedEvent(*this));
    }

    ClosedEvent::ClosedEvent(const DateWrap &date, const std::string &event_name)
        : BaseEvent(date, event_name), invitees(Vector<int>(10)) {

    }
}