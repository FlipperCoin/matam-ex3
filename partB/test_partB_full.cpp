#include "gtest/gtest.h"
#include "base_event.h"
#include "open_event.h"
#include <iostream>

using namespace mtm;

TEST(BaseEventTests, test) {
    int students[] = {3, 4, 2};
    BaseEvent event(DateWrap(1,1,1), "event", students, 3);
//    EXPECT_NO_THROW(event.printLong(std::cout));
//    EXPECT_NO_THROW(event.registerParticipant(1));
//    EXPECT_NO_THROW(event.printLong(std::cout));
    EXPECT_NO_THROW(event.unregisterParticipant(2));
  EXPECT_NO_THROW(event.printLong(std::cout));
    OpenEvent open_event(DateWrap(1,1,1), "event", students, 3);
    open_event.registerParticipant((5));
    open_event.printLong(std::cout);
    event.printLong(std::cout);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}