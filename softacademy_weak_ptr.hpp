#ifndef SOFTACADEMY_WEAK_PTR_HPP
#define SOFTACADEMY_WEAK_PTR_HPP

#include "softacademy_shared_ptr.hpp"
#include <cstddef>
#include <utility>

namespace softacademy {

template <typename T> class SharedPtr;


template <typename T>
class WeakPtr {
public:
    WeakPtr() noexcept: ptr_(nullptr), control_(nullptr){}
    WeakPtr(const SharedPtr<T>& sp) noexcept : ptr_(sp.m_ptr), control_(sp.m_control) {
        inc_weak();
    }

    WeakPtr(const WeakPtr& other) noexcept : ptr_(other.ptr_), control_(other.control_) {
        inc_weak();
    }
    WeakPtr(WeakPtr&& other) noexcept: ptr_(other.ptr_), control_(other.control_) {
        other.ptr_ = nullptr;
        other.control_ = nullptr;
    }

    WeakPtr& operator=(const WeakPtr& other) noexcept {
        if (this != &other) {
            dec_weak();
            ptr_ = other.ptr_;
            control_ = other.control_;
            inc_weak();
        }
        return *this;
    }
    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            dec_weak();
            ptr_ = other.ptr_;
            control_ = other.control_;
            other.ptr_ = nullptr;
            other.control_ = nullptr;
        }
        return *this;
    }
    WeakPtr& operator=(const SharedPtr<T>& sp) noexcept {
        dec_weak();
        ptr_ = sp.m_ptr;
        control_ = sp.m_control;
        inc_weak();
        return *this;
    }

    ~WeakPtr() {
        dec_weak();
    }

    std::size_t use_count() const noexcept {
        return control_ ? control_->strong_count : 0;
    }
    bool expired() const noexcept {
        return use_count() == 0;
    }

    SharedPtr<T> lock() const noexcept {
        if (expired()) {
            return SharedPtr<T>();
        }
        return SharedPtr<T>(ptr_, control_);
    }

    void reset() noexcept {
        dec_weak();
        ptr_ = nullptr;
        control_ = nullptr;
    }
    void swap(WeakPtr& other) noexcept {
        std::swap(ptr_, other.ptr_); 
        std::swap(control_, other.control_); 
    }

private:
    T* ptr_;
    detail::ControlBlock* control_;

    void inc_weak() noexcept {
        if (control_) {
            control_->weak_count++;
        }
    }
    void dec_weak() noexcept {
        if (!control_) {
            return;
        }
        control_->weak_count--;
        if (control_->weak_count == 0 && control_->strong_count == 0) {
            delete control_;
        }
    }

    friend class SharedPtr<T>;
};

} // namespace softacademy

#endif
