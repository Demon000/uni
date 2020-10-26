#ifndef LAB1_HOME_CPP_IMAGE_H
#define LAB1_HOME_CPP_IMAGE_H


#include <string>
#include <istream>
#include <sstream>

class Image {
public:
    void fillRandom() {
        for (int i = 0; i < width * height; i++) {
            setPixel(i, rand() % 256);
        }
    }

    void readFromFile(std::istream& in) {
        int w, h, pixel;

        in >> w >> h;

        resize(w, h);

        for (int i = 0; i < w * h; i++) {
            in >> pixel;
            setPixel(i, pixel);
        }
    }

    void writeToFile(std::ostream& out) {
        out << width << "\n" << height << "\n";

        for (int i = 0; i < width * height; i++) {
            out << getPixel(i) << "\n";
        }
    }

    virtual void resize(int w, int h) {
        width = w;
        height = h;
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

    virtual void setPixel(int i, int value) = 0;

    virtual void setPixel(int x, int y, int value) {
        setPixel(mapCoordinates(x, y), value);
    }

    virtual int getPixel(int i) = 0;

    virtual int getPixel(int x, int y) {
        return getPixel(mapCoordinates(x, y));
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

    int width = 0;
    int height = 0;
};


#endif //LAB1_HOME_CPP_IMAGE_H
