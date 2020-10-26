#ifndef LAB1_HOME_CPP_IMAGEPROCESSINGTHREAD_H
#define LAB1_HOME_CPP_IMAGEPROCESSINGTHREAD_H


#include <iostream>
#include <thread>
#include <thread>
#include "Image.h"

class ImageProcessingThread {
public:
    ImageProcessingThread() {}

    ImageProcessingThread(Image *source, Image *target, int start, int end)
            : source(source), target(target), beginning(start), end(end) {}

    virtual void process(int x, int y) = 0;

    void run() {
//        std::cout << "Starting image processing thread with beginning: " << beginning << ", end: " << end << "\n";
        for (int i = beginning; i < end; i++) {
            process(source->mapCoordinatesX(i), source->mapCoordinatesY(i));
        }
    }

    Image *source = nullptr;
    Image *target = nullptr;
    int beginning = 0;
    int end = 0;
};


#endif //LAB1_HOME_CPP_IMAGEPROCESSINGTHREAD_H
