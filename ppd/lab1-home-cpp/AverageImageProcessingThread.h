#ifndef LAB1_HOME_CPP_AVERAGEIMAGEPROCESSINGTHREAD_H
#define LAB1_HOME_CPP_AVERAGEIMAGEPROCESSINGTHREAD_H


#include "ImageProcessingThread.h"
#include "ImageProcessingUtils.h"

class AverageImageProcessingThread : public ImageProcessingThread {
public:
    AverageImageProcessingThread() : ImageProcessingThread() {}

    AverageImageProcessingThread(Image *source, Image *target, int start, int end, int size)
            : ImageProcessingThread(source, target, start, end), size(size) {}

    void process(int x, int y) override {
        ImageProcessingUtils::averagePixels(source, target, x, y, size);
    }

private:
    int size = 0;
};


#endif //LAB1_HOME_CPP_AVERAGEIMAGEPROCESSINGTHREAD_H
