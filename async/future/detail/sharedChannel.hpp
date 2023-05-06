#ifndef EXE_SHAREDCHANNEL_HPP
#define EXE_SHAREDCHANNEL_HPP


#include <optional>
#include <mutex>
#include <condition_variable>


namespace asynchronous::detail {

template <typename T>
class sharedChannel final {
public:
    void set(T value) {
        std::lock_guard lock(mutex);
        result.emplace(std::move(value));
        cv.notify_all();
    }

    T get() {
        std::unique_lock lock(mutex);

        cv.wait(lock, [&]() {
            return result.has_value();
        });

        return result.value();
    }

private:

    std::optional<T> result;
    std::mutex mutex;
    std::condition_variable cv;
};

}


#endif //EXE_SHAREDCHANNEL_HPP
