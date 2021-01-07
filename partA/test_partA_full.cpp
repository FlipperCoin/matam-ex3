#include "gtest/gtest.h"
#include "date_wrap.h"

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}