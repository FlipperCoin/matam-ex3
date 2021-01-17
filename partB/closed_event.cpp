#include "closed_event.h"
#include "exceptions.h"

namespace mtm {

    void ClosedEvent::registerParticipant(int student) {
        if (findStudent(student) != -1) {
            throw AlreadyRegistered();
        }
        if (!checkInvite(student)){
            throw RegistrationBlocked();
        }
        participants.add(student);
    }

    bool ClosedEvent::checkInvite(int student){
        for (int i = 0; i < invitees_num; i++) {
            if (invitees[i] == student) {
                return true;
            }
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

        if (invitees_max == invitees_num) {
            this->resizeListInvitees();
        }
        invitees[invitees_num++] = student;
    }

    void ClosedEvent::resizeListInvitees(){
        int *temp = new int[invitees_max + LIST_RESIZE];
        invitees_max += LIST_RESIZE;
        for (int i = 0; i < invitees_num; i++) {
            temp[i] = invitees[i];
        }
        delete[] invitees;
        invitees = temp;
    }

    ClosedEvent::~ClosedEvent() {
        delete[] participants;
        delete[] invitees;
    }
}