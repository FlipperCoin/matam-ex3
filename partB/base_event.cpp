#include "base_event.h"
#include "exceptions.h"

namespace mtm {

    void BaseEvent::registerParticipant(int student) {
        if (!isStudentNumberValid(student)) {
            throw InvalidStudent();
        }

        if (findStudent(student) != -1) {
            throw AlreadyRegistered();
        }

        if (participants_num == participants_max) {
            this->resizeListParticipants();
        }

        participants[participants_num++] = student;
        this->sortStudents();
    }

    void BaseEvent::unregisterParticipant(int student) {
        int index = findStudent(student);
        if (index == -1) {
            throw NotRegistered();
        }
        participants[index] = participants[--participants_num];
        this->sortStudents();

    }

    std::ostream &BaseEvent::printShort(std::ostream &stream) const {
        return stream << event_name << " " << date << std::endl;
    }

    std::ostream &BaseEvent::printLong(std::ostream &stream) const {
        printShort(stream);
        for (int i = 0; i < participants_num; ++i) {
            stream << participants[i] << std::endl;
        }

        return stream;
    }

    BaseEvent::~BaseEvent() {
        delete[] participants;
    }

    BaseEvent &BaseEvent::operator=(const BaseEvent &event) {
        if (this == &event) {
            return *this;
        }

        int *temp = new int[event.participants_max];
        for (int i = 0; i < event.participants_num; ++i) {
            temp[i] = event.participants[i];
        }

        delete[] participants;
        participants = temp;
        participants_num = event.participants_num;
        participants_max = event.participants_max;

        return *this;
    }

    bool BaseEvent::isStudentNumberValid(int student) {
        return !(student < MINIMUM_STUDENT_NUMBER || student > MAXIMUM_STUDENT_NUMBER);
    }

    void BaseEvent::resizeListParticipants(){
        int *temp = new int[participants_max + LIST_RESIZE];
        participants_max += LIST_RESIZE;
        for (int i = 0; i < participants_num; i++) {
            temp[i] = participants[i];
        }
        delete[] participants;
        participants = temp;
    }

    int BaseEvent::findStudent(int student) {
        for (int i = 0; i < participants_num; i++) {
            if (participants[i] == student) {
                return i;
            }
        }
        return -1;
    }

    // TODO check this
    void BaseEvent::sortStudents() {
        int i, j, min, temp;
        for (i = 0; i < participants_num - 1; i++) {
            min = i;
            for (j = i + 1; j < participants_num; j++) {
                if (participants[j] < participants[min]) {
                    min = j;
                }
            }
            temp = participants[i];
            participants[i] = participants[min];
            participants[min] = temp;
        }
    }

    bool BaseEvent::operator<(const BaseEvent& event) {
        if (date > event.date) {
            return false;
        }

        if (date < event.date) {
            return true;
        }

        return event_name < event.event_name;
    }

    bool BaseEvent::operator==(const BaseEvent &event) const {
        return (date == event.date && event_name == event.event_name);
    }

    const DateWrap &BaseEvent::getDate() {
        return date;
    }

    const string &BaseEvent::getName() {
        return event_name;
    }
}