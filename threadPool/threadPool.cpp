#include "threadPool.hpp"


namespace tp {

threadPool::threadPool(std::int16_t size) {
    assert(size >= 0);

    this->size = size;
}

threadPool::~threadPool() {
    assert(workers.empty());
}

void threadPool::start() {
    for (std::uint16_t i = 0; i < size; ++i) {
        workers.emplace_back([this]() {
            routine();
        });
    }
}

void threadPool::stop() {
    blockingBuffer.cancel();
    for (auto&& worker : workers) {
        worker.join();
    }
    workers.clear();
}

void threadPool::submit(Task&& task) {
    waitGroup.inc();
    blockingBuffer.push(std::move(task));
}

void threadPool::wait() {
    waitGroup.wait();
}

void threadPool::routine() {
    while (true) {
        auto task = blockingBuffer.pop();
        if (task.has_value()) {
            try {
                task.value()();
            }
            catch (...) {}
            waitGroup.dec();
        } else {
            break;
        }
    }
}

}
