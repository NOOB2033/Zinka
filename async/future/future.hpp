#ifndef EXE_FUTURE_HPP
#define EXE_FUTURE_HPP


#include <memory>


#include "detail/sharedChannel.hpp"


namespace asynchronous {

template <typename T>
class future final {
public:
    explicit future(const std::shared_ptr<detail::sharedChannel<T>>& ptr)
        : channel_ptr(ptr)
    {}

    future(const future&) = delete;
    future& operator=(const future&) = delete;

    future(future&&) = default;
    future& operator=(future&&) = default;

    T get() {
        return channel_ptr.get()->get();
    }

private:
    std::shared_ptr<detail::sharedChannel<T>> channel_ptr;
};

}


#endif //EXE_FUTURE_HPP
