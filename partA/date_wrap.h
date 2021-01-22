#ifndef _DATE_WRAP_H_
#define _DATE_WRAP_H_

#include <ostream>

extern "C" {
    #include "date.h"
}

namespace mtm {
    class DateWrap 
    {
        private:
            Date date_adt;
        public:
            DateWrap(int day, int month, int year);
            DateWrap(const DateWrap& date_wrap);
            ~DateWrap();
            DateWrap& operator=(const DateWrap& date);
            int day() const;
            int month() const;
            int year() const;

            DateWrap operator++(int);
            DateWrap operator+(int days) const;
            DateWrap& operator+=(int days);

            bool operator<(const DateWrap& date) const;
            bool operator==(const DateWrap& date) const;
            bool operator!=(const DateWrap& date) const;
            bool operator<=(const DateWrap& date) const;
            bool operator>(const DateWrap& date) const;
            bool operator>=(const DateWrap& date) const;

    };

    std::ostream& operator<<(std::ostream& out, const DateWrap& date_wrap);
    DateWrap operator+(int days, const DateWrap& date);
}

#endif