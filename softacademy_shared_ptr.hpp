#ifndef SOFTACADEMY_SHARED_PTR_HPP
#define SOFTACADEMY_SHARED_PTR_HPP

#include <cstddef>
#include <utility>

namespace softacademy {

template <typename T> class WeakPtr;

namespace detail {

struct ControlBlock {
    std::size_t strong_count;
    std::size_t weak_count;
    void* ptr;
    void (*deleter)(void*);

    ControlBlock(void* p, void (*d)(void*));
};

template <typename U>
void default_delete(void* p) {
    delete static_cast<U*>(p);
}

} // namespace detail

template <typename T>
class SharedPtr {
public:
    using element_type = T;

    SharedPtr() noexcept;
    explicit SharedPtr(T* ptr);

    SharedPtr(const SharedPtr& other) noexcept;
    SharedPtr(SharedPtr&& other) noexcept;

    SharedPtr& operator=(const SharedPtr& other) noexcept;
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    ~SharedPtr();

    T* get() const noexcept;
    T& operator*() const;
    T* operator->() const noexcept;

    std::size_t use_count() const noexcept;
    explicit operator bool() const noexcept;

    void reset() noexcept;
    void reset(T* ptr);

    void swap(SharedPtr& other) noexcept;

private:
    T* ptr_;
    detail::ControlBlock* control_;

    void inc_strong() noexcept;
    void dec_strong() noexcept;

    friend class WeakPtr<T>;
};

} // namespace softacademy

#endif
