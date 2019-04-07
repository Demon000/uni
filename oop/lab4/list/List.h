#ifndef LIST_H
#define LIST_H

template <typename T>
class Node {
    friend class List;

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
    ~List();

    void push_back(const T&);
    void push_front(const T&);

private:
    void insert_before(Node<T>*, const T&);
    void swap_data(Node<T>* first, Node<T>* second);

    Node<T>* sentinel;
    int size;
};

#endif // LIST_H
