#include <iostream>
#include <fstream>
#include "Image.h"
#include "DynamicImage.h"
#include "AverageImageProcessingThread.h"
#include "StaticImage.h"

#define INPUT_FILE_PATH "date.txt"

enum ProcessingType {
    SEQUENTIAL,
    THREADS,
};

typedef StaticImage ImageClass;
typedef void (*processingFunctionType)(Image& source, Image& target, int p, int size);

void runThreads(Image& source, Image& target, int p, int size) {
    std::vector<std::shared_ptr<AverageImageProcessingThread>> threadsData;
    std::vector<std::shared_ptr<std::thread>> threads;
    int n = source.width * source.height;
    int chunk = n / p;
    int rest = n % p;
    int start;
    int end = 0;

    target.resize(source.width, source.height);

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

        threadsData.push_back(std::make_shared<AverageImageProcessingThread>(&source, &target, start, end, size));
        std::shared_ptr<AverageImageProcessingThread> threadData = threadsData.back();
        threads.push_back(std::make_shared<std::thread>(&AverageImageProcessingThread::run, threadData));
    }

    for (int i = 0; i < p; i++) {
        if (threads[i]->joinable()) {
            threads[i]->join();
        }
    }
}

void runSequential(Image& source, Image& target, int p, int size) {
    target.resize(source.width, source.height);
    for (int i = 0; i < source.height; i++) {
        for (int j = 0; j < source.width; j++) {
            ImageProcessingUtils::averagePixels(&source, &target, j, i, size);
        }
    }
}

int runWithParameters(int width, int height, int size, enum ProcessingType type, int threads, int runs) {
    std::ofstream out(INPUT_FILE_PATH);
    ImageClass generatedImage;
    generatedImage.resize(width, height);
    generatedImage.fillRandom();
    generatedImage.writeToFile(out);
    out.close();

    std::ifstream in(INPUT_FILE_PATH);
    ImageClass sourceImage;
    sourceImage.readFromFile(in);

    ImageClass targetImage;

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
        processingFn(sourceImage, targetImage, threads, size);
    }
    auto duration = std::chrono::high_resolution_clock::now() - startTime;
    auto averageDuration = duration_cast<std::chrono::milliseconds>(duration / runs).count();

//    std::cout << sourceImage.toString() << "\n";
//    std::cout << targetImage.toString() << "\n";

    std::cout << "Average duration: " << averageDuration << "\n";

    return 0;
}

int main() {
    int runs = 5;

    int parameters[][5] {
            { 10, 10, 3, ProcessingType::THREADS, 4 },
            { 10, 10, 3, ProcessingType::SEQUENTIAL, 0 },

            { 1000, 1000, 5, ProcessingType::THREADS, 2 },
            { 1000, 1000, 5, ProcessingType::THREADS, 4 },
            { 1000, 1000, 5, ProcessingType::THREADS, 8 },
            { 1000, 1000, 5, ProcessingType::THREADS, 16 },
            { 1000, 1000, 5, ProcessingType::SEQUENTIAL, 0 },

            { 10, 10000, 5, ProcessingType::THREADS, 2 },
            { 10, 10000, 5, ProcessingType::THREADS, 4 },
            { 10, 10000, 5, ProcessingType::THREADS, 8 },
            { 10, 10000, 5, ProcessingType::THREADS, 16 },
            { 10, 10000, 5, ProcessingType::SEQUENTIAL, 0 },

            { 10000, 10, 5, ProcessingType::THREADS, 2 },
            { 10000, 10, 5, ProcessingType::THREADS, 4 },
            { 10000, 10, 5, ProcessingType::THREADS, 8 },
            { 10000, 10, 5, ProcessingType::THREADS, 16 },
            { 10000, 10, 5, ProcessingType::SEQUENTIAL, 0 },
    };
    int size = sizeof(parameters) / sizeof(parameters[0]);

    for (int i = 0; i < size; i++) {
        std::cout << "Running N=" << parameters[i][0] << ", M=" << parameters[i][1]
                << ", n=m=" << parameters[i][2];

        if (parameters[i][3] == ProcessingType::THREADS) {
            std::cout << ", p=" << parameters[i][4] << ";" << std::endl;
        } else if (parameters[i][3] == ProcessingType::SEQUENTIAL) {
            std::cout << ", p=sequential;" << std::endl;
        }

        runWithParameters(parameters[i][0], parameters[i][1],
                          parameters[i][2], static_cast<ProcessingType>(parameters[i][3]), parameters[i][4], runs);
    }
}
