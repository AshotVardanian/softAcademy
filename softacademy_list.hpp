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

        Node(const T& v, Node* p = nullptr, Node* n = nullptr);
        Node(T&& v, Node* p = nullptr, Node* n = nullptr);
    };

public:
    using value_type = T;
    using size_type  = std::size_t;

    LinkedList() noexcept;
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;
    LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(LinkedList&& other) noexcept;
    ~LinkedList();

    size_type size() const noexcept;
    bool empty() const noexcept;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void clear() noexcept;

    void push_front(const T& value);
    void push_front(T&& value);
    void push_back(const T& value);
    void push_back(T&& value);

    template <typename... Args>
    void emplace_front(Args&&... args);

    template <typename... Args>
    void emplace_back(Args&&... args);

    void pop_front();
    void pop_back();

    void swap(LinkedList& other) noexcept;

private:
    Node* head_;
    Node* tail_;
    size_type size_;

    void copy_from(const LinkedList& other);
    void move_from(LinkedList&& other) noexcept;
    void destroy_all() noexcept;
};

} // namespace softacademy

#endif
