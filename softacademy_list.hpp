#ifndef SOFTACADEMY_LIST_HPP
#define SOFTACADEMY_LIST_HPP

#include <cstddef>
#include <utility>

namespace softacademy {

template <typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        Node(const T& v, Node* p = nullptr, Node* n = nullptr): value(v), prev(p), next(n){}
        Node(T&& v, Node* p = nullptr, Node* n = nullptr) : value(v), prev(p), next(n) {}
    };

public:
    using value_type = T;
    using size_type  = std::size_t;

    LinkedList() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}
    LinkedList(const LinkedList& other) : head_(nullptr), tail_(nullptr), size_(0) {
        copy_from(other);
    }
    LinkedList(LinkedList&& other) noexcept : head_(nullptr), tail_(nullptr), size_(0) {
        move_from(std::move(other));
    }
    LinkedList& operator=(const LinkedList& other){
        if (this != &other) {
            destroy_all();
            copy_from(other);
        }
        return *this;
    }
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            destroy_all();
            move_from(std::move(other));
        }
        return *this;
    }
    ~LinkedList() {
        destroy_all();
    }
    size_type size() const noexcept {
        return size_;
    }
    bool empty() const noexcept {
        return size_ == 0;
    }
    T& front() {
        if (!head_) { 
            throw std::out_of_range("LinkedList::front() on empty list"); 
        }
        return head_->value;
    }
    const T& front() const {
        if (!head_) {
            throw std::out_of_range("LinkedList::front() on empty list");
        }
        return head_->value;
    }
    T& back() {
        if (!tail_) {
            throw std::out_of_range("LinkedList::back() on empty list");
        }
        return tail_->value;
    }
    const T& back() const {
        if (!tail_) {
            throw std::out_of_range("LinkedList::back() on empty list");
        }
        return tail_->value; 
    }

    void clear() noexcept {
        destroy_all();
    }

    void push_front(const T& value) {
        Node* node = new Node(value, nullptr, head_);
        if (head_) { 
            head_->prev = node; 
        }
        head_ = node;
        if (!tail_) {
            tail_ = node; 
        }
        ++size_;
    }
    void push_front(T&& value) {
        Node* node = new Node(std::move(value), nullptr, head_);
        if (head_) { 
            head_->prev = node; 
        }
        head_ = node;
        if (!tail_) { 
            tail_ = node; 
        }
        ++size_;
    }
    void push_back(const T& value) {
        Node* node = new Node(value, tail_, nullptr);
        if (tail_) { 
            tail_->next = node; 
        }
        tail_ = node;
        if (!head_) { 
            head_ = node;
        }
        ++size_;
    }
    void push_back(T&& value) {
        Node* node = new Node(std::move(value), tail_, nullptr);
        if (tail_) tail_->next = node;
        tail_ = node;
        if (!head_) head_ = node;
        ++size_;
    }
    template <typename... Args>
    void emplace_front(Args&&... args) {
        Node* node = new Node(T(std::forward<Args>(args)...), nullptr, head_);
        if (head_) head_->prev = node;
        head_ = node;
        if (!tail_) tail_ = node;
        ++size_;
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        Node* node = new Node(T(std::forward<Args>(args)...), tail_, nullptr);
        if (tail_) tail_->next = node;
        tail_ = node;
        if (!head_) head_ = node;
        ++size_;
    }

    void pop_front() {
        if (!head_) {
            throw std::out_of_range("LinkedList::pop_front() on empty list");
        }
        Node* tmp = head_;
        head_ = head_->next;
        if (head_) { 
            head_->prev = nullptr; 
        }
        else { 
            tail_ = nullptr; 
        }
        delete tmp;
        --size_;
    }
    void pop_back() {
        if (!tail_) { 
            throw std::out_of_range("LinkedList::pop_back() on empty list");
        }
        Node* tmp = tail_;
        tail_ = tail_->prev;
        if (tail_) { 
            tail_->next = nullptr; 
        }
        else { 
            head_ = nullptr; 
        }
        delete tmp;
        --size_;
    }

    void swap(LinkedList& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

private:
    Node* head_;
    Node* tail_;
    size_type size_;

    void copy_from(const LinkedList& other) {
        Node* current = other.head_;
        while (current) {
            push_back(current->value);
            current = current->next;
        }
    }
    void move_from(LinkedList&& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    void destroy_all() noexcept {
        Node* current = head_;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }
};

} // namespace softacademy

#endif
