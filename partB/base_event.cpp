#include "base_event.h"
#include "exceptions.h"
#include "vector.h"

using std::string;

namespace mtm {

    void BaseEvent::registerParticipant(int student) {
        if (!isStudentNumberValid(student)) {
            throw InvalidStudent();
        }

        if (participants.find(student) != -1) {
            throw AlreadyRegistered();
        }

        participants.add(student);
        participants.sort_int();
    }

    void BaseEvent::unregisterParticipant(int student) {
        if (!isStudentNumberValid(student)) {
            throw InvalidStudent();
        }

        int index = participants.find(student);
        if (index == -1) {
            throw NotRegistered();
        }
        participants.remove(student);
        participants.sort_int();
    }

    std::ostream &BaseEvent::printShort(std::ostream &stream) const {
        return stream << event_name << " " << date << std::endl;
    }

    std::ostream& BaseEvent::printLong(std::ostream& stream) const {
        printShort(stream);
        for (int i = 0; i < participants.getCount() ; ++i) {
            stream << participants[i] << std::endl;
        }

        return stream;
    }

    bool BaseEvent::isStudentNumberValid(int student) {
        return !(student < MINIMUM_STUDENT_NUMBER || student > MAXIMUM_STUDENT_NUMBER);
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

     const DateWrap& BaseEvent::getDate() const {
        return date;
    }

    bool BaseEvent::operator==(const BaseEvent &event) const {
        return (date == event.date && event_name == event.event_name);
    }

    const string &BaseEvent::getName() const {
        return event_name;
    }

    BaseEvent::BaseEvent(const DateWrap &date, const string &event_name) :
            date(date), event_name(event_name), participants(Vector<int>(10)) {

    }
}