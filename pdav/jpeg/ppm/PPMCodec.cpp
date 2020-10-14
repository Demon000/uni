#include <fstream>
#include <cstring>
#include "PPMCodec.h"

enum PPMFormat {
    PPM3,
    PPM6,
};

#define PPM3_FORMAT_HEADER "P3"
#define PPM6_FORMAT_HEADER "P6"
#define PPM_FORMAT_LENGTH 2

static void skip_whitespace(std::ifstream& input, int skip=0) {
    bool is_comment = false;
    bool is_beginning = true;
    int skipped = 0;
    char c;

    while (true) {
        input.get(c);
        if (c == '\n') {
            goto line_ended;
        }

        if (is_comment) {
            goto skipping;
        }

        if (c == '#' && is_beginning) {
            is_comment = true;
        }

        if (isspace(c) && is_beginning) {
            goto skipping;
        }

        is_beginning = false;

        if (is_comment) {
            goto skipping;
        }

        input.putback(c);
        break;

line_ended:
        is_comment = false;
        is_beginning = true;
skipping:
        skipped++;
        if (skipped == skip) {
            break;
        }
    }
}

void readUint(std::ifstream& input, uint32_t& value) {
    skip_whitespace(input);

    input >> value;
}

void readByte(std::ifstream& input, uint8_t& value) {
    input.read(reinterpret_cast<char *>(&value), sizeof(value));
}

void writeUintLine(std::ofstream& output, uint32_t value) {
    output << value << '\n';
}

void PPMCodec::readP3(RawRGBImage &image, std::ifstream& input, uint32_t max) {
    uint32_t temp;

    for (size_t i = 0; i < image.dataSize(); i++) {
        auto& pixel = image.dataAt(i);
        readUint(input, temp);
        pixel.x = temp * 255 / max;

        readUint(input, temp);
        pixel.y = temp * 255 / max;

        readUint(input, temp);
        pixel.z = temp * 255 / max;
    }
}

void PPMCodec::readP6(RawRGBImage &image, std::ifstream& input, uint32_t max) {
    uint8_t temp;

    skip_whitespace(input, 1);

    for (size_t i = 0; i < image.dataSize(); i++) {
        auto& pixel = image.dataAt(i);
        readByte(input, temp);
        pixel.x = temp * 255 / max;

        readByte(input, temp);
        pixel.y = temp * 255 / max;

        readByte(input, temp);
        pixel.z = temp * 255 / max;
    }
}

void PPMCodec::read(RawRGBImage &image, std::ifstream& input) {
    char format_buffer[PPM_FORMAT_LENGTH];
    enum PPMFormat format;
    uint32_t width;
    uint32_t height;
    uint32_t max;

    input.read(format_buffer, PPM_FORMAT_LENGTH);
    if (memcmp(format_buffer, PPM3_FORMAT_HEADER, PPM_FORMAT_LENGTH) == 0) {
        format = PPMFormat::PPM3;
    } else if (memcmp(format_buffer, PPM6_FORMAT_HEADER, PPM_FORMAT_LENGTH) == 0) {
        format = PPMFormat::PPM6;
    } else {
        throw std::runtime_error("File does not contain PPM format header");
    }

    readUint(input, width);
    readUint(input, height);
    readUint(input, max);
    if (max > 255) {
        throw std::runtime_error("2 byte color component parsing not supported");
    }

    image.resize(width, height);

    if (format == PPMFormat::PPM3) {
        readP3(image, input, max);
    } else {
        readP6(image, input, max);
    }
}

void PPMCodec::write(RawRGBImage &image, std::ofstream &output) {
    std::ifstream input;

    output << PPM3_FORMAT_HEADER << '\n';
    writeUintLine(output, image.width());
    writeUintLine(output, image.height());
    writeUintLine(output, 255);
    for (size_t i = 0; i < image.dataSize(); i++) {
        auto& pixel = image.dataAt(i);
        writeUintLine(output, pixel.x);
        writeUintLine(output, pixel.y);
        writeUintLine(output, pixel.z);
    }
}
