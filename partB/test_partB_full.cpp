#include "gtest/gtest.h"
#include "base_event.h"
#include "open_event.h"
#include "festival.h"
#include <iostream>
#include "shared_pointer.h"
#include "custom_event.h"

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
//    DateWrap d(5,5,5);
//    Festival f(d);
//    OpenEvent e1(d, "1");
//    CustomEvent e2(d, "2", [](int){return true;});
//    ClosedEvent e3(d, "3");
//    f.add(OpenEvent)
}

TEST(BaseEventTests, test2) {
    b();
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}