
#include "date_wrap.h"
#include "exceptions.h"

namespace mtm {
    const int MAX_DAY = 30;
    const int MIN_DAY = 1;
    const int MAX_MONTH = 12;
    const int MIN_MONTH = 1;

    static bool isDateValid(int day, int month) {
        return !(day < 1 || day > 30 || month < 1 || month > 12);
    }

    DateWrap::DateWrap(int day, int month, int year) : date_adt(dateCreate(day, month, year)) {
        if (!isDateValid(day, month)) {
            throw InvalidDate();
        }

        if (nullptr == date_adt) {
            throw Exception(); // TODO
        }
    }

    void DateWrap::safeDateGet(int &day, int &month, int &year) const {
        if (!dateGet(date_adt, &day, &month, &year)) {
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
        return (*this < date || *this == date);
    }

    bool DateWrap::operator>(const DateWrap& date) const {
        return !(*this <= date);
    }

    bool DateWrap::operator>=(const DateWrap& date) const {
        return !(*this < date);
    }

    bool DateWrap::operator<(const DateWrap& date) const {
        return (dateCompare(date_adt, date.date_adt) < 0);
    }

    bool DateWrap::operator==(const DateWrap& date) const {
        return (dateCompare(date_adt, date.date_adt) == 0);
    }

    bool DateWrap::operator!=(const DateWrap& date) const {
        return !(*this == date);
    }

    DateWrap operator+(int days, const DateWrap& date) {
        return date + days;
    }

    ostream& operator<<(ostream& out, const DateWrap& date_wrap) {
        return out << date_wrap.day() << '/' << date_wrap.month() << '/' << date_wrap.year();
    }

    DateWrap DateWrap::operator++(int) {
        DateWrap dateCopy = *this;
        dateTick(date_adt);
        return dateCopy;
    }

    DateWrap DateWrap::operator+(int days) const {
        if (days < 0) {
            throw NegativeDays();
        }

        DateWrap dateCopy = *this;
        for (int i = 0; i < days; ++i) {
            dateTick(dateCopy.date_adt);
        }

        return dateCopy;
    }

    DateWrap& DateWrap::operator+=(int days) {
        // incrementing a copy so in case of failure "this" doesn't change
        DateWrap newDate = *this + days;
        *this = newDate;
        return *this;
    }

    DateWrap::DateWrap(const DateWrap &date_wrap) : DateWrap(date_wrap.day(), date_wrap.month(), date_wrap.year()) {

    }

    DateWrap& DateWrap::operator=(const DateWrap &date) {
        if (this == &date) {
            return *this;
        }

        Date dateAdtCopy = dateCopy(date.date_adt);
        if (dateAdtCopy == nullptr) {
            throw Exception(); // TODO
        }

        dateDestroy(date_adt);
        date_adt = dateAdtCopy;

        return *this;
    }

    DateWrap::~DateWrap() {
        dateDestroy(date_adt);
    }
}

