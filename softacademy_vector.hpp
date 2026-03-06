#ifndef SOFTACADEMY_VECTOR_HPP
#define SOFTACADEMY_VECTOR_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>

namespace softacademy {

template <typename T>
class Vector {
public:
    using value_type = T;
    using size_type  = std::size_t;

    Vector() noexcept : size_(0), capacity_(0), data_(nullptr){}
    explicit Vector(size_type count) : size_(count), capacity_(0) {
        while (capacity_ < size_) {
            if (capacity_ == 0) {
                capacity_++;
                continue;
            }
            capacity_ *= 2;
        }
        data_ = new T[capacity_];
    }
    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (size_type i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        size_ = other.size_; 
        capacity_ = other.capacity_; 
        data_ = new T[capacity_];
        for (size_type i = 0; i < size_;i++) {
            data_[i] = other.data_[i];
        }
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    ~Vector() {
        delete[] data_;
    }
    size_type size() const noexcept {
        return size_;
    }
    size_type capacity() const noexcept {
        return capacity_;
    }
    bool empty() const noexcept {
        return size_ == 0;
    }
    void reserve(size_type new_cap) {
        if (capacity_ >= new_cap) {
            return;
        }
        T* tmp = new T[new_cap];
        for (size_type i = 0; i < size_; i++) {
            tmp[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = tmp;
        tmp = nullptr;
        capacity_ = new_cap;
    }
    void shrink_to_fit() {
        if (capacity_ == size_ ) {
            return;
        }
        if (size_ == 0) {
            delete[] data_;
            data_ = nullptr;
            capacity_ = 0;
            return;
        }
        T* new_data = new T[size_];
        for (size_type i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = size_;
    }
    T& operator[](size_type index) noexcept {
        return data_[index];
    }
    const T& operator[](size_type index) const noexcept {
        return data_[index];
    }
    T& at(size_type index) {
        if (index >= size_)
            throw std::out_of_range("Vector::at index out of range");
        return data_[index];
    }
    const T& at(size_type index) const {
        if (index >= size_)
            throw std::out_of_range("Vector::at index out of range");
        return data_[index];
    }

    T& front() {
        if (size_ == 0) {
            throw std::out_of_range("Vector::front() called on empty vector");
        }
        return data_[0];
    }
    const T& front() const {
        if (size_ == 0) {
            throw std::out_of_range("Vector::front() called on empty vector");
        }
        return data_[0];
    }
    T& back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector::back() called on empty vector");
        }
        return data_[size_ - 1];
    }
    const T& back() const {
        if (size_ == 0) {
            throw std::out_of_range("Vector::back() called on empty vector");
        }
        return data_[size_ - 1];
    }

    T* data() noexcept {
        return data_;
    }
    const T* data() const noexcept {
        return data_;
    }

    void clear() noexcept {
        size_ = 0;
    }
    void push_back(const T& value) {
        grow_if_needed();
        data_[size_] = value;
        size_++;
    }
    void push_back(T&& value) {
        grow_if_needed();
        data_[size_] = std::move(value);
        size_++;
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        grow_if_needed();
        data_[size_] = T(std::forward<Args>(args)...);
        return data_[size_++];
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector::pop_back() called on empty vector");
        }
        size_--;
    }
    void resize(size_type new_size) {
        if (new_size > capacity_) {
            reallocate(new_size);
        }

        if (new_size > size_) {
            for (size_type i = size_; i < new_size; ++i) {
                data_[i] = T();
            }
        }
        size_ = new_size;
    }
    void resize(size_type new_size, const T& value) {
        if (new_size > capacity_) {
            reallocate(new_size);
        }
        if (new_size > size_) {
            for (size_type i = size_; i < new_size; ++i) {
                data_[i] = value;
            }
        }
        size_ = new_size;
    }

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

private:
    size_type size_;
    size_type capacity_;
    T* data_;
    void grow_if_needed() {
        if (size_ == capacity_) {
            size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
    }
    void reallocate(size_type new_capacity) {
        T* new_data = new T[new_capacity];

        for (size_type i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
};

} // namespace softacademy

#endif
