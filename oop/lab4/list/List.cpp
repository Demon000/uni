#include "List.h"

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
    size = 0;
}

template <typename T>
List<T>::~List() {
    Node<T>* node = sentinel->next;
    Node<T>* temp;
    while (node != sentinel) {
        temp = node->next;
        delete node;
        node = temp;
    }

    sentinel->prev = sentinel;
    sentinel->next = sentinel;
}

template <typename T>
void List<T>::insert_before(Node<T>* next, const T& data) {
    Node<T>* node = new Node<T>(data, next->prev, next);
    next->prev->next = node;
    next->prev = node;
}

template <typename T>
void List<T>::swap_data(Node<T>* first, Node<T>* second) {
    T temp = first->data;
    first->data = second->data;
    second->data = temp;
}

template <typename T>
void List<T>::push_back(const T& data) {
    insert_before(sentinel, data);
}

template <typename T>
void List<T>::push_front(const T& data) {
    insert_before(sentinel->next, data);
}
