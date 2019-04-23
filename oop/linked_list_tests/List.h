#include <functional>
#include <iostream>

#ifndef LIST_H
#define LIST_H

template <typename T>
class ListIterator;

template <typename T>
class List;

template <typename T>
class Node {
    friend class List<T>;
    friend class ListIterator<T>;

private:
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node();
    Node(const T&, Node<T>*, Node<T>*);
};

template <typename T>
Node<T>::Node() : prev{this}, next{this} {}

template <typename T>
Node<T>::Node(const T& data, Node<T>* prev, Node<T>* next) :
        data{data}, prev{prev}, next{next} {}

template <typename T>
class List {
    friend class ListIterator<T>;

public:
    List();
    List(const List&);
    ~List();
    List& operator=(const List& other);
    List(List&& other);
    List& operator=(List&& other);


    void add(const T& data);
    T& get(int position) const;
    void set(int position, const T& data);
    int size() const noexcept;

    ListIterator<T> begin();
    ListIterator<T> end();

private:
    void insert_before(Node<T>*, const T&);
    void push_back(const T&);
    Node<T>* node_at(int position) const;
    void for_each_node(std::function<void(Node<T>*)> fn) const;
    void empty();

    Node<T>* sentinel = new Node<T>();
    int size_;
};

template <typename T>
void List<T>::for_each_node(std::function<void(Node<T>*)> fn) const {
    Node<T>* node = sentinel->next;
    while (node != sentinel) {
        Node<T>* next = node->next;
        fn(node);
        node = next;
    }
}

template <typename T>
void List<T>::empty() {
    for_each_node([](Node<T>* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    });

    sentinel->prev = sentinel->next = sentinel;
    size_ = 0;
}

template <typename T>
void List<T>::insert_before(Node<T>* next, const T& data) {
    Node<T>* node = new Node<T>(data, next->prev, next);
    node->prev->next = node;
    node->next->prev = node;
    size_++;
}

template <typename T>
void List<T>::push_back(const T& data) {
    insert_before(sentinel, data);
}

template <typename T>
Node<T>* List<T>::node_at(int position) const {
    Node<T>* node = sentinel->next;
    int i = 0;
    while (i < position) {
        node = node->next;
        i++;
    }

    return node;
}

template<typename T>
List<T>::List() {
    empty();
}

template<typename T>
List<T>::List(const List<T>& other) {
    empty();

    other.for_each_node([&](const Node<T>* node) {
        push_back(node->data);
    });
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this == &other) {
        return *this;
    }

    empty();

    other.for_each_node([&](const Node<T>* node) {
        push_back(node->data);
    });

    return *this;
}

template<typename T>
List<T>::List(List&& other) {
    std::swap(sentinel, other.sentinel);
    std::swap(size_, other.size_);
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& other) {
    if (this == &other) {
        return *this;
    }

    std::swap(sentinel, other.sentinel);
    std::swap(size_, other.size_);

    return *this;
}

template<typename T>
List<T>::~List() {
    empty();
    delete sentinel;
}

template<typename T>
void List<T>::add(const T& data) {
    insert_before(sentinel, data);
}

template<typename T>
T& List<T>::get(int position) const {
    Node<T>* node = node_at(position);
    return node->data;
}

template<typename T>
void List<T>::set(int position, const T& data) {
    Node<T>* node = node_at(position);
    node->data = data;
}

template<typename T>
int List<T>::size() const noexcept {
    return size_;
}

template<typename T>
ListIterator<T> List<T>::begin() {
    return ListIterator<T>(*this);
}

template<typename T>
ListIterator<T> List<T>::end() {
    return ListIterator<T>(*this);
}

template<typename T>
class ListIterator {
public:
    ListIterator(const List<T>& list) noexcept;
    ListIterator(const List<T>& list, int position) noexcept;
    ListIterator& operator++();
    bool operator==(const ListIterator& other) noexcept;
    bool operator!=(const ListIterator& other) noexcept;
    T& operator*();

    bool valid()const;
    T& element() const;
    void next();

private:
    Node<T>* current;
    Node<T>* sentinel;
};

template<typename T>
ListIterator<T>::ListIterator(const List<T>& list) noexcept {
    sentinel = list.sentinel;
    current = sentinel->next;
}

template<typename T>
ListIterator<T>::ListIterator(const List<T>& list, int position) noexcept {
    current = list.node_at(position);
}

template<typename T>
bool ListIterator<T>::valid()const {
    return current == sentinel;
}

template<typename T>
T& ListIterator<T>::element() const {
    return current->data;
}

template<typename T>
void ListIterator<T>::next() {
    current = current->next;
}

template<typename T>
T& ListIterator<T>::operator*() {
    return element();
}

template<typename T>
ListIterator<T>& ListIterator<T>::operator++() {
    ListIterator<T>& old = *this;
    next();
    return old;
}

template<typename T>
bool ListIterator<T>::operator==(const ListIterator<T>& other) noexcept {
    return this->current == other.current;
}

template<typename T>
bool ListIterator<T>::operator!=(const ListIterator<T>& other)noexcept {
    return this->current != other.current;
}

#endif // LIST_H
