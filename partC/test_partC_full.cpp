#include "gtest/gtest.h"
#include "date_wrap.h"
#include "exceptions.h"

using namespace mtm;

class ScheduleTests : public ::testing::Test {

protected:

    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(ScheduleTests, test) {

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}