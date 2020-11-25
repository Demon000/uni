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
    }

    bool isClosed() {
        std::lock_guard lock(m);
        return closed;
    }

    bool isEmpty() {
        std::lock_guard lock(m);
        return q.empty();
    }

    bool shouldWait() {
        return !(isEmpty() && isClosed());
    }

    bool popFront(D & data, std::chrono::milliseconds const& timeout=1ms) {
        std::unique_lock lock(m);

        while (q.empty()) {
            auto status = c.wait_for(lock, timeout);
            if (status == std::cv_status::timeout) {
                return false;
            }
        }

        data = q.front();
        q.pop();

        return true;
    }

private:
    bool closed = false;
    std::mutex m;
    std::condition_variable c;
    std::queue<D> q;
};


#endif // QUEUE_H
