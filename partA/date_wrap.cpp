#include "date_wrap.h"

namespace mtm {
    DateWrap::DateWrap(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {
    
    }   

    const int& DateWrap::day() const {
        return this->m_day;
    }

    const int& DateWrap::month() const {
        return this->m_month;
    }

    const int& DateWrap::year() const {
        return this->m_year;
    }

    bool DateWrap::operator<=(const DateWrap& date) const {

    }

    bool DateWrap::operator>(const DateWrap& date) const {

    }

    bool DateWrap::operator>=(const DateWrap& date) const {

    }

    bool DateWrap::operator<(const DateWrap& date) const {

    }

    bool DateWrap::operator==(const DateWrap& date) const {
    
    }

    bool DateWrap::operator!=(const DateWrap& date) const {
        
    }

    DateWrap operator+(int days, const DateWrap& date) {
        return date + days;
    }

    ostream& operator<<(ostream& in, const DateWrap& dateWrap) {

    }

    DateWrap DateWrap::operator++(int) {

    }

    DateWrap DateWrap::operator+(int days) const {

    }

    DateWrap& DateWrap::operator+=(int days) {

    }
}

