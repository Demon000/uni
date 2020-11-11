#include <chrono>
#include <iostream>
#include <mpi.h>
#include "addition.h"

#define FIRST_NUMBER_INPUT_FILE "Numar1.txt"
#define SECOND_NUMBER_INPUT_FILE "Numar2.txt"
#define RESULT_NUMBER_OUTPUT_FILE "Numar3.txt"

typedef void (*processingFunctionType)(std::istream & firstIn, std::istream & secondIn, std::ofstream & out);

enum AdditionMode {
    ITERATIVE = 0,
    MPI_SCATTER_GATHER = 1,
    MPI_MANUAL = 2,
};

bool isMpiMode(int mode) {
    return mode == MPI_SCATTER_GATHER || mode == MPI_MANUAL;
}

int main(int argc, char *argv[]) {
    processingFunctionType processingFn;
    int noRuns = 100;

    if (argc != 2) {
        std::cout << "Invalid arguments" << std::endl;
        return -1;
    }

    int mode = std::atoi(argv[1]);
    switch (mode) {
        case ITERATIVE:
            processingFn = runIterative;
            break;
        case MPI_SCATTER_GATHER:
            processingFn = runScatterGather;
            break;
        case MPI_MANUAL:
            processingFn = runManual;
            break;
        default:
            std::cout << "Invalid processing type\n";
            return -1;
    }

    int worldRank;
    if (isMpiMode(mode)) {
        MPI_Init(nullptr, nullptr);
        MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    }

    double totalDuration = 0;

    for (int i = 0; i < noRuns; i++) {
        std::ifstream firstIn(FIRST_NUMBER_INPUT_FILE);
        std::ifstream secondIn(SECOND_NUMBER_INPUT_FILE);
        std::ofstream out(RESULT_NUMBER_OUTPUT_FILE);

        double startTimeMPI;
        std::chrono::time_point<std::chrono::system_clock> startTimeIterative;
        if (isMpiMode(mode)) {
            MPI_Barrier(MPI_COMM_WORLD);
            startTimeMPI = MPI_Wtime();
        } else {
            startTimeIterative = std::chrono::high_resolution_clock::now();
        }

        processingFn(firstIn, secondIn, out);

        double endTimeMPI;
        std::chrono::time_point<std::chrono::system_clock> endTimeIterative;
        if (isMpiMode(mode)) {
            MPI_Barrier(MPI_COMM_WORLD);
            endTimeMPI = MPI_Wtime();
        } else {
            endTimeIterative = std::chrono::high_resolution_clock::now();
        }

        if (isMpiMode(mode) && worldRank == 0) {
            totalDuration += (endTimeMPI - startTimeMPI) * 1000;
        } else if (!isMpiMode(mode)) {
            auto duration = endTimeIterative - startTimeIterative;
            totalDuration += duration_cast<std::chrono::milliseconds>(duration).count();
        }
    }

    if (!isMpiMode(mode) || worldRank == 0) {
        double averageDuration = totalDuration / noRuns;
        std::cout << "Average duration: " << averageDuration << "\n";
    }

    if (isMpiMode(mode)) {
        MPI_Finalize();
    }

    return 0;
}
