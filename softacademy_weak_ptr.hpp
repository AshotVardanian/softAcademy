#ifndef SOFTACADEMY_WEAK_PTR_HPP
#define SOFTACADEMY_WEAK_PTR_HPP

#include <cstddef>

namespace softacademy {

template <typename T> class SharedPtr;

namespace detail {
struct ControlBlock;
}

template <typename T>
class WeakPtr {
public:
    WeakPtr() noexcept;
    WeakPtr(const SharedPtr<T>& sp) noexcept;

    WeakPtr(const WeakPtr& other) noexcept;
    WeakPtr(WeakPtr&& other) noexcept;

    WeakPtr& operator=(const WeakPtr& other) noexcept;
    WeakPtr& operator=(WeakPtr&& other) noexcept;
    WeakPtr& operator=(const SharedPtr<T>& sp) noexcept;

    ~WeakPtr();

    std::size_t use_count() const noexcept;
    bool expired() const noexcept;

    SharedPtr<T> lock() const noexcept;

    void reset() noexcept;
    void swap(WeakPtr& other) noexcept;

private:
    T* ptr_;
    detail::ControlBlock* control_;

    void inc_weak() noexcept;
    void dec_weak() noexcept;

    friend class SharedPtr<T>;
};

} // namespace softacademy

#endif
