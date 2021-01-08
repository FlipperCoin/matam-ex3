#include "base_event.h"
#include "exceptions.h"

namespace mtm {

    BaseEvent::BaseEvent(const BaseEvent &event) :
            BaseEvent(event.date, event.event_name, event.participants, event.participants_max) {

    }

    BaseEvent::BaseEvent(const DateWrap &date, const string& event_name, const int *participants,
                         int participants_length) :
            date(date), event_name(event_name), participants_max(participants_length), participants_length(participants_length)
    {
        if (participants == nullptr) {
            throw Exception(); // TODO
        }

        this->participants = new int[participants_length];

        for (int i = 0; i < participants_length; i++) {
            if (!isStudentNumberValid(participants[i])) {
                throw InvalidStudent();
            }

            this->participants[i] = participants[i];
        }
        this->sortStudents();
    }

    void BaseEvent::registerParticipant(int student) {
        if (findStudent(student) != -1) {
            throw AlreadyRegistered();
        }

        if (participants_length == participants_max) {
            int *temp = new int[participants_max + PARTICIPANTS_RESIZE];
            participants_max += PARTICIPANTS_RESIZE;

            for (int i = 0; i < participants_length; i++) {
                temp[i] = participants[i];
            }

            delete[] participants;
            participants = temp;
        }

        participants[participants_length++] = student;
        this->sortStudents();
    }

    void BaseEvent::unregisterParticipant(int student) {
        int index = findStudent(student);
        if (index == -1) {
            throw NotRegistered();
        }
        participants[index] = participants[--participants_length];
        this->sortStudents();
    }

    std::ostream &BaseEvent::printShort(std::ostream &stream) const {
        return stream << event_name << " " << date << std::endl;
    }

    std::ostream &BaseEvent::printLong(std::ostream &stream) const {
        printShort(stream);
        for (int i = 0; i < participants_length; ++i) {
            stream << participants[i] << std::endl;
        }
    }

    BaseEvent BaseEvent::clone() const {
        return *this;
    }

    BaseEvent::~BaseEvent() {
        delete[] participants;
    }

    BaseEvent &BaseEvent::operator=(const BaseEvent &event) {
        int *temp = new int[event.participants_max];
        for (int i = 0; i < event.participants_length; ++i) {
            temp[i] = event.participants[i];
        }

        delete[] participants;
        participants = temp;
        participants_length = event.participants_length;
        participants_max = event.participants_max;
    }

    bool BaseEvent::isStudentNumberValid(int student) {
        return !(student < MINIMUM_STUDENT_NUMBER || student > MAXIMUM_STUDENT_NUMBER);
    }

    int BaseEvent::findStudent(int student) {
        for (int i = 0; i < participants_length; i++) {
            if (participants[i] == student) {
                return i;
            }
        }
        return -1;
    }

    // TODO check this
    void BaseEvent::sortStudents() {
        int i, j, min, temp;
        for (i = 0; i < participants_length - 1; i++) {
            min = i;
            for (j = i + 1; j < participants_length; j++) {
                if (participants[j] < participants[min]) {
                    min = j;
                }
            }
            temp = participants[i];
            participants[i] = participants[min];
            participants[min] = temp;
        }
    }
}