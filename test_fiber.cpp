#include <iostream>
#include "fiber.h"
#include "thread.h"

void run_in_fiber() {
    std::cout << "run_in_fiber begin";
    sylar::Fiber::YieldToHold();
    std::cout << "run_in_fiber end";
    sylar::Fiber::YieldToHold();
}

void test_fiber() {
    std::cout << "main begin -1" << std::endl;
    {
        sylar::Fiber::GetThis();
        std::cout << "main begin";
        sylar::Fiber::ptr fiber(new sylar::Fiber(run_in_fiber));
        fiber->swapIn();
        std::cout << "main after swapIn";
        fiber->swapIn();
        std::cout << "main after end";
        fiber->swapIn();
    }
    std::cout << "main after end2";
}

int main(int argc, char** argv) {
    sylar::Thread::SetName("main");

    std::vector<sylar::Thread::ptr> thrs;
    for(int i = 0; i < 2; ++i) {
        thrs.push_back(sylar::Thread::ptr(
                    new sylar::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    // for(auto i : thrs) {
    //     i->join();
    // }
    return 0;
}
