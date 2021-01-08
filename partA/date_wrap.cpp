
#include "date_wrap.h"
#include "exceptions.h"

namespace mtm {
    DateWrap::DateWrap(int day, int month, int year) : m_dateADT(dateCreate(day,month,year)) {
        if (day < 1 || day > 30 || month < 1 || month > 12) {
            throw InvalidDate();
        }

        if (nullptr == m_dateADT) {
            throw Exception(); // TODO
        }
    }

    void DateWrap::safeDateGet(int &day, int &month, int &year) const {
        if (!dateGet(m_dateADT, &day, &month, &year)) {
            throw Exception(); // TODO
        }
    }

    int DateWrap::day() const {
        int day, month, year;
        safeDateGet(day, month, year);
        return day;
    }

    int DateWrap::month() const {
        int day, month, year;
        safeDateGet(day, month, year);
        return month;
    }

    int DateWrap::year() const {
        int day, month, year;
        safeDateGet(day, month, year);
        return year;
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

    ostream& operator<<(ostream& out, const DateWrap& dateWrap) {
        return out << dateWrap.day() << '/' << dateWrap.month() << '/' << dateWrap.year();
    }

    DateWrap DateWrap::operator++(int) {

    }

    DateWrap DateWrap::operator+(int days) const {

    }

    DateWrap& DateWrap::operator+=(int days) {

    }
}

