#ifndef LAB1_HOME_CPP_CACHEINPUTIMAGEPROCESSINGTHREAD_H
#define LAB1_HOME_CPP_CACHEINPUTIMAGEPROCESSINGTHREAD_H

#include "ImageProcessingUtils.h"
#include "ImageUtils.h"
#include "CountDownLatch.h"

class CacheInputImageProcessingThread {
public:
    CacheInputImageProcessingThread(Image &image, CountDownLatch &latch, int start, int end, int size)
            : image(image), latch(latch), start(start), end(end), size(size) {
        int dataStart = std::max(start - (size - 1) * image.getWidth() - (size - 1), 0);
        local = Image(image.getWidth(), image.getHeight(), dataStart, end);
    }

    void run() {
        ImageUtils::copyPixels(image, local);

        latch.countDown();
        latch.await();

        for (int i = start; i < end; i++) {
            process(image.mapCoordinatesX(i), image.mapCoordinatesY(i));
        }
    }

    void process(int x, int y) {
        ImageProcessingUtils::averagePixels(local, image, x, y, size);
    }

private:
    CountDownLatch &latch;
    Image &image;
    Image local;
    int start = 0;
    int end = 0;
    int size = 0;
};

#endif //LAB1_HOME_CPP_CACHEINPUTIMAGEPROCESSINGTHREAD_H
