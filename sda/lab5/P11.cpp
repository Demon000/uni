#include <utility>
#include <list>

#include "P11.h"

using namespace std;

#define INITIAL_CAPACITY 4

class MaxHeap {
public:
    MaxHeap() {
        capacity = INITIAL_CAPACITY;
        size = 0;
        elements = new TElem[capacity];
    }

    ~MaxHeap() {
        delete[] elements;
    }

    TElem pop() {
        int min = elements[0];

        size--;
        elements[0] = elements[size];
        siftDown(0);

        return min;
    }

    void push(TElem value) {
        expand();

        elements[size] = value;
        siftUp(size);

        size++;
    }

    TElem getRoot() {
        return elements[0];
    }

    int getSize() {
        return size;
    }

private:
    void expand() {
        if (size < capacity) {
            return;
        }

        int newCapacity = capacity * 2;
        TElem* newElements = new TElem[newCapacity];

        for (int i = 0; i < capacity; i++) {
            newElements[i] = elements[i];
        }

        for (int i = capacity; i < newCapacity; i++) {
            newElements[i] = 0;
        }

        delete[] elements;

        elements = newElements;
        capacity = newCapacity;

    }

    int getParentIndex(int index) {
        return (index - 1) / 2;
    }

    int getLeftChildIndex(int index) {
        return (index * 2) + 1;
    }

    int getRightChildIndex(int index) {
        return (index * 2) + 2;
    }

    void siftUp(int index) {
        if (index == 0) {
            return;
        }

        int parentIndex = getParentIndex(index);
        if (elements[parentIndex] > elements[index]) {
            return;
        }

        swap(elements[parentIndex], elements[index]);
        siftUp(parentIndex);
    }

    void siftDown(int index) {
        int leftChildIndex = getLeftChildIndex(index);
        int rightChildIndex = getRightChildIndex(index);
        int minIndex;

        if (rightChildIndex >= size) {
            if (leftChildIndex >= size) {
                return;
            } else {
                minIndex = leftChildIndex;
            }
        } else {
            if (elements[leftChildIndex] > elements[rightChildIndex]) {
                minIndex = leftChildIndex;
            } else {
                minIndex = rightChildIndex;
            }
        }

        if (elements[index] < elements[minIndex]) {
            swap(elements[index], elements[minIndex]);
            siftDown(minIndex);
        }
    }

    int capacity;
    int size;
    TElem* elements;
};

void stergeMin(list<TElem>& elements, int k) {
    list<TElem> bigElements;
    MaxHeap heap;

    for (TElem value : elements) {
        if (heap.getSize() < k) {
            heap.push(value);
        } else if (heap.getSize() == k) {
            if (heap.getRoot() > value) {
                int root = heap.pop();
                bigElements.push_back(root);
                heap.push(value);
            } else {
                bigElements.push_back(value);
            }
        }
    }

    elements.clear();
    for (TElem value : bigElements) {
        elements.push_back(value);
    }
}
