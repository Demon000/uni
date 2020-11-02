#include <cstdio>

#include <mpi.h>
#include <chrono>

void sum(int *a, int *b, int *c, int size) {
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

void printArray(int *v, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    int n = 100000;
    int m = 10;
    int a[n];
    int b[n];
    int c[n];

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    MPI_Status status;
    int p = world_size - 1;
    int chunk = n / p;
    int rest = n % p;

    auto startTime = std::chrono::high_resolution_clock::now();

    if (world_rank == 0) {
        for (int i = 0; i < n; i++) {
            a[i] = rand() % m;
            b[i] = rand() % m;
        }

        int start;
        int end = 0;
        for (int i = 1; i < world_size; i++) {
            start = end;
            end = start + chunk;

            if (end > n) {
                end = n;
            }

            if (rest > 0) {
                end += 1;
                rest--;
            }

            MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(a + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(b + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        for (int i = 1; i < world_size; i++) {
            MPI_Recv(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);

            MPI_Recv(c + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "time threads: " << duration_cast<std::chrono::microseconds>(endTime - startTime).count() << "\n";

//        printArray(a, n);
//        printArray(b, n);
//        printArray(c, n);
    } else {
        int start;
        int end;
        MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(a + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(b + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        sum(a + start, b + start, c + start, end - start);

        MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        MPI_Send(c + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD);

//        std::cout << start << " " << end <<  " " << world_rank << std::endl;
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
