#ifndef LAB1_HOME_CPP_IMAGE_H
#define LAB1_HOME_CPP_IMAGE_H


#include <string>
#include <istream>
#include <sstream>
#include <vector>

class Image {
public:
    Image(int width, int height) : Image(width, height, width * height) {}

    Image(int width, int height, int size) : Image(width, height, 0, size) {}

    Image(int width, int height, int start, int end)
            : start(start), end(end) {
        resize(width, height, end - start);
    }

    Image() {}

    void resize(int w, int h, int s) {
        width = w;
        height = h;
        size = s;
        pixels.resize(w * h);
    }

    int mapCoordinates(int x, int y) {
        return y * width + x;
    }

    int mapCoordinatesX(int i) {
        return i % width;
    }

    int mapCoordinatesY(int i) {
        return i / width;
    }

    void checkAccess(int i) {
        if (i < start) {
            throw std::runtime_error("Accessing value before skip image data");
        }

        if (i >= end) {
            throw std::runtime_error("Accessing value after skip image data");
        }
    }

    void setPixel(int i, int value) {
        checkAccess(i);
        pixels[i - start] = value;
    }

    void setPixel(int x, int y, int value) {
        setPixel(mapCoordinates(x, y), value);
    }

    int getPixel(int i) {
        checkAccess(i);
        return pixels[i - start];
    }

    int getPixel(int x, int y) {
        return getPixel(mapCoordinates(x, y));
    }

    std::vector<uint8_t>& getPixels() {
        return pixels;
    }

    int getStart() const {
        return start;
    }

    int getEnd() const {
        return end;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    int getSize() const {
        return width * height;
    }

    int getRealSize() const {
        return size;
    }

    bool isSkip() const {
        return getSize() != getRealSize();
    }

    static Image readFromFile(std::istream& in) {
        int w, h, pixel;

        in >> w >> h;

        Image image(w, h);

        for (int i = 0; i < w * h; i++) {
            in >> pixel;
            image.setPixel(i, pixel);
        }

        return image;
    }

    static Image generateRandom(int width, int height) {
        Image image(width, height);

        for (int i = 0; i < width * height; i++) {
            image.setPixel(i, rand() % 256);
        }

        return image;
    }

    void writeToFile(std::ostream& out) {
        out << width << "\n" << height << "\n";

        for (int i = 0; i < width * height; i++) {
            out << getPixel(i) << "\n";
        }
    }

    std::string toString() {
        std::stringstream ss;

        ss << "Width: " << width << ", height: " << height << "\n";

        for (int i = 0; i < width * height; i++) {
            ss << getPixel(i) << " ";

            if (i % width == width - 1) {
                ss << "\n";
            } else {
                ss << " ";
            }
        }

        return ss.str();
    }

private:
    std::vector<uint8_t> pixels;
    int start = 0;
    int end = 0;
    int size = 0;
    int width = 0;
    int height = 0;
};


#endif //LAB1_HOME_CPP_IMAGE_H
