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
    }

    bool ClosedEvent::checkInvite(int student){
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
    }

    ClosedEvent *ClosedEvent::clone() const {
        return (new ClosedEvent(*this));
    }
}