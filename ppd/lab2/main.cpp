#include <iostream>
#include <vector>
#include <thread>
#include <cmath>

void printV(const std::vector<int>& v) {
    for (int i : v) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}

void runSeq(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& c) {
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < a.size(); i++) {
        c[i] = sqrt(a[i] * a[i] * a[i] * a[i] * a[i] + b[i] * b[i]);
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "time seq: " << duration_cast<std::chrono::microseconds>(endTime - startTime).count() << "\n";

}

void sumThread(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& c, int start, int end) {
    for (int i = start; i < end; i++) {
        c[i] = sqrt(a[i] * a[i] * a[i] * a[i] * a[i] + b[i] * b[i]);
    }
}

void runThreads(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& c, int p) {
    std::vector<std::thread> threads;
    size_t n = a.size();
    size_t chunk = n / p;
    size_t rest = n % p;
    size_t start;
    size_t end = 0;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < p; i++) {
        start = end;
        end = start + chunk;

        if (end > n) {
            end = n;
        }

        if (rest > 0) {
            end += 1;
            rest--;
        }

        threads.emplace_back(sumThread, std::ref(a), std::ref(b), std::ref(c), start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << "time threads: " << duration_cast<std::chrono::microseconds>(endTime - startTime).count() << "\n";
}

int main() {
    int n = 10000000;
    int max = 1000;
    int p = 4;

    std::vector<int> a(n);
    std::vector<int> b(n);
    std::vector<int> c(n);
    std::vector<int> d(n);

    for (int i = 0; i < n; i++) {
        a[i] = rand() % max;
        b[i] = rand() % max;
    }

    runSeq(a, b, c);
    runThreads(a, b, d, p);

//    printV(a);
//    printV(b);
//    printV(c);
//    printV(d);

    return 0;
}
