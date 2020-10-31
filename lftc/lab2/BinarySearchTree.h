#ifndef LAB2_BINARYSEARCHTREE_H
#define LAB2_BINARYSEARCHTREE_H

#include <memory>

template <typename T>
class Node {
public:
    Node<T> *smallest() {
        Node<T>* next = this;
        while (next->left != nullptr) {
            next = next->left;
        }

        return next;
    }

    Node<T> *next() {
        if (right != nullptr) {
            return right->smallest();
        }

        Node<T> *next = this;
        while (next->parent != nullptr
               && next == next->parent->right) {
            next = next->parent;
        }

        return next->parent;
    }

    T data;
    int index = 0;
    Node<T>* parent = nullptr;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
};

template <typename T>
class BinarySearchTree {
public:
    ~BinarySearchTree() {
        root = destroyNode(root);
    }

    int length() {
        return length_;
    }

    Node<T>* insertNode(const T& data, bool unique=false) {
        Node<T> *added;
        root = insert(nullptr, root, &added, data, unique);
        return added;
    }

    std::vector<T> linear() {
        std::vector<T> items;

        Node<T> *current = nullptr;
        if (root != nullptr) {
            current = root->smallest();
        }

        while (current != nullptr) {
            items.push_back(current->data);
            current = current->next();
        }

        return items;
    }

private:
    struct Node<T> *root = nullptr;
    int length_ = 0;

    Node<T>* destroyNode(Node<T> *node) {
        if (node == nullptr) {
            return nullptr;
        }

        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
        length_--;
        return nullptr;
    }

    Node<T>* createNode() {
        return new Node<T>();
    }

    Node<T>* insert(Node<T> *parent, Node<T> *node, Node<T> **added, const T& data, bool unique) {
        if (node == nullptr) {
            node = createNode();
            node->data = data;
            node->parent = parent;
            node->index = length_;
            *added = node;
            length_++;
        } else if (data < node->data) {
            node->left = insert(node, node->left, added, data, unique);
        } else if (data == node->data && unique) {
            *added = node;
        } else if (data >= node->data) {
            node->right = insert(node, node->right, added, data, unique);
        }

        return node;
    }
};


#endif //LAB2_BINARYSEARCHTREE_H
