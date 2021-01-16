#ifndef _BASE_EVENT_H_
#define _BASE_EVENT_H_

#include <iostream>
#include "date_wrap.h"

using std::string;

namespace mtm {
    const int MINIMUM_STUDENT_NUMBER = 1;
    const int MAXIMUM_STUDENT_NUMBER = 20000;
    const int LIST_RESIZE = 10;

    class BaseEvent {
    protected:
        DateWrap date;
        string event_name;
        int *participants;
        int participants_num;
        int participants_max;
    public:
        BaseEvent(const DateWrap &date, const string& event_name) :
                date(date), event_name(event_name), participants_num(0), participants_max(LIST_RESIZE), participants(new int[LIST_RESIZE]){
        };

        BaseEvent(const BaseEvent &event):
            date(event.date), event_name(event.event_name), participants_num(event.participants_num), participants_max(event.participants_max),
            participants(new int[event.participants_num + event.participants_max]){
            for (int i = 0; i < event.participants_num; i++) {
                this->participants[i] = event.participants[i];
            }
        }

        virtual void registerParticipant(int student);
        virtual void unregisterParticipant(int student);
        virtual ostream& printShort(ostream &stream) const;
        virtual std::ostream& printLong(std::ostream& stream) const;
        virtual BaseEvent* clone() const = 0;
        virtual ~BaseEvent();
        bool isStudentNumberValid(int student);
        int findStudent(int student);
        void resizeListParticipants();
        void sortStudents();
        BaseEvent& operator=(const BaseEvent &event);
    };

}

#endif