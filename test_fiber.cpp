#include <iostream>
#include "fiber.h"
#include "thread.h"
#include "scheduler.h"

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
        std::cout << "main begin" << std::endl;
        sylar::Fiber::ptr fiber(new sylar::Fiber(run_in_fiber));
        fiber->swapIn();
        std::cout << "main after swapIn" << std::endl;
        fiber->swapIn();
        std::cout << "main after end" << std::endl;
        fiber->swapIn();
    }
    std::cout << "main after end2" << std::endl;
}

int main(int argc, char** argv) {
    sylar::Scheduler sc(3, false, "test");
    sc.start();
    sc.schedule(&test_fiber);
    sc.stop();
    return 0;
}
