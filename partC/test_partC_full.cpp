#include "gtest/gtest.h"
#include "date_wrap.h"
#include "exceptions.h"
#include "schedule.h"
#include "one_time_event.h"
#include "festival.h"
#include "recurring_event.h"
#include "open_event.h"
#include "closed_event.h"
#include "custom_event.h"
#include <fstream>
#include <iostream>

using namespace mtm;

class ScheduleTests : public ::testing::Test {

protected:
    Schedule *s;
    Schedule *s_filled;
    std::stringstream *string_out;
    std::ostream *out;
    string expected_events_out;
    string expected_events_out_verbose;
    DateWrap d1 = DateWrap(2,2,3);
    DateWrap d2 = DateWrap(16,6,3);
    DateWrap d3 = DateWrap(9,1,4);
    DateWrap d4 = DateWrap(9,2,4);
    DateWrap d5 = DateWrap(9,3,4);

    void SetUp() override {
        string_out = new std::stringstream;
//        out = &std::cout;
        out = string_out;
        s = new Schedule(out);
        s_filled = new Schedule(out);

        std::ifstream f("../outputs_full/events_out.txt");
        expected_events_out = string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        f.close();

        std::ifstream f2("../outputs_full/events_out_verbose.txt");
        expected_events_out_verbose = string((std::istreambuf_iterator<char>(f2)), std::istreambuf_iterator<char>());
        f2.close();

        addEvents(s_filled);
    }

    void TearDown() override {
        delete s;
        delete s_filled;
        delete string_out;
    }

    void addEvents(Schedule* s1) {
        // different events
        // events on the same day
        // events with the same name on different day
        auto ec1 = OneTimeEvent<OpenEvent>(d1,"event0");

        auto e1 = OpenEvent(d1, "event1");
        e1.registerParticipant(1);
        e1.registerParticipant(4);
        e1.registerParticipant(6);
        auto e3 = ClosedEvent(d1, "event3");
        e3.addInvitee(1);e3.registerParticipant(1);
        e3.addInvitee(2);e3.registerParticipant(2);
        e3.addInvitee(6);e3.registerParticipant(6);
        auto ec2 = Festival(d1);
        auto e2 = ClosedEvent(d1, "event2");
        e2.addInvitee(2);e2.registerParticipant(2);
        e2.addInvitee(4);e2.registerParticipant(4);
        e2.addInvitee(5);e2.registerParticipant(5);
        e2.addInvitee(7); // used in later tests
        ec2.add(e3);
        ec2.add(e1);
        ec2.add(e2);

        auto e5 = ClosedEvent(d1, "event5");
        e5.addInvitee(2);e5.registerParticipant(2);
        e5.addInvitee(4);e5.registerParticipant(4);
        e5.addInvitee(5);e5.registerParticipant(5);
        auto e4 = OpenEvent(d1, "event4");
        e4.registerParticipant(3);
        e4.registerParticipant(5);
        e4.registerParticipant(6);
        auto e6 = ClosedEvent(d1, "event6");
        e6.addInvitee(2);e6.registerParticipant(2);
        e6.addInvitee(4);e6.registerParticipant(4);
        e6.addInvitee(5);e6.registerParticipant(5);
        auto e7 = CustomEvent<bool (*)(int)>(d1, "event7", [](int){return true;});
        e7.registerParticipant(3);
        auto ec3 = Festival(d1);
        ec3.add(e4);
        ec3.add(e7);
        ec3.add(e5);
        ec3.add(e6);


        auto e9 = OpenEvent(d2, "event9");
        e9.registerParticipant(3);
        e9.registerParticipant(5);
        auto e8 = OpenEvent(d2, "event2"); // same name diff day
        e8.registerParticipant(3);
        auto e10 = CustomEvent<bool (*)(int)>(d2, "event10", [](int){return true;});
        e10.registerParticipant(1);
        e10.registerParticipant(2);
        e10.registerParticipant(4);
        auto ec4 = Festival(d2);
        ec4.add(e10);
        ec4.add(e8);
        ec4.add(e9);

        auto ec5 = OneTimeEvent<OpenEvent>(d3, "event11");
        auto ec6 = OneTimeEvent<OpenEvent>(d3, "event12");
        auto ec7 = OneTimeEvent<OpenEvent>(d4, "event13");
        auto ec8 = OneTimeEvent<OpenEvent>(d5, "event14");

        s1->addEvents(ec2);
        s1->addEvents(ec8);
        s1->addEvents(ec3);
        s1->addEvents(ec5);
        s1->addEvents(ec1);
        s1->addEvents(ec6);
        s1->addEvents(ec7);
        s1->addEvents(ec4);
    }
};

TEST_F(ScheduleTests, addEventsNormal) {
    addEvents(s);

    s->printAllEvents();
    EXPECT_EQ(string_out->str(), expected_events_out);
}
TEST_F(ScheduleTests, addDuplicateEvent) {
    auto d1 = DateWrap(2,2,3);
    auto e3 = OpenEvent(d1, "event20");
    auto e4 = OpenEvent(d1, "event4");
    auto ec3 = Festival(d1);
    ec3.add(e3);
    ec3.add(e4);

    EXPECT_THROW(s_filled->addEvents(ec3), EventAlreadyExists);
    s_filled->printAllEvents();
    EXPECT_EQ(string_out->str(), expected_events_out);
}
TEST_F(ScheduleTests, addDuplicateEvent2) {
    auto d1 = DateWrap(2,2,3);
    auto e3 = OpenEvent(d1, "event20");
    auto e4 = OpenEvent(d1, "event30");
    auto e4tag = OpenEvent(d1, "event30");
    auto ec3 = Festival(d1);
    ec3.add(e3);
    ec3.add(e4);
    ec3.add(e4tag);

    EXPECT_THROW(s_filled->addEvents(ec3), EventAlreadyExists);
    s_filled->printAllEvents();
    EXPECT_EQ(string_out->str(), expected_events_out);
}
TEST_F(ScheduleTests, addDuplicateEvent3) {
    auto d1 = DateWrap(2,2,3);
    auto e3 = OpenEvent(d1, "event20");
    auto e4 = OpenEvent(d1, "event30");
    auto e4tag = ClosedEvent(d1, "event30");
    auto ec3 = Festival(d1);
    ec3.add(e3);
    ec3.add(e4);
    ec3.add(e4tag);

    EXPECT_THROW(s_filled->addEvents(ec3), EventAlreadyExists);
    s_filled->printAllEvents();
    EXPECT_EQ(string_out->str(), expected_events_out);
}
TEST_F(ScheduleTests, registerToEventNormal) {
    EXPECT_NO_THROW(s_filled->registerToEvent(d2, "event2",1));
    s_filled->registerToEvent(d2, "event2", 5);
    s_filled->registerToEvent(d1, "event2", 7);
    s_filled->registerToEvent(d3,"event11",7);

    s_filled->printEventDetails(d2,"event2");
    s_filled->printEventDetails(d1,"event2");
    s_filled->printEventDetails(d3,"event11");

    EXPECT_EQ(string_out->str(), "event2 16/6/3\n"
                                 "1\n"
                                 "3\n"
                                 "5\n\n"
                                 "event2 2/2/3\n"
                                 "2\n"
                                 "4\n"
                                 "5\n"
                                 "7\n\n"
                                 "event11 9/1/4\n"
                                 "7\n\n"
                                 );
}
TEST_F(ScheduleTests, registerToEventAlreadyRegistered) {
    EXPECT_NO_THROW(s_filled->registerToEvent(d2, "event2",1));
    EXPECT_NO_THROW(s_filled->registerToEvent(d1, "event2", 7));
    EXPECT_THROW(s_filled->registerToEvent(d1, "event3", 2),AlreadyRegistered);
}
TEST_F(ScheduleTests, registerToEventRegistrationBlocked) {
    EXPECT_NO_THROW(s_filled->registerToEvent(d1, "event4", 7));
    EXPECT_NO_THROW(s_filled->registerToEvent(d4, "event13", 1));
    EXPECT_THROW(s_filled->registerToEvent(d1,"event5",8),RegistrationBlocked);
}
TEST_F(ScheduleTests, registerToEventDoesNotExist) {
    EXPECT_THROW(s_filled->registerToEvent(d2,"event20",2), EventDoesNotExist); // date exists, name doesnt
    EXPECT_THROW(s_filled->registerToEvent(DateWrap(5,5,5),"event1",3), EventDoesNotExist); // name exists, date doesnt
    EXPECT_THROW(s_filled->registerToEvent(d2,"event1",3), EventDoesNotExist); // name & date exist but not same
    EXPECT_THROW(s_filled->registerToEvent(DateWrap(5,5,5),"event20",3), EventDoesNotExist); // name & date does not exist
}
TEST_F(ScheduleTests, unregisterFromEventNormal) {
    EXPECT_NO_THROW(s_filled->unregisterFromEvent(d1,"event2",2));
    EXPECT_NO_THROW(s_filled->unregisterFromEvent(d1,"event4",5));
    EXPECT_NO_THROW(s_filled->unregisterFromEvent(d1,"event4",6));
    EXPECT_NO_THROW(s_filled->unregisterFromEvent(d2,"event9",5));
    EXPECT_NO_THROW(s_filled->unregisterFromEvent(d2,"event2",3));

    s_filled->printEventDetails(d1,"event2");
    s_filled->printEventDetails(d1,"event4");
    s_filled->printEventDetails(d2,"event9");
    s_filled->printEventDetails(d2,"event2");
    EXPECT_EQ(string_out->str(),"event2 2/2/3\n"
                                 "4\n"
                                 "5\n\n"
                                 "event4 2/2/3\n"
                                 "3\n\n"
                                 "event9 16/6/3\n"
                                 "3\n\n"
                                 "event2 16/6/3\n\n"
    );
}
TEST_F(ScheduleTests, unregisterFromEventNotRegistered) {
    EXPECT_THROW(s_filled->unregisterFromEvent(d1,"event2",10),NotRegistered);
}
TEST_F(ScheduleTests, unregisterFromEventDoesNotExist) {
    EXPECT_THROW(s_filled->unregisterFromEvent(d4,"event2",1),EventDoesNotExist);
    EXPECT_THROW(s_filled->unregisterFromEvent(d1,"event20",1),EventDoesNotExist);
    EXPECT_THROW(s_filled->unregisterFromEvent(DateWrap(5,5,5),"event1",1),EventDoesNotExist);
    EXPECT_THROW(s_filled->unregisterFromEvent(DateWrap(5,5,5),"event20",1),EventDoesNotExist);
}
TEST_F(ScheduleTests, printAllEventsNormal) {
    s_filled->printAllEvents();

    EXPECT_EQ(string_out->str(), expected_events_out);
}
TEST_F(ScheduleTests, printAllEventsNoEvents) {
    s->printAllEvents();

    EXPECT_EQ(string_out->str(), "");
}
TEST_F(ScheduleTests, printMonthEventsNormal) {
    // contain same month but diff year, same year diff month

    std::ifstream f("../outputs_full/events_out_month.txt");
    string expected_events_out_month = string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();

    s_filled->printMonthEvents(d2.month(),d2.year());
    EXPECT_EQ(string_out->str(), "event10 16/6/3\n\n"
                                 "event2 16/6/3\n\n"
                                 "event9 16/6/3\n\n");

    string_out->str(std::string());
    s_filled->printMonthEvents(d1.month(),d1.year());
    EXPECT_EQ(string_out->str(), "event0 2/2/3\n\n"
                                 "event1 2/2/3\n\n"
                                 "event2 2/2/3\n\n"
                                 "event3 2/2/3\n\n"
                                 "event4 2/2/3\n\n"
                                 "event5 2/2/3\n\n"
                                 "event6 2/2/3\n\n"
                                 "event7 2/2/3\n\n");

    string_out->str(std::string());
    s_filled->printMonthEvents(d4.month(),d4.year());
    EXPECT_EQ(string_out->str(), "event13 9/2/4\n\n");

    string_out->str(std::string());
    s_filled->printMonthEvents(d5.month(),d5.year());
    EXPECT_EQ(string_out->str(), "event14 9/3/4\n\n");

    string_out->str(std::string());
    s_filled->printMonthEvents(d3.month(),d3.year());
    EXPECT_EQ(string_out->str(), "event11 9/1/4\n\n"
                                 "event12 9/1/4\n\n");
}
TEST_F(ScheduleTests, printMonthEventsEventsEmpty) {
    EXPECT_NO_THROW(s->printMonthEvents(d1.month(),d1.year()));
    EXPECT_EQ(string_out->str(), "");
}
TEST_F(ScheduleTests, printMonthEventsNoEventsInMonth) {
    EXPECT_NO_THROW(s_filled->printMonthEvents(5,5));
    EXPECT_EQ(string_out->str(), "");
}
TEST_F(ScheduleTests, printMonthEventsInvalidDate) {
    EXPECT_THROW(s_filled->printMonthEvents(0,d1.year()), InvalidNumber);
    EXPECT_THROW(s_filled->printMonthEvents(-1,d1.year()), InvalidNumber);
    EXPECT_THROW(s_filled->printMonthEvents(13,d1.year()), InvalidNumber);
    EXPECT_NO_THROW(s_filled->printMonthEvents(1,d1.year()));
    EXPECT_NO_THROW(s_filled->printMonthEvents(12,d1.year()));
}
TEST_F(ScheduleTests, printSomeEventsNormal) {
    s_filled->printSomeEvents([](const BaseEvent& e) {
        return ((e.getDate() == DateWrap(9,1,4) && e.getName() == "event11")
                || (e.getDate() == DateWrap(2,2,3) && e.getName() == "event2")
                || (e.getDate() == DateWrap(2,2,3) && e.getName() == "event4")
                || (e.getDate() == DateWrap(16,6,3) && e.getName() == "event9")
                || (e.getDate() == DateWrap(5,5,5) && e.getName() == "event20") // no such event name or date
                || (e.getDate() == DateWrap(5,5,5) && e.getName() == "event1") // name exists, no such event date
                || (e.getDate() == DateWrap(16,6,3) && e.getName() == "event20") // date exists, no such name
                || (e.getDate() == DateWrap(16,6,3) && e.getName() == "event1") // date & name exist, not together
        );
    });
    EXPECT_EQ(string_out->str(), "event2 2/2/3\n\n"
                                 "event4 2/2/3\n\n"
                                 "event9 16/6/3\n\n"
                                 "event11 9/1/4\n\n");
}
TEST_F(ScheduleTests, printSomeEventsAllTruePredicate) {
    s_filled->printSomeEvents([](const BaseEvent& e) {return true;});
    EXPECT_EQ(string_out->str(), expected_events_out);
}
TEST_F(ScheduleTests, printSomeEventsAllFalsePredicate) {
    s_filled->printSomeEvents([](const BaseEvent& e) {return false;});
    EXPECT_EQ(string_out->str(), "");
}
TEST_F(ScheduleTests, printSomeEventsNormalVerbose) {
    s_filled->printSomeEvents([](const BaseEvent& e) {
        return ((e.getDate() == DateWrap(9,1,4) && e.getName() == "event11")
                || (e.getDate() == DateWrap(2,2,3) && e.getName() == "event2")
                || (e.getDate() == DateWrap(2,2,3) && e.getName() == "event4")
                || (e.getDate() == DateWrap(16,6,3) && e.getName() == "event9")
                || (e.getDate() == DateWrap(5,5,5) && e.getName() == "event20") // no such event name or date
                || (e.getDate() == DateWrap(5,5,5) && e.getName() == "event1") // name exists, no such event date
                || (e.getDate() == DateWrap(16,6,3) && e.getName() == "event20") // date exists, no such name
                || (e.getDate() == DateWrap(16,6,3) && e.getName() == "event1") // date & name exist, not together
        );
    }, true);
    EXPECT_EQ(string_out->str(), "event2 2/2/3\n"
                                 "2\n"
                                 "4\n"
                                 "5\n\n"
                                 "event4 2/2/3\n"
                                 "3\n"
                                 "5\n"
                                 "6\n\n"
                                 "event9 16/6/3\n"
                                 "3\n"
                                 "5\n\n"
                                 "event11 9/1/4\n\n");
}
TEST_F(ScheduleTests, printSomeEventsAllTruePredicateVerbose) {
    s_filled->printSomeEvents([](const BaseEvent& e) {return true;}, true);
    EXPECT_EQ(string_out->str(), expected_events_out_verbose);
}
TEST_F(ScheduleTests, printSomeEventsAllFalsePredicateVerbose) {
    s_filled->printSomeEvents([](const BaseEvent& e) {return false;});
    EXPECT_EQ(string_out->str(), "");
}
TEST_F(ScheduleTests, printEventDetailsNormal) {
    s_filled->printEventDetails(d4, "event13");
    EXPECT_EQ(string_out->str(), "event13 9/2/4\n\n");

    string_out->str(std::string());
    s_filled->printEventDetails(d1, "event3");
    EXPECT_EQ(string_out->str(), "event3 2/2/3\n"
                                 "1\n"
                                 "2\n"
                                 "6\n\n");

    string_out->str(std::string());
    s_filled->printEventDetails(d1, "event2");
    EXPECT_EQ(string_out->str(), "event2 2/2/3\n"
                                 "2\n"
                                 "4\n"
                                 "5\n\n");

    string_out->str(std::string());
    s_filled->printEventDetails(d2, "event2");
    EXPECT_EQ(string_out->str(), "event2 16/6/3\n"
                                 "3\n\n");


}
TEST_F(ScheduleTests, printEventDetailsDoesNotExist) {
    EXPECT_THROW(s_filled->printEventDetails(DateWrap(5,5,5),"event1"),EventDoesNotExist);
    EXPECT_THROW(s_filled->printEventDetails(DateWrap(5,5,5),"event20"),EventDoesNotExist);
    EXPECT_THROW(s_filled->printEventDetails(d1,"event20"),EventDoesNotExist);
    EXPECT_THROW(s_filled->printEventDetails(d1,"event9"),EventDoesNotExist);
}
TEST_F(ScheduleTests, sanity) {
    // make sure all works logically & everything memory-safe
    // add a lot from different containers, register, unregister, print all kinds of stuff.
    s_filled->unregisterFromEvent(d1,"event5",5);
    s_filled->unregisterFromEvent(d1,"event4",5);
    s_filled->registerToEvent(d1,"event4",1);
    auto e1 = OpenEvent(d5,"event6");
    e1.registerParticipant(1);
    e1.registerParticipant(500);
    e1.registerParticipant(80000);
    e1.registerParticipant(6);
    auto e2 = OpenEvent(d5,"event8");
    e2.registerParticipant(14);
    e2.registerParticipant(26);
    auto ec1 = Festival(d5);
    ec1.add(e1);
    ec1.add(e2);
    s_filled->addEvents(ec1);
    s_filled->addEvents(OneTimeEvent<OpenEvent>(d4,"event(-1)"));
    s_filled->registerToEvent(d5, "event8", 66);
    s_filled->unregisterFromEvent(d5, "event6", 1);

    auto *s2 = new Schedule();
    *s2 = *s_filled;
    s2->addEvents(OneTimeEvent<OpenEvent>(d3,"event100"));
    EXPECT_NO_THROW(s_filled->registerToEvent(d2, "event9", 4));
    EXPECT_NO_THROW(s2->registerToEvent(d2, "event9", 4));
    EXPECT_THROW(s2->registerToEvent(d2, "event9", 3), AlreadyRegistered);

    s_filled->unregisterFromEvent(d5,"event8", 26);
    s_filled->unregisterFromEvent(d2,"event2",3);
    s_filled->registerToEvent(d5, "event6", 234);
    s_filled->registerToEvent(d2, "event2", 5);
    delete s2;

    s_filled->unregisterFromEvent(d2,"event2",5);
    s_filled->registerToEvent(d2, "event2", 3);
    s_filled->unregisterFromEvent(d2,"event2", 3);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}