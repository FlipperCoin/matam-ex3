#include <ostream>

using std::ostream;

namespace mtm {
    class DateWrap 
    {
        private:
            int m_day=0;
            int m_month=0;
            int m_year=0;
        public:
            DateWrap(int day, int month, int year);
            DateWrap(const DateWrap& dateWrap) = default;
            ~DateWrap() = default;
            DateWrap& operator=(const DateWrap& date) = default;
            const int& day() const;
            const int& month() const;
            const int& year() const;

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