#ifndef LAB1_HOME_CPP_CACHEOUTPUTIMAGEPROCESSINGTHREAD_H
#define LAB1_HOME_CPP_CACHEOUTPUTIMAGEPROCESSINGTHREAD_H

#include "CacheOutputImageProcessingThread.h"
#include "ImageProcessingUtils.h"
#include "ImageUtils.h"
#include "CountDownLatch.h"

class CacheOutputImageProcessingThread {
public:
    CacheOutputImageProcessingThread(Image &image, CountDownLatch &latch, int start, int end, int size)
            : image(image), latch(latch), start(start), end(end), size(size) {
        local = Image(image.getWidth(), image.getHeight(), start, end);
    }

    void run() {
        for (int i = start; i < end; i++) {
            process(image.mapCoordinatesX(i), image.mapCoordinatesY(i));
        }

        latch.countDown();
        latch.await();

        ImageUtils::copyPixels(local, image);
    }

    void process(int x, int y) {
        ImageProcessingUtils::averagePixels(image, local, x, y, size);
    }

private:
    CountDownLatch &latch;
    Image &image;
    Image local;
    int start = 0;
    int end = 0;
    int size = 0;
};

#endif //LAB1_HOME_CPP_CACHEOUTPUTIMAGEPROCESSINGTHREAD_H
