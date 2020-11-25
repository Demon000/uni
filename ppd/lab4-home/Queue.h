#ifndef QUEUE_H
#define QUEUE_H


#include <queue>
#include <condition_variable>
#include <iostream>

using namespace std::chrono_literals;

template <typename D>
class Queue {
public:
    Queue(std::vector<D> const& datas, bool closed=false) : Queue(closed) {
        for (auto const& data : datas) {
            pushBack(data);
        }
    }

    Queue(bool closed=false) : closed(closed) {}

    void pushBack(D const& data) {
        std::lock_guard lock(m);

        q.push(data);
        c.notify_one();
    }

    void markClosed() {
        std::lock_guard lock(m);

        closed = true;
        c.notify_all();
    }

    bool isClosed() {
        return closed;
    }

    bool isEmpty() {
        std::lock_guard lock(m);
        return q.empty();
    }

    bool popFront(D & data) {
        std::unique_lock lock(m);

        while (true) {
            if (!q.empty()) {
                break;
            }

            if (closed) {
                return true;
            }

            c.wait(lock);
        }

        data = q.front();
        q.pop();

        return false;
    }

    template <typename F>
    void popAllFront(F fn) {
        while (true) {
            D data;
            auto failed = popFront(data);
            if (failed) {
                break;
            }

            fn(data);
        }
    }

private:
    std::atomic_bool closed = false;
    std::mutex m;
    std::condition_variable c;
    std::queue<D> q;
};


#endif // QUEUE_H
