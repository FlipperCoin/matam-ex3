#ifndef _BASE_EVENT_H_
#define _BASE_EVENT_H_

#include <iostream>
#include "date_wrap.h"
#include "vector.h"

using std::string;

namespace mtm {
    const int MINIMUM_STUDENT_NUMBER = 1;
    const int MAXIMUM_STUDENT_NUMBER = 1234567890;
    const int LIST_RESIZE = 10;

    class BaseEvent {
    protected:
        DateWrap date;
        string event_name;
        Vector<int> participants;
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
        static bool isStudentNumberValid(int student);
        const DateWrap& getDate() const;
        const string& getName() const;
        BaseEvent& operator=(const BaseEvent &event) = delete;
        bool operator<(const BaseEvent &event);
        bool operator==(const BaseEvent &event) const;
    };

}

#endif