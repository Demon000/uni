#include <thread>
#include "Queue.h"
#include "PolynomialStreamsGenerator.h"

std::vector<PolynomialMember>
runThreaded(std::vector<PolynomialStream> const& streams, int noProducerThreads, int noConsumerThreads, LockingType type) {
    Queue<PolynomialStream> streamsQueue{streams, true};
    Queue<PolynomialMember> membersQueue;
    Polynomial polynomial{type};

    std::vector<std::thread> threads;
    for (int i = 0; i < noProducerThreads; i++) {
        auto thread = std::thread([&]() {
            streamsQueue.popAllFront([&](PolynomialStream & stream) {
                stream.read([&](PolynomialMember const& member) {
                    membersQueue.pushBack(member);
                });
            });

            membersQueue.markClosed();
        });
        threads.push_back(std::move(thread));
    }

    for (int i = 0; i < noConsumerThreads; i++) {
        auto thread = std::thread([&]() {
            membersQueue.popAllFront([&](PolynomialMember & member) {
                polynomial.add(member);
            });
        });
        threads.push_back(std::move(thread));
    }

    for (auto & thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return polynomial.getMembers();
}

std::vector<PolynomialMember> runSequential(std::vector<PolynomialStream> const& streams, LockingType type) {
    Polynomial polynomial{type};

    for (auto & stream : streams) {
        stream.read([&](auto const& member) {
            polynomial.add(member);
        });
    }

    return polynomial.getMembers();
}

#define PATH_BEGIN "polynomials/polynomial_"
#define PATH_END ".txt"
int main() {
    std::vector<std::vector<int>> configurations = {
            { 10, 50, 1000, 0, 1, 3, GLOBAL_LOCK },
            { 10, 50, 1000, 0, 1, 5, GLOBAL_LOCK },
            { 10, 50, 1000, 0, 1, 7, GLOBAL_LOCK },

            { 10, 50, 1000, 0, 2, 2, GLOBAL_LOCK },
            { 10, 50, 1000, 0, 2, 4, GLOBAL_LOCK },
            { 10, 50, 1000, 0, 2, 6, GLOBAL_LOCK },

            { 10, 50, 1000, 0, 3, 1, GLOBAL_LOCK },
            { 10, 50, 1000, 0, 3, 3, GLOBAL_LOCK },
            { 10, 50, 1000, 0, 3, 5, GLOBAL_LOCK },

            { 10, 50, 1000, 0, 1, 3, INDIVIDUAL_LOCK },
            { 10, 50, 1000, 0, 1, 5, INDIVIDUAL_LOCK },
            { 10, 50, 1000, 0, 1, 7, INDIVIDUAL_LOCK },

            { 10, 50, 1000, 0, 2, 2, INDIVIDUAL_LOCK },
            { 10, 50, 1000, 0, 2, 4, INDIVIDUAL_LOCK },
            { 10, 50, 1000, 0, 2, 6, INDIVIDUAL_LOCK },

            { 10, 50, 1000, 0, 3, 1, INDIVIDUAL_LOCK },
            { 10, 50, 1000, 0, 3, 3, INDIVIDUAL_LOCK },
            { 10, 50, 1000, 0, 3, 5, INDIVIDUAL_LOCK },

            { 10, 50, 1000, 1, 0, 0, NO_LOCK },

            { 5, 100, 10000, 0, 1, 3, GLOBAL_LOCK },
            { 5, 100, 10000, 0, 1, 5, GLOBAL_LOCK },
            { 5, 100, 10000, 0, 1, 7, GLOBAL_LOCK },

            { 5, 100, 10000, 0, 2, 2, GLOBAL_LOCK },
            { 5, 100, 10000, 0, 2, 4, GLOBAL_LOCK },
            { 5, 100, 10000, 0, 2, 6, GLOBAL_LOCK },

            { 5, 100, 10000, 0, 3, 1, GLOBAL_LOCK },
            { 5, 100, 10000, 0, 3, 3, GLOBAL_LOCK },
            { 5, 100, 10000, 0, 3, 5, GLOBAL_LOCK },

            { 5, 100, 10000, 0, 1, 3, INDIVIDUAL_LOCK },
            { 5, 100, 10000, 0, 1, 5, INDIVIDUAL_LOCK },
            { 5, 100, 10000, 0, 1, 7, INDIVIDUAL_LOCK },

            { 5, 100, 10000, 0, 2, 2, INDIVIDUAL_LOCK },
            { 5, 100, 10000, 0, 2, 4, INDIVIDUAL_LOCK },
            { 5, 100, 10000, 0, 2, 6, INDIVIDUAL_LOCK },

            { 5, 100, 10000, 0, 3, 1, INDIVIDUAL_LOCK },
            { 5, 100, 10000, 0, 3, 3, INDIVIDUAL_LOCK },
            { 5, 100, 10000, 0, 3, 5, INDIVIDUAL_LOCK },

            { 5, 100, 10000, 1, 0, 0, NO_LOCK },

//            { 5000, 100, 10000, 0, 3, 3, GLOBAL_LOCK },
//            { 5000, 100, 10000, 0, 3, 5, INDIVIDUAL_LOCK },
//            { 5000, 100, 10000, 1, 0, 0, NO_LOCK },
    };
    int noRuns = 100;

    int lastNoPolynomials = -1;
    int lastMaxNoMembers = -1;
    int lastMaxMemberPower = -1;
    std::vector<PolynomialMember> lastMembers;
    for (auto const& config : configurations) {
        if (config[0] != lastNoPolynomials || config[1] != lastMaxNoMembers || config[2] != lastMaxMemberPower) {
            lastNoPolynomials = config[0];
            lastMaxNoMembers = config[1];
            lastMaxMemberPower = config[2];
            lastMembers.clear();

            PolynomialStreamsGenerator::writePolynomialFiles(
                    PATH_BEGIN, PATH_END, lastNoPolynomials, lastMaxNoMembers, lastMaxMemberPower);
        }

        auto streams = PolynomialStreamsGenerator::openPolynomialStreams(PATH_BEGIN, PATH_END, lastNoPolynomials);

        int64_t sum = 0;

        std::vector<PolynomialMember> members;
        for (int r = 0; r < noRuns; r++) {
            auto start = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()).count();

            if (config[3] == 0) {
                members = runThreaded(streams, config[4], config[5], (LockingType) config[6]);
            } else if (config[3] == 1) {
                members = runSequential(streams, (LockingType) config[6]);
            }

            auto end = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            sum += end - start;
        }

        std::cout
                << " polynomials: " << config[0]
                << ", max members: " << config[1]
                << ", max member power: " << config[2];

        if (config[3] == 0) {
            std::cout
                    << ", threaded"
                    << ", producer threads: " << config[4]
                    << ", consumer threads: " << config[5];
            if (config[6] == GLOBAL_LOCK) {
                std::cout << ", with global lock";
            } else if (config[6] == INDIVIDUAL_LOCK) {
                std::cout << ", with individual lock";
            }
        } else if (config[3] == 1) {
            std::cout << ", sequential";
        }

        if (!lastMembers.empty()) {
            if (lastMembers.size() != members.size()) {
                std::cout << "Members differ in size from last result for this configuration" << std::endl;
            } else {
                for (int i = 0; i < members.size(); i++) {
                    PolynomialMember const& lastMember = lastMembers[i];
                    PolynomialMember const& member = members[i];

                    if (lastMember.coefficient != member.coefficient
                            || lastMember.power != member.power) {
                        std::cout << "Member " << i << " differs from last result for this configuration" << std::endl;
                        std::cout << "coefficient: " << lastMember.coefficient << " vs " << member.coefficient << std::endl;
                        std::cout << "power: " << lastMember.power << " vs " << member.power << std::endl;
                    }
                }
            }
        }
        lastMembers = members;

        std::cout << " took " << sum / noRuns << "us on average for " << noRuns << " runs" << std::endl;

        PolynomialStreamsGenerator::freeStreams(streams);
    }

    return 0;
}
