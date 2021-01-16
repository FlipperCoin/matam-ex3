
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

    DateWrap::DateWrap(int day, int month, int year) : dateAdt(dateCreate(day, month, year)) {
        if (!isDateValid(day, month)) {
            throw InvalidDate();
        }

        if (nullptr == dateAdt) {
            throw Exception(); // TODO
        }
    }

    void DateWrap::safeDateGet(int &day, int &month, int &year) const {
        if (!dateGet(dateAdt, &day, &month, &year)) {
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
        return (dateCompare(dateAdt, date.dateAdt) < 0);
    }

    bool DateWrap::operator==(const DateWrap& date) const {
        return (dateCompare(dateAdt, date.dateAdt) == 0);
    }

    bool DateWrap::operator!=(const DateWrap& date) const {
        return !(*this == date);
    }

    DateWrap operator+(int days, const DateWrap& date) {
        return date + days;
    }

    ostream& operator<<(ostream& out, const DateWrap& dateWrap) {
        return out << dateWrap.day() << '/' << dateWrap.month() << '/' << dateWrap.year();
    }

    DateWrap DateWrap::operator++(int) {
        DateWrap dateCopy = *this;
        dateTick(dateAdt);
        return dateCopy;
    }

    DateWrap DateWrap::operator+(int days) const {
        if (days < 0) {
            throw NegativeDays();
        }

        DateWrap dateCopy = *this;
        for (int i = 0; i < days; ++i) {
            dateTick(dateCopy.dateAdt);
        }

        return dateCopy;
    }

    DateWrap& DateWrap::operator+=(int days) {
        // incrementing a copy so in case of failure "this" doesn't change
        DateWrap newDate = *this + days;
        *this = newDate;
        return *this;
    }

    DateWrap::DateWrap(const DateWrap &dateWrap) : DateWrap(dateWrap.day(), dateWrap.month(), dateWrap.year()) {

    }

    DateWrap& DateWrap::operator=(const DateWrap &date) {
        Date dateAdtCopy = dateCopy(date.dateAdt);
        if (dateAdtCopy == nullptr) {
            throw Exception(); // TODO
        }

        dateDestroy(dateAdt);
        dateAdt = dateAdtCopy;

        return *this;
    }

    DateWrap::~DateWrap() {
        dateDestroy(dateAdt);
    }
}

