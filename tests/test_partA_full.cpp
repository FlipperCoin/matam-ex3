#include "gtest/gtest.h"
#include "date_wrap.h"
#include "exceptions.h"

using namespace mtm;

class DateWrapTests : public ::testing::Test {

protected:
    DateWrap *d;
    int day;
    int month;
    int year;

    void SetUp() override {
        day = 1;
        month = 1;
        year = 1;
        d = new DateWrap(day,month,year);
    }

    void TearDown() override {
        delete d;
    }
};

TEST_F(DateWrapTests, setupTest) {
    EXPECT_TRUE(d);
}

TEST_F(DateWrapTests, ctorTest) {
    EXPECT_NO_THROW(DateWrap d(1,1,1));
}

TEST_F(DateWrapTests, ctorInvalidDate) {
    EXPECT_THROW(DateWrap d(0,1,1), InvalidDate);
    EXPECT_THROW(DateWrap d(-1,1,1), InvalidDate);
    EXPECT_THROW(DateWrap d(31,1,1), InvalidDate);
    EXPECT_THROW(DateWrap d(1,0,1), InvalidDate);
    EXPECT_THROW(DateWrap d(1,-1,1), InvalidDate);
    EXPECT_THROW(DateWrap d(1,13,1), InvalidDate);
    EXPECT_NO_THROW(DateWrap d(1,1,0));
    EXPECT_NO_THROW(DateWrap d(1,1,-1));
    EXPECT_NO_THROW(DateWrap d(30,1,1));
    EXPECT_NO_THROW(DateWrap d(1,12,1));
}

TEST_F(DateWrapTests, copyCtor) {
    EXPECT_NO_THROW(DateWrap d2 = *d);
    DateWrap d2 = *d;
    EXPECT_EQ(d2.year(),d->year());
    EXPECT_EQ(d2.month(),d->month());
    EXPECT_EQ(d2.day(),d->day());
    d2 += 1;
    EXPECT_EQ(d2.day(), day + 1);
    EXPECT_EQ(d->day(), day);
    *d += 5;
    EXPECT_EQ(d2.day(), day + 1);
    EXPECT_EQ(d->day(), day + 5);
}

TEST_F(DateWrapTests, destructor) {
    DateWrap *d2 = new DateWrap(2,2,2);
    delete d2; // valgrind check
}

TEST_F(DateWrapTests, assignment) {
    DateWrap d2(2,2,2);
    d2 = *d;
    EXPECT_EQ(d2.day(), day);
    EXPECT_EQ(d2.month(), month);
    EXPECT_EQ(d2.year(), year);
    d2 += 1;
    EXPECT_EQ(d2.day(), day + 1);
    EXPECT_EQ(d->day(), day);
    *d += 5;
    EXPECT_EQ(d2.day(), day + 1);
    EXPECT_EQ(d->day(), day + 5);
}

TEST_F(DateWrapTests, getDayMonthYear) {
    EXPECT_EQ(d->day(), day);
    EXPECT_EQ(d->month(), month);
    EXPECT_EQ(d->year(), year);
}

TEST_F(DateWrapTests, compareOperators) {
    DateWrap& d1 = *d;
    DateWrap d2(day + 3, month + 2, year);
    DateWrap d3(day + 2, month + 3, year);
    DateWrap d4(day + 1, month + 1, year + 1);

    EXPECT_FALSE(d1 < d1);
    EXPECT_TRUE(d1 < d2);
    EXPECT_TRUE(d1 < d3);
    EXPECT_TRUE(d1 < d4);
    EXPECT_FALSE(d2 < d2);
    EXPECT_TRUE(d2 < d3);
    EXPECT_TRUE(d2 < d4);
    EXPECT_FALSE(d3 < d3);
    EXPECT_TRUE(d3 < d4);
    EXPECT_FALSE(d4 < d4);
    EXPECT_FALSE(d2 < d1);
    EXPECT_FALSE(d3 < d1);
    EXPECT_FALSE(d4 < d1);
    EXPECT_FALSE(d3 < d2);
    EXPECT_FALSE(d4 < d2);
    EXPECT_FALSE(d4 < d3);

    EXPECT_TRUE(d1 <= d1);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d1 <= d3);
    EXPECT_TRUE(d1 <= d4);
    EXPECT_TRUE(d2 <= d2);
    EXPECT_TRUE(d2 <= d3);
    EXPECT_TRUE(d2 <= d4);
    EXPECT_TRUE(d3 <= d3);
    EXPECT_TRUE(d3 <= d4);
    EXPECT_TRUE(d4 <= d4);
    EXPECT_FALSE(d2 <= d1);
    EXPECT_FALSE(d3 <= d1);
    EXPECT_FALSE(d4 <= d1);
    EXPECT_FALSE(d3 <= d2);
    EXPECT_FALSE(d4 <= d2);
    EXPECT_FALSE(d4 <= d3);

    EXPECT_TRUE(d1 == d1);
    EXPECT_FALSE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
    EXPECT_FALSE(d1 == d4);
    EXPECT_TRUE(d2 == d2);
    EXPECT_FALSE(d2 == d3);
    EXPECT_FALSE(d2 == d4);
    EXPECT_TRUE(d3 == d3);
    EXPECT_FALSE(d3 == d4);
    EXPECT_TRUE(d4 == d4);
    EXPECT_FALSE(d2 == d1);
    EXPECT_FALSE(d3 == d1);
    EXPECT_FALSE(d4 == d1);
    EXPECT_FALSE(d3 == d2);
    EXPECT_FALSE(d4 == d2);
    EXPECT_FALSE(d4 == d3);

    EXPECT_TRUE(d1 >= d1);
    EXPECT_FALSE(d1 >= d2);
    EXPECT_FALSE(d1 >= d3);
    EXPECT_FALSE(d1 >= d4);
    EXPECT_TRUE(d2 >= d2);
    EXPECT_FALSE(d2 >= d3);
    EXPECT_FALSE(d2 >= d4);
    EXPECT_TRUE(d3 >= d3);
    EXPECT_FALSE(d3 >= d4);
    EXPECT_TRUE(d4 >= d4);
    EXPECT_TRUE(d2 >= d1);
    EXPECT_TRUE(d3 >= d1);
    EXPECT_TRUE(d4 >= d1);
    EXPECT_TRUE(d3 >= d2);
    EXPECT_TRUE(d4 >= d2);
    EXPECT_TRUE(d4 >= d3);

    EXPECT_FALSE(d1 > d1);
    EXPECT_FALSE(d1 > d2);
    EXPECT_FALSE(d1 > d3);
    EXPECT_FALSE(d1 > d4);
    EXPECT_FALSE(d2 > d2);
    EXPECT_FALSE(d2 > d3);
    EXPECT_FALSE(d2 > d4);
    EXPECT_FALSE(d3 > d3);
    EXPECT_FALSE(d3 > d4);
    EXPECT_FALSE(d4 > d4);
    EXPECT_TRUE(d2 > d1);
    EXPECT_TRUE(d3 > d1);
    EXPECT_TRUE(d4 > d1);
    EXPECT_TRUE(d3 > d2);
    EXPECT_TRUE(d4 > d2);
    EXPECT_TRUE(d4 > d3);

    EXPECT_FALSE(d1 != d1);
    EXPECT_TRUE(d1 != d2);
    EXPECT_TRUE(d1 != d3);
    EXPECT_TRUE(d1 != d4);
    EXPECT_FALSE(d2 != d2);
    EXPECT_TRUE(d2 != d3);
    EXPECT_TRUE(d2 != d4);
    EXPECT_FALSE(d3 != d3);
    EXPECT_TRUE(d3 != d4);
    EXPECT_FALSE(d4 != d4);
    EXPECT_TRUE(d2 != d1);
    EXPECT_TRUE(d3 != d1);
    EXPECT_TRUE(d4 != d1);
    EXPECT_TRUE(d3 != d2);
    EXPECT_TRUE(d4 != d2);
    EXPECT_TRUE(d4 != d3);
}

TEST_F(DateWrapTests, addDays) {
    DateWrap d2 = *d + 1;
    DateWrap d3 = 2 + *d;
    DateWrap d4 = 30 + *d;
    DateWrap d5 = 45 + *d;
    DateWrap d6 = 60 + *d;
    DateWrap d7 = 360 + *d;

    EXPECT_THROW(*d + (-1), NegativeDays);
    EXPECT_THROW((-1) + *d, NegativeDays);

    EXPECT_EQ(d->day(), day); // not changed from exceptions or valid + operations
    EXPECT_EQ(d->month(), month);
    EXPECT_EQ(d->year(), year);

    EXPECT_EQ(d2.day(), day + 1);
    EXPECT_EQ(d2.month(), month);
    EXPECT_EQ(d2.year(), year);

    EXPECT_EQ(d3.day(), day + 2);
    EXPECT_EQ(d3.month(), month);
    EXPECT_EQ(d3.year(), year);

    EXPECT_EQ(d4.day(), day);
    EXPECT_EQ(d4.month(), month + 1);
    EXPECT_EQ(d4.year(), year);

    EXPECT_EQ(d5.day(), day + 15);
    EXPECT_EQ(d5.month(), month + 1);
    EXPECT_EQ(d5.year(), year);

    EXPECT_EQ(d6.day(), day);
    EXPECT_EQ(d6.month(), month + 2);
    EXPECT_EQ(d6.year(), year);

    EXPECT_EQ(d7.day(), day);
    EXPECT_EQ(d7.month(), month);
    EXPECT_EQ(d7.year(), year + 1);
}

TEST_F(DateWrapTests, print) {
    std::stringstream o;
    o << *d;
    EXPECT_EQ(o.str(), "1/1/1");
    DateWrap d2(27,11,2021);
    o.str(std::string());
    o << d2;
    EXPECT_EQ(o.str(), "27/11/2021");
}

TEST_F(DateWrapTests, incrementDays) {
    DateWrap dCopy = (*d)++;
    EXPECT_EQ(dCopy.day(), day);
    EXPECT_EQ(dCopy.month(), month);
    EXPECT_EQ(dCopy.year(), year);
    EXPECT_EQ(d->day(), day+1);
    EXPECT_EQ(d->month(), month);
    EXPECT_EQ(d->year(), year);

    DateWrap d2(30,1,1);
    d2++;
    EXPECT_EQ(d2.day(), 1);
    EXPECT_EQ(d2.month(), 2);
    EXPECT_EQ(d2.day(), 1);

    DateWrap d3(30,12,1);
    d3++;
    EXPECT_EQ(d3.day(), 1);
    EXPECT_EQ(d3.month(), 1);
    EXPECT_EQ(d3.year(), 2);

    EXPECT_THROW((*d) += -1, NegativeDays);
    EXPECT_EQ(d->day(), day+1); // not changed from exception
    EXPECT_EQ(d->month(), month);
    EXPECT_EQ(d->year(), year);

    EXPECT_NO_THROW((*d) += 0);
    EXPECT_EQ(d->day(), day+1); // not changed from adding 0
    EXPECT_EQ(d->month(), month);
    EXPECT_EQ(d->year(), year);

    DateWrap d5 = (*d) + 0;
    EXPECT_EQ(d5.day(), day+1); // just a copy
    EXPECT_EQ(d5.month(), month);
    EXPECT_EQ(d5.year(), year);

    d5++;
    EXPECT_NE(d5.day(),d->day()); // actually made a copy of d when added 0

    DateWrap d4(30,12,1);
    d4 += 1;
    EXPECT_EQ(d3.day(), 1);
    EXPECT_EQ(d3.month(), 1);
    EXPECT_EQ(d3.year(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}