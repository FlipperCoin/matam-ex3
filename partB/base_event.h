#ifndef _BASE_EVENT_H_
#define _BASE_EVENT_H_

#include "date_wrap.h"
#include <iostream>

using std::string;

namespace mtm {
    const int MINIMUM_STUDENT_NUMBER = 1;
    const int MAXIMUM_STUDENT_NUMBER = 20000;
    const int PARTICIPANTS_RESIZE = 10;

    class BaseEvent {
    private:
        DateWrap date;
        string event_name;
        int *participants;
        int participants_length;
        int participants_max;
    public:
        BaseEvent(const DateWrap &date, const string& event_name, const int * participants, int participants_length);
        BaseEvent(const BaseEvent&event);
        virtual void registerParticipant(int student);
        virtual void unregisterParticipant(int student);
        virtual ostream& printShort(ostream &stream) const;
        virtual std::ostream& printLong(std::ostream& stream) const;
        virtual BaseEvent clone() const;
        virtual ~BaseEvent();
        bool isStudentNumberValid(int student);
        int findStudent(int student);
        void sortStudents();
        BaseEvent& operator=(const BaseEvent &event);
    };

}

#endif