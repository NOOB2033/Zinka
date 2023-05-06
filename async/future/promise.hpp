#ifndef EXE_PROMISE_HPP
#define EXE_PROMISE_HPP


#include "future.hpp"


namespace asynchronous {

template <typename T>
class promise final {
public:
    promise() {
        channel_ptr = std::make_shared<detail::sharedChannel<T>>();
    }

    promise(const promise&) = delete;
    promise& operator=(const promise&) = delete;

    promise(promise&&) = default;
    promise& operator=(promise&&) = default;


    void setValue(T value) {
        channel_ptr.get()->set(std::move(value));
    }

    future<T> getFuture() {
        return future<T>(channel_ptr);
    }

private:
    std::shared_ptr<detail::sharedChannel<T>> channel_ptr;
};

}


#endif //EXE_PROMISE_HPP
