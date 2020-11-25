#ifndef POLYNOMIALSTREAMSGENERATOR_H
#define POLYNOMIALSTREAMSGENERATOR_H


#include <vector>
#include <istream>
#include <sstream>
#include <fstream>
#include <random>
#include "PolynomialStream.h"

class PolynomialStreamsGenerator {
public:
    static std::string buildPath(std::string const& pathBegin, std::string const& pathEnd, int i) {
        std::stringstream ss;
        ss << pathBegin;
        ss << i;
        ss << pathEnd;
        return ss.str();
    }

    static void writePolynomialFiles(std::string const& pathBegin, std::string const& pathEnd,
                                     int noPolynomials, int maxNoMembers, int maxMemberPower) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> noMembersDistribution(1, maxNoMembers);
        std::uniform_int_distribution<> memberPowerDistribution(0, maxMemberPower);

        for (int i = 0; i < noPolynomials; i++) {
            std::string path = buildPath(pathBegin, pathEnd, i);

            std::ofstream out(path);
            int noMembers = noMembersDistribution(gen);

            for (int j = 0; j < noMembers; j++) {
                int memberPower = memberPowerDistribution(gen);
                out << 1 << " " << memberPower << std::endl;
            }
        }
    }

    static std::vector<PolynomialStream> openPolynomialStreams(std::string const& pathBegin, std::string const& pathEnd,
                                                             int noPolynomials) {
        std::vector<PolynomialStream> streams;

        for (int i = 0; i < noPolynomials; i++) {
            std::string path = buildPath(pathBegin, pathEnd, i);

            auto *in = new std::ifstream (path);
            auto stream = PolynomialStream(in);
            streams.push_back(stream);
        }

        return streams;
    }

    static void freeStreams(std::vector<PolynomialStream> const& streams) {
        for (auto stream : streams) {
            delete stream.in;
        }
    }
};


#endif //POLYNOMIALSTREAMSGENERATOR_H
