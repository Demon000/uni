#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include "Image.h"
#include "CacheOutputImageProcessingThread.h"
#include "ImageUtils.h"

#define INPUT_FILE_PATH "date.txt"

enum ProcessingType {
    SEQUENTIAL,
    THREADS,
};

typedef void (*processingFunctionType)(Image& source, int p, int size);

void runThreads(Image& source, int p, int size) {
    std::vector<std::shared_ptr<CacheOutputImageProcessingThread>> threadsData;
    std::vector<std::shared_ptr<std::thread>> threads;
    CountDownLatch latch(p);
    int n = source.getWidth() * source.getHeight();
    int chunk = n / p;
    int rest = n % p;
    int start;
    int end = 0;

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

        threadsData.push_back(std::make_shared<CacheOutputImageProcessingThread>(source, latch, start, end, size));
        std::shared_ptr<CacheOutputImageProcessingThread> threadData = threadsData.back();
        threads.push_back(std::make_shared<std::thread>(&CacheOutputImageProcessingThread::run, threadData));
    }

    for (int i = 0; i < p; i++) {
        if (threads[i]->joinable()) {
            threads[i]->join();
        }
    }
}

void runSequential(Image &source, int p, int size) {
    Image temp(source.getWidth(), source.getHeight());

    for (int i = 0; i < source.getHeight(); i++) {
        for (int j = 0; j < source.getWidth(); j++) {
            ImageProcessingUtils::averagePixels(source, temp, j, i, size);
        }
    }

    ImageUtils::copyPixels(temp, source);
}

int runWithParameters(int width, int height, int size, enum ProcessingType type, int threads, int runs) {
    std::ifstream in(INPUT_FILE_PATH);
    Image sourceImage = Image::readFromFile(in);

    processingFunctionType processingFn;
    switch (type) {
        case SEQUENTIAL:
            processingFn = runSequential;
            break;
        case THREADS:
            processingFn = runThreads;
            break;
        default:
            std::cout << "Invalid processing type\n";
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < runs; i++) {
        processingFn(sourceImage, threads, size);
    }
    auto duration = std::chrono::high_resolution_clock::now() - startTime;
    auto averageDuration = duration_cast<std::chrono::milliseconds>(duration / runs).count();

    std::cout << "Average duration: " << averageDuration << "\n";

    return 0;
}

static int parameters[][5] {
        { 10, 10, 3, ProcessingType::SEQUENTIAL, 0 },
        { 10, 10, 3, ProcessingType::THREADS, 4 },

        { 1000, 1000, 5, ProcessingType::SEQUENTIAL, 0 },
        { 1000, 1000, 5, ProcessingType::THREADS, 2 },
        { 1000, 1000, 5, ProcessingType::THREADS, 4 },
        { 1000, 1000, 5, ProcessingType::THREADS, 8 },
        { 1000, 1000, 5, ProcessingType::THREADS, 16 },

        { 10, 10000, 5, ProcessingType::SEQUENTIAL, 0 },
        { 10, 10000, 5, ProcessingType::THREADS, 2 },
        { 10, 10000, 5, ProcessingType::THREADS, 4 },
        { 10, 10000, 5, ProcessingType::THREADS, 8 },
        { 10, 10000, 5, ProcessingType::THREADS, 16 },

        { 10000, 10, 5, ProcessingType::SEQUENTIAL, 0 },
        { 10000, 10, 5, ProcessingType::THREADS, 2 },
        { 10000, 10, 5, ProcessingType::THREADS, 4 },
        { 10000, 10, 5, ProcessingType::THREADS, 8 },
        { 10000, 10, 5, ProcessingType::THREADS, 16 },
};

int main() {
    int runs = 5;
    int lastWidth = 0;
    int lastHeight = 0;

    for (auto parameter : parameters) {
        std::cout << "Running N=" << parameter[0] << ", M=" << parameter[1]
                  << ", n=m=" << parameter[2];

        if (parameter[3] == ProcessingType::THREADS) {
            std::cout << ", p=" << parameter[4] << ";" << std::endl;
        } else if (parameter[3] == ProcessingType::SEQUENTIAL) {
            std::cout << ", p=sequential;" << std::endl;
        }

        if (lastWidth != parameter[0] || lastHeight != parameter[1]) {
            lastWidth = parameter[0];
            lastHeight = parameter[1];

            std::ofstream out(INPUT_FILE_PATH);
            Image generatedImage = Image::generateRandom(lastWidth, lastHeight);
            generatedImage.writeToFile(out);
            out.close();
        }

        runWithParameters(parameter[0], parameter[1],
                          parameter[2], static_cast<ProcessingType>(parameter[3]),
                          parameter[4], runs);
    }
}
