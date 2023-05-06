#ifndef EXE_BLOCKINGQUEUE_HPP
#define EXE_BLOCKINGQUEUE_HPP


#include <optional>
#include <deque>
#include <mutex>
#include <condition_variable>


namespace synchronous {

template <typename T>
class blockingQueue final {
public:
    void push(T&& value) {
        std::lock_guard lock(mutex);
        if (is_close) {
            return;
        }

        queue.push_back(std::move(value));
        cv.notify_all();
    }

    std::optional<T> pop() {
        std::unique_lock lock(mutex);
        cv.wait(lock, [&]() {
            return not queue.empty() or is_close;
        });

        if (queue.empty()) {
            return std::nullopt;
        }

        auto value = std::move(queue.front());
        queue.pop_front();
        return value;
    }

    void close() {
        std::lock_guard lock(mutex);
        is_close = true;
        cv.notify_all();
    }

    void cancel() {
        std::lock_guard lock(mutex);
        is_close = true;
        queue.clear();
        cv.notify_all();
    }

private:
    bool is_close = false;
    std::deque<T> queue;
    std::mutex mutex;
    std::condition_variable cv;
};

}


#endif //EXE_BLOCKINGQUEUE_HPP
