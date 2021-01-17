#include "gtest/gtest.h"
#include "base_event.h"
#include "open_event.h"
#include <iostream>
#include "shared_pointer.h"

using namespace mtm;

static void a() {
    // TODO: check because added empty constructor
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}