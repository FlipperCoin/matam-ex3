#ifndef _BASE_EVENT_H_
#define _BASE_EVENT_H_

#include <iostream>
#include "date_wrap.h"
#include "vector.h"

using std::string;

namespace mtm {
    const int MINIMUM_STUDENT_NUMBER = 1;
    const int MAXIMUM_STUDENT_NUMBER = 20000;
    const int LIST_RESIZE = 10;

    class BaseEvent {
    protected:
        DateWrap date;
        string event_name;
        Vector<int> participants;
        //int *participants;
        //int participants_num;
        //int participants_max;
    public:
        BaseEvent(const DateWrap &date, const string& event_name) :
                date(date), event_name(event_name), participants(Vector<int>(10)) { }

        BaseEvent(const BaseEvent& event) = default;
        virtual ~BaseEvent() = default;
        virtual void registerParticipant(int student);
        virtual void unregisterParticipant(int student);
        virtual std::ostream& printShort(ostream& stream) const;
        virtual std::ostream& printLong(std::ostream& stream) const;
        virtual BaseEvent* clone() const = 0;
        bool isStudentNumberValid(int student);
        DateWrap getDate() const;
        const DateWrap& getDate();
        const string& getName();
        BaseEvent& operator=(const BaseEvent &event) = delete;
        bool operator<(const BaseEvent &event);
        bool operator==(const BaseEvent &event) const;
    };

}

#endif