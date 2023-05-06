#include "waitGroup.hpp"


namespace tp::detail {

void waitGroup::inc() {
    std::lock_guard lock(mutex);
    ++counter;
}

void waitGroup::dec() {
    std::lock_guard lock(mutex);
    if (--counter == 0) {
        cv.notify_all();
    }
}

void waitGroup::wait() {
    std::unique_lock lock(mutex);
    cv.wait(lock, [&]() {
        return counter == 0;
    });
}

}
