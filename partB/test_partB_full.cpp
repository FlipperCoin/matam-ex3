#include "gtest/gtest.h"
#include "base_event.h"
#include "open_event.h"
#include "festival.h"
#include <iostream>
#include "shared_pointer.h"
#include "custom_event.h"
#include "closed_event.h"
#include "recurring_event.h"
#include "one_time_event.h"
#include "algorithm"

using namespace mtm;

static void a() {
    SharedPointer<BaseEvent> p;
    p = SharedPointer<BaseEvent>(new OpenEvent(DateWrap(1,1,1),"lalala"));
    std::cout << p->getName() << std::endl;
    std::cout << (*p).getDate() << std::endl;
    auto c = p;
    auto d = c;
    auto e = c;
    auto f = p;
}



TEST(BaseEventTests, test) {
    a();
}

void c() {

}

void b() {
    DateWrap d(5,5,5);
    Festival f(d);
    OpenEvent e1(d, "1");
//    CustomEvent e2(d, "2", [](int){return true;});
//    ClosedEvent e3(d, "3");
//    f.add(OpenEvent)
}

TEST(BaseEventTests, test2) {
    b();
}


TEST(BaseEventTests, test3) {
    CustomEvent<bool (*)(int)> e(DateWrap(5,5,5),"1",[](int s){return s != 3;});
    e.registerParticipant(1);
    e.registerParticipant(2);

    auto e2 = e;
    e.registerParticipant(4);

    CustomEvent<bool (*)(int)> e3(DateWrap(6,5,5),"3",[](int s){return s != 5;});
    e3.registerParticipant(3);

    EXPECT_THROW(e2.registerParticipant(1), AlreadyRegistered);
    EXPECT_THROW(e2.registerParticipant(3), RegistrationBlocked);
    EXPECT_NO_THROW(e2.registerParticipant(4));

    e3 = e2;
    EXPECT_THROW(e3.registerParticipant(1), AlreadyRegistered);
    EXPECT_THROW(e3.registerParticipant(4), AlreadyRegistered);
    EXPECT_NO_THROW(e3.registerParticipant(5));
    EXPECT_THROW(e3.registerParticipant(3), RegistrationBlocked);

    EXPECT_EQ(e3.getDate(), DateWrap(5,5,5));
    EXPECT_EQ(e3.getName(), "1");
    EXPECT_EQ(e2.getDate(), DateWrap(5,5,5));
    EXPECT_EQ(e2.getName(), "1");
}
TEST(BaseEventTests, test4) {
    ClosedEvent e(DateWrap(5,5,5),"1");
    e.addInvitee(1);
    e.addInvitee(2);
    e.registerParticipant(1);
    e.registerParticipant(2);

    auto e2 = e;
    e.addInvitee(4);

    ClosedEvent e3(DateWrap(6,5,5),"3");
    e3.addInvitee(3);
    e3.registerParticipant(3);

    EXPECT_THROW(e2.registerParticipant(1), AlreadyRegistered);
    EXPECT_THROW(e2.registerParticipant(3), RegistrationBlocked);
    EXPECT_THROW(e2.registerParticipant(4), RegistrationBlocked);

    e2.addInvitee(4);
    e3 = e2;
    EXPECT_THROW(e2.registerParticipant(1), AlreadyRegistered);
    EXPECT_NO_THROW(e2.registerParticipant(4));
    EXPECT_THROW(e2.registerParticipant(3), RegistrationBlocked);

    EXPECT_EQ(e3.getDate(), DateWrap(5,5,5));
    EXPECT_EQ(e3.getName(), "1");
    EXPECT_EQ(e2.getDate(), DateWrap(5,5,5));
    EXPECT_EQ(e2.getName(), "1");
}
TEST(BaseEventTests, test5) {
    DateWrap d1 = DateWrap(2,2,3);
    DateWrap d2 = DateWrap(16,6,3);
    DateWrap d3 = DateWrap(9,1,4);
    DateWrap d4 = DateWrap(9,2,4);
    DateWrap d5 = DateWrap(9,3,4);

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

    auto ec9 = RecurringEvent<OpenEvent>(d1, "event_recur1", 5, 4);
    auto ec10 = RecurringEvent<OpenEvent>(d2, "event_recur2", 4, 7);

    // festival copy and assignment
    auto ec2_copy = ec2;
    ec2.add(OpenEvent(d1,"a"));
    for (auto i = ec2_copy.begin(); i != ec2_copy.end(); ++i) {
        ASSERT_NE((*i).getName(),"a");
    }
    EXPECT_NO_THROW(ec2_copy.add(OpenEvent(d1,"a")););
    EXPECT_NO_THROW(ec2_copy.add(OpenEvent(d1, "event1")));
    EXPECT_THROW(ec2_copy.add(OpenEvent(d2,"b")),DateMismatch);
    EXPECT_NO_THROW(ec2.add(OpenEvent(d1,"a")));
    auto ec3_copy = ec3;
    auto ec10_copy = ec10;
    ec3 = ec2;
    auto j1 = ec3.begin();
    for (auto i = ec2.begin(); i != ec2.end(); ++i,++j1) {
        ASSERT_EQ(*i,*j1);
        ASSERT_NE(&i,&j1);
        ASSERT_NE(&(*i),&(*j1));
    }
    EXPECT_NO_THROW(ec3.add(OpenEvent(d1,"b")););
    EXPECT_NO_THROW(ec3.add(OpenEvent(d1, "event1")));
    EXPECT_THROW(ec3.add(OpenEvent(d2,"b")),DateMismatch);
    EXPECT_NO_THROW(ec2.add(OpenEvent(d1,"b")));
    ec2 = ec3;
    ec4 = ec2;

    // recurring copy and assignment
    auto ec9_copy = ec9;
    auto j = ec9.begin();
    for (auto i = ec9_copy.begin(); i != ec9_copy.end(); ++i,++j) {
        ASSERT_EQ(*i,*j);
        ASSERT_NE(&i,&j);
        ASSERT_NE(&(*i),&(*j));
    }
    ec9 = ec10;
    auto t = ec10.begin();
    for (auto i = ec9.begin(); i != ec9.end(); ++i,++t) {
        ASSERT_EQ(*i,*t);
        ASSERT_NE(&i,&t);
        ASSERT_NE(&(*i),&(*t));
    }

    // one time copy and assignment
    auto ec6_copy = ec6;
    auto t1 = ec6_copy.begin();
    for (auto i = ec6.begin(); i != ec6.end(); ++i,++t1) {
        ASSERT_EQ(*i,*t1);
        ASSERT_NE(&i,&t1);
        ASSERT_NE(&(*i),&(*t1));
    }

    ec7 = ec6;
    ec8 = ec5;

    // virtual destructor
    EventContainer* arr[3] = {
            new Festival(ec2),
            new RecurringEvent<OpenEvent>(ec9),
            new OneTimeEvent<OpenEvent>(ec6)
    };
    for (auto & i : arr) {
        delete i;
    }
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}