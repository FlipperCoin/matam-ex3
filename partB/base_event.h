#ifndef _BASE_EVENT_H_
#define _BASE_EVENT_H_

#include <iostream>
#include "date_wrap.h"
#include "vector.h"

namespace mtm {
    const int MINIMUM_STUDENT_NUMBER = 1;
    const int MAXIMUM_STUDENT_NUMBER = 1234567890;

    class BaseEvent {
    protected:
        DateWrap date;
        std::string event_name;
        Vector<int> participants;
        static bool isStudentNumberValid(int student);
    public:
        BaseEvent(const DateWrap &date, const std::string& event_name);

        BaseEvent(const BaseEvent& event) = default;
        virtual ~BaseEvent() = default;
        virtual void registerParticipant(int student);
        virtual void unregisterParticipant(int student);
        virtual std::ostream& printShort(std::ostream& stream) const;
        virtual std::ostream& printLong(std::ostream& stream) const;
        virtual BaseEvent* clone() const = 0;
        const DateWrap& getDate() const;
        const std::string& getName() const;
        BaseEvent& operator=(const BaseEvent &event) = default;
        bool operator<(const BaseEvent &event);
        bool operator==(const BaseEvent &event) const;
    };

}

#endif