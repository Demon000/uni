#ifndef LAB1_HOME_CPP_COUNTDOWNLATCH_H
#define LAB1_HOME_CPP_COUNTDOWNLATCH_H

#include <chrono>
#include <condition_variable>
#include <mutex>

class CountDownLatch {
public:
    explicit CountDownLatch(const unsigned int count): count(count) { }
    virtual ~CountDownLatch() = default;

    void await() {
        std::unique_lock<std::mutex> lock(mutex);

        if (count > 0) {
            conditional.wait(lock, [this](){ return count == 0; });
        }
    }

    template <class Rep, class Period>
    bool await(const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock<std::mutex> lock(mutex);

        bool result = true;
        if (count > 0) {
            result = conditional.wait_for(lock, timeout, [this](){ return count == 0; });
        }

        return result;
    }

    void countDown() {
        std::unique_lock<std::mutex> lock(mutex);

        if (count > 0) {
            count--;
            conditional.notify_all();
        }
    }

    unsigned int getCount() {
        std::unique_lock<std::mutex> lock(mutex);

        return count;
    }

protected:
    std::mutex mutex;
    std::condition_variable conditional;
    unsigned int count = 0;
};

#endif //LAB1_HOME_CPP_COUNTDOWNLATCH_H
