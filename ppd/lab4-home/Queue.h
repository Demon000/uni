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

    /**
     * Add an element to the queue
     * @param data the element to be added to the queue
     */
    void pushBack(D const& data) {
        std::lock_guard lock(m);

        q.push(data);
        c.notify_one();
    }

    /**
     * Mark the queue as closed
     */
    void markClosed() {
        std::lock_guard lock(m);

        closed = true;
        c.notify_all();
    }

    /**
     * Pop an element from the queue
     * @param data reference in which to put the popped data
     * @return whether the queue is closed or not
     */
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

    /**
     * Pop elements from the queue until it drains and gets closed, run a function for each element popped
     * @tparam F function template
     * @param fn function to run
     */
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
