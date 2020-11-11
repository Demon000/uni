#include <iostream>
#include <mpi.h>
#include "addition.h"

static constexpr bool DEBUG = false;

void runManual(std::istream & firstIn, std::istream & secondIn, std::ofstream & out) {
//    MPI_Init(nullptr, nullptr);

    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    int availableWorldSize = worldSize - 1;

    int worldRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);

    MPI_Request request;

    if (worldRank == 0) {
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
        int maxNoDigits = totalMaxDigits / availableWorldSize * availableWorldSize;
        if (totalMaxDigits >= maxNoDigits) {
            maxNoDigits += availableWorldSize;
        }

        int *firstDigits = new int[maxNoDigits];
        int *secondDigits = new int[maxNoDigits];
        int *resultDigits = new int[maxNoDigits];

        auto *requests = new MPI_Request[availableWorldSize];
        int localNoDigits = maxNoDigits / availableWorldSize;
        for (int i = 0; i < availableWorldSize; i++) {
            int processRank = i + 1;
            int digitsStart = i * localNoDigits;
            MPI_Isend(&localNoDigits, 1, MPI_INT, processRank, 0, MPI_COMM_WORLD, &request);

            readNumberDigits(firstIn, &firstDigits[digitsStart], digitsStart, localNoDigits, firstNoDigits, maxNoDigits);
            MPI_Isend(&firstDigits[digitsStart], localNoDigits, MPI_INT, processRank, 0, MPI_COMM_WORLD, &request);

            readNumberDigits(secondIn, &secondDigits[digitsStart], digitsStart, localNoDigits, secondNoDigits, maxNoDigits);
            MPI_Isend(&secondDigits[digitsStart], localNoDigits, MPI_INT, processRank, 0, MPI_COMM_WORLD, &request);

            MPI_Irecv(&resultDigits[digitsStart], localNoDigits, MPI_INT, processRank, 0, MPI_COMM_WORLD, &requests[i]);
        }

        for (int i = 0; i < availableWorldSize; i++) {
            int processRank = i + 1;
            int digitsStart = i * localNoDigits;
            if (DEBUG) std::cout << "waiting for results from: " << processRank << std::endl;
            MPI_Wait(&requests[i], MPI_STATUS_IGNORE);
            if (DEBUG) std::cout << "received for results from: " << processRank << std::endl;
            if (DEBUG) printDigits(std::cout, &resultDigits[digitsStart], localNoDigits);
        }

        printDigitsTrimZeros(out, resultDigits, maxNoDigits);
    } else {
        int localNoDigits;
        MPI_Request noDigitsRequest;
        MPI_Irecv(&localNoDigits, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &noDigitsRequest);
        MPI_Wait(&noDigitsRequest, MPI_STATUS_IGNORE);

        auto *localFirstDigits = new int[localNoDigits];
        auto *localSecondDigits = new int[localNoDigits];
        auto *localResultDigits = new int[localNoDigits];
        int carry = 0;

        MPI_Request firstDigitsRequest;
        MPI_Irecv(localFirstDigits, localNoDigits, MPI_INT, 0, 0, MPI_COMM_WORLD, &firstDigitsRequest);

        MPI_Request secondDigitsRequest;
        MPI_Irecv(localSecondDigits, localNoDigits, MPI_INT, 0, 0, MPI_COMM_WORLD, &secondDigitsRequest);

        int receivedCarry;
        MPI_Request carryRequest;
        if (worldRank != 1) {
            MPI_Irecv(&receivedCarry, 1, MPI_INT, worldRank - 1, 0, MPI_COMM_WORLD, &carryRequest);
        }

        MPI_Wait(&firstDigitsRequest, MPI_STATUS_IGNORE);
        if (DEBUG) std::cout << "received first in: " << worldRank << std::endl;
        if (DEBUG) printDigits(std::cout, localFirstDigits, localNoDigits);
        MPI_Wait(&secondDigitsRequest, MPI_STATUS_IGNORE);
        if (DEBUG) std::cout << "received second in: " << worldRank << std::endl;
        if (DEBUG) printDigits(std::cout, localSecondDigits, localNoDigits);

        int isCarryReceived = 0;
        if (worldRank != 1) {
            MPI_Request_get_status(carryRequest, &isCarryReceived, MPI_STATUS_IGNORE);
            if (isCarryReceived) {
                if (DEBUG) std::cout << "received carry ahead of time in: " << worldRank << std::endl;
                carry = receivedCarry;
                MPI_Request_free(&carryRequest);
            }
        }

        bool isAllNine;
        carry = addWithCarry(localFirstDigits, localSecondDigits,
                             localResultDigits, localNoDigits,
                             carry, isAllNine);

        if (DEBUG) std::cout << "done addition in: " << worldRank << std::endl;
        if (DEBUG) printDigits(std::cout, localResultDigits, localNoDigits);

        if (worldRank != 1 && !isCarryReceived) {
            if (DEBUG) std::cout << "waiting for carry in: " << worldRank << std::endl;
            MPI_Wait(&carryRequest, MPI_STATUS_IGNORE);
            carry = receivedCarry;
            if (DEBUG) std::cout << "received carry in: " << worldRank << std::endl;

            if (isAllNine) {
                carry = addCarryAllNine(localResultDigits, localNoDigits, carry);
            } else {
                addCarry(localResultDigits, localNoDigits, carry);
            }
        }

        if (worldRank != worldSize - 1) {
            if (DEBUG) std::cout << "sending carry in: " << worldRank << std::endl;
            MPI_Isend(&carry, 1, MPI_INT, worldRank + 1, 0, MPI_COMM_WORLD, &request);
        }

        if (DEBUG) std::cout << "sending calculated from: " << worldRank << std::endl;
        MPI_Isend(localResultDigits, localNoDigits, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    }

//    MPI_Finalize();
}
