#ifndef LAB0_CPP_PPDUTILS_H
#define LAB0_CPP_PPDUTILS_H


#include <string>

class PPDUtils {
public:
    /**
     * Write `size` random numbers bounded by `min` and `max` to the given path.
     * @param path Path to write the random numbers to.
     * @param size Amount if numbers to write.
     * @param min Lower bound for the random numbers.
     * @param max Exclusive upper bound for the random numbers.
     */
    static void writeRandomNumbersToFile(const std::string& path, size_t size, int min, int max);

    /**
     * Compare 2 files given their paths.
     * @param first First file path.
     * @param second Second file path.
     * @return -1 if the first file has less numbers than the second file, or the files have the same amount
     *              of numbers and the number in the first file is smaller
     *         1 if the second file has less numbers than the first file, or if the files have the same amount
     *              of numbers and the number in the second file is smaller
     *         0 if the files have the same numbers
     */
    static int compareNumbersFromFile(const std::string& first, const std::string& second);

};


#endif //LAB0_CPP_PPDUTILS_H
