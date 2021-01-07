#include <ostream>

extern "C" {
    #include "date.h"
}

using std::ostream;

namespace mtm {
    class DateWrap 
    {
        private:
            Date m_dateADT;
            void safeDateGet(int &day, int &month, int &year) const;
        public:
            DateWrap(int day, int month, int year);
            DateWrap(const DateWrap& dateWrap) = default;
            ~DateWrap() = default;
            DateWrap& operator=(const DateWrap& date) = default;
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
            friend ostream& operator<<(ostream& in, const DateWrap& dateWrap);
    };

    DateWrap operator+(int days, const DateWrap& date);
}