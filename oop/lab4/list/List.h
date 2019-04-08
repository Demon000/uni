#include <functional>
#include <stdexcept>
#include <iostream>

#ifndef LIST_H
#define LIST_H

template <typename T>
class List;

template <typename T>
class Node {
    friend class List<T>;

private:
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node();
    Node(const T&, Node<T>*, Node<T>*);
};

template <typename T>
class List {
public:
    List();
    List(const List&);
    ~List();
    T& operator[](int);
    List<T>& operator=(const List<T>&);

    /**
     * Get the size of the list.
     *
     * @return The size of the list.
     */
    int size() const;

    /**
     * Add a new element to the list.
     *
     * @param The new element.
     */
    void push_back(const T&);

    /**
     * Sort the elements of the list.
     *
     * @param cmp A comparator function.
     */
    void sort(std::function<bool(const T&, const T&)>);

    /**
     * Go over the elements of the list.
     *
     * @param fn A function to be called for each element of the list.
     *
     * @return Whether the list has been iterated until the end or not.
     */
    bool for_each(std::function<bool(T&)>);
    bool for_each(std::function<bool(const T&)>) const;

    /**
     * Remove an element from the list.
     *
     * @param position The index of the element to remove.
     */
    void remove(int);

    /**
     * Empty the list.
     */
    void empty();

private:
    void insert_before(Node<T>*, const T&);
    void swap_data(Node<T>* first, Node<T>* second);
    Node<T>* node_at(int position);

    Node<T>* sentinel;
    int size_;
};

template <typename T>
Node<T>::Node() {
    prev = this;
    next = this;
}

template <typename T>
Node<T>::Node(const T& data, Node<T>* prev, Node<T>* next) :
        data{data}, prev{prev}, next{next} {}

template <typename T>
List<T>::List() {
    sentinel = new Node<T>();
    size_ = 0;
}

template <typename T>
List<T>::List(const List& other) {
    other.for_each([&](const T& data) {
        push_back(data);
        return false;
    });
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this == &other) {
        return *this;
    }

    empty();
    other.for_each([&](const T& data) {
        push_back(data);
        return false;
    });


    return *this;
}

template <typename T>
void List<T>::empty() {
    Node<T>* node = sentinel->next;
    Node<T>* temp;
    while (node != sentinel) {
        temp = node->next;
        delete node;
        node = temp;
    }

    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    size_ = 0;
}

template <typename T>
List<T>::~List() {
    empty();
    delete sentinel;
}

template <typename T>
int List<T>::size() const {
    return size_;
}

template <typename T>
void List<T>::insert_before(Node<T>* next, const T& data) {
    Node<T>* node = new Node<T>(data, next->prev, next);
    next->prev->next = node;
    next->prev = node;
    size_++;
}

template <typename T>
void List<T>::push_back(const T& data) {
    insert_before(sentinel, data);
}

template <typename T>
void List<T>::swap_data(Node<T>* first, Node<T>* second) {
    T temp_data = first->data;
    first->data = second->data;
    second->data = temp_data;
}

template <typename T>
void List<T>::sort(std::function<bool(const T&, const T&)> cmp) {
    Node<T>* first = sentinel->next;

    while (first != sentinel) {
        Node<T>* second = first->next;

        while (second != sentinel) {
            if (!cmp(first->data, second->data)) {
                swap_data(first, second);
            }

            second = second->next;
        }

        first = first->next;
    }
}

template <typename T>
Node<T>* List<T>::node_at(int position) {
    Node<T>* node = sentinel->next;
    int i = 0;
    while (i < position) {
        node = node->next;
        i++;
    }

    return node;
}

template <typename T>
T& List<T>::operator[](int position) {
    Node<T>* node = node_at(position);
    return node->data;
}

template <typename T>
void List<T>::remove(int position) {
    Node<T>* node = node_at(position);
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

template <typename T>
bool List<T>::for_each(std::function<bool(const T&)> fn) const {
    Node<T>* node = sentinel->next;
    while (node != sentinel) {
        bool done = fn(node->data);
        if (done) {
            return true;
        }

        node = node->next;
    }

    return false;
}

template <typename T>
bool List<T>::for_each(std::function<bool(T&)> fn) {
    Node<T>* node = sentinel->next;
    while (node != sentinel) {
        bool done = fn(node->data);
        if (done) {
            return true;
        }

        node = node->next;
    }

    return false;
}

#endif // LIST_H
