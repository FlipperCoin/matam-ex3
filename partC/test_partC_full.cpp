#include "gtest/gtest.h"
#include "date_wrap.h"
#include "exceptions.h"
#include "schedule.h"

using namespace mtm;

class ScheduleTests : public ::testing::Test {

protected:
    Schedule *s;
    std::stringstream *out;

    void SetUp() override {
        out = new std::stringstream;
        s = new Schedule(out);
    }

    void TearDown() override {
        delete s;
    }
};

// TODO: Should check input validity of date / student / event name?

TEST_F(ScheduleTests, addEventsNormal) {
    // different events
    // events on the same day
    // events with the same name on different day
}
TEST_F(ScheduleTests, addDuplicateEvent) {
    // add different events and then a container with a duplicate from previous events
    // make sure schedule stayed the same
}
TEST_F(ScheduleTests, addDuplicateEvent2) {
    // if possible: add different events and then a container with a duplicate in the same container
    // make sure schedule stayed the same
}
TEST_F(ScheduleTests, sanity) {
    // make sure all works logically & everything memory-safe
    // add a lot from different containers, register, unregister, print all kinds of stuff.
}
TEST_F(ScheduleTests, registerToEventNormal) {

}
TEST_F(ScheduleTests, registerToEventAlreadyRegistered) {

}
TEST_F(ScheduleTests, registerToEventRegistrationBlocked) {

}
TEST_F(ScheduleTests, registerToEventDoesNotExist) {

}
TEST_F(ScheduleTests, unregisterFromEventNormal) {

}
TEST_F(ScheduleTests, unregisterFromEventNotRegistered) {

}
TEST_F(ScheduleTests, unregisterFromEventDoesNotExist) {

}
TEST_F(ScheduleTests, printAllEventsNormal) {

}
TEST_F(ScheduleTests, printAllEventsNoEvents) {

}
TEST_F(ScheduleTests, printMonthEventsNormal) {
    // contain same month but diff year, same year diff month
}
TEST_F(ScheduleTests, printMonthEventsEventsEmpty) {

}
TEST_F(ScheduleTests, printMonthEventsNoEventsInMonth) {

}
TEST_F(ScheduleTests, printMonthEventsInvalidDate) {

}
bool predicate(const BaseEvent& event) {
    return true;
}
TEST_F(ScheduleTests, printSomeEventsNormal) {
    s->printSomeEvents([](const BaseEvent& e) {return true;});
    s->printSomeEvents(predicate);
}
TEST_F(ScheduleTests, printSomeEventsAllTruePredicate) {

}
TEST_F(ScheduleTests, printSomeEventsAllFalsePredicate) {

}
TEST_F(ScheduleTests, printSomeEventsNormalVerbose) {

}
TEST_F(ScheduleTests, printSomeEventsAllTruePredicateVerbose) {

}
TEST_F(ScheduleTests, printSomeEventsAllFalsePredicateVerbose) {

}
TEST_F(ScheduleTests, printEventDetailsNormal) {

}
TEST_F(ScheduleTests, printEventDetailsDoesNotExist) {

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}