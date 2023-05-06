#ifndef EXE_WAITGROUP_HPP
#define EXE_WAITGROUP_HPP


#include <mutex>
#include <condition_variable>


namespace tp::detail {

class waitGroup final {
public:
    void inc();

    void dec();

    void wait();

private:
    std::uint64_t counter = 0;
    std::mutex mutex;
    std::condition_variable cv;
};

}


#endif //EXE_WAITGROUP_HPP
