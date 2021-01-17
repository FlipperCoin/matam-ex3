#include "gtest/gtest.h"
#include "base_event.h"
#include "open_event.h"
#include <iostream>
#include "shared_pointer.h"
#include "open_event.h"

using namespace mtm;

static void a() {
    SharedPointer<BaseEvent> p(new OpenEvent(DateWrap(1,1,1),"lalala"));
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