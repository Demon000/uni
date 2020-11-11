#include <iostream>
#include <mpi.h>
#include "addition.h"

static constexpr int MASTER_RANK = 0;

void runScatterGather(std::istream & firstIn, std::istream & secondIn, std::ofstream & out) {
//    MPI_Init(nullptr, nullptr);

    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);

    MPI_Status status;
    MPI_Request request;

    int *firstDigits = nullptr;
    int *secondDigits = nullptr;
    int *resultDigits = nullptr;
    int maxNoDigits;

    if (worldRank == MASTER_RANK) {
        int firstNoDigits;
        int secondNoDigits;

        firstIn >> firstNoDigits;
        if (!firstIn) {
            throw std::runtime_error("Failed to open file");
        }

        secondIn >> secondNoDigits;
        if (!firstIn) {
            throw std::runtime_error("Failed to open file");
        }

        int totalMaxDigits = std::max(firstNoDigits, secondNoDigits);
        maxNoDigits = totalMaxDigits / worldSize * worldSize;
        if (totalMaxDigits >= maxNoDigits) {
            maxNoDigits += worldSize;
        }

        firstDigits = new int[maxNoDigits];
        secondDigits = new int[maxNoDigits];
        resultDigits = new int[maxNoDigits];

        readNumberAllDigits(firstIn, firstDigits, firstNoDigits, maxNoDigits);
        readNumberAllDigits(secondIn, secondDigits, secondNoDigits, maxNoDigits);

        int localNoDigits = maxNoDigits / worldSize;
        for (int i = 0; i < worldSize; i++) {
            MPI_Isend(&localNoDigits, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &request);
        }
    }

    int localNoDigits;
    MPI_Recv(&localNoDigits, 1, MPI_INT, MASTER_RANK, 0, MPI_COMM_WORLD, &status);

    auto *localFirstDigits = new int[localNoDigits];
    auto *localSecondDigits = new int[localNoDigits];
    auto *localResultDigits = new int[localNoDigits];

    MPI_Scatter(firstDigits, localNoDigits, MPI_INT,
                 localFirstDigits, localNoDigits, MPI_INT,
                 MASTER_RANK, MPI_COMM_WORLD);

    MPI_Scatter(secondDigits, localNoDigits, MPI_INT,
                 localSecondDigits, localNoDigits, MPI_INT,
                 MASTER_RANK, MPI_COMM_WORLD);

    bool isAllNine;
    int carry = addWithCarry(localFirstDigits, localSecondDigits,
                             localResultDigits, localNoDigits,
                             0, isAllNine);

    if (worldRank != 0) {
        MPI_Recv(&carry, 1, MPI_INT, worldRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (isAllNine) {
            carry = addCarryAllNine(localResultDigits, localNoDigits, carry);
        } else {
            addCarry(localResultDigits, localNoDigits, carry);
        }
    }

    if (worldRank != worldSize - 1) {
        MPI_Send(&carry, 1, MPI_INT, worldRank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Gather(localResultDigits, localNoDigits, MPI_INT,
                resultDigits, localNoDigits, MPI_INT,
                MASTER_RANK, MPI_COMM_WORLD);

    if (worldRank == MASTER_RANK && resultDigits != nullptr) {
        printDigitsTrimZeros(out, resultDigits, maxNoDigits);
    }

//    MPI_Finalize();
}
