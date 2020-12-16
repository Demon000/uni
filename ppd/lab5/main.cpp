#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

void printN(std::vector<int> const& v) {
    for (auto const& x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    int p = 4;
    int n = 100000000;
    int max_num = 10;
    std::vector<int> a(n), b(n), c(n), d(n);

    for (int i = 0; i < n; i++) {
        a[i] = rand() % max_num;
        b[i] = rand() % max_num;
    }

//    printN(a);
//    printN(b);

    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;

    start= std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
    end = std::chrono::high_resolution_clock::now();

    auto duration_seq = duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Seq: " << duration_seq.count() << std::endl;

    omp_set_num_threads(p);

    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for default(none) schedule(static) shared(d, a, b, n)
    for (int i = 0; i < n; i++) {
        d[i] = a[i] + b[i];
    }
    end = std::chrono::high_resolution_clock::now();
    auto duration_threaded = duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Threaded: " << duration_threaded.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for default(none) schedule(guided) shared(d, a, b, n)
    for (int i = 0; i < n; i++) {
        d[i] = a[i] + b[i];
    }
    end = std::chrono::high_resolution_clock::now();
    auto duration_threaded_dynamic = duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Threaded dynamic: " << duration_threaded_dynamic.count() << std::endl;

    return 0;
}
