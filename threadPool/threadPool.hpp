#ifndef EXE_THREADPOOL_HPP
#define EXE_THREADPOOL_HPP


#include <functional>
#include <vector>
#include <thread>
#include <cassert>

#include "../sync/blockingQueue.hpp"
#include "detail/waitGroup.hpp"


namespace tp {

using Task = std::function<void()>;

class threadPool final {
public:
    explicit threadPool(std::int16_t size);
    ~threadPool();

    threadPool(const threadPool&) = delete;
    threadPool(threadPool&&) noexcept = delete;
    threadPool& operator=(const threadPool&) = delete;
    threadPool& operator=(threadPool&&) = delete;

    void start();
    void stop();

    void submit(Task&& task);
    void wait();

private:
    void routine();

    std::uint16_t size = 0;
    std::vector<std::thread> workers;
    synchronous::blockingQueue<Task> blockingBuffer;
    detail::waitGroup waitGroup;
};

}


#endif //EXE_THREADPOOL_HPP
