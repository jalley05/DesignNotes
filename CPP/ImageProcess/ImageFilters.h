#pragma once

#include <vector>
#include <stdint.h>

namespace ImageFilters
{
    typedef std::vector<std::vector<uint8_t>>  ImageType_8;
    typedef std::vector<std::vector<uint16_t>> ImageType_16;
    typedef std::vector<std::vector<uint32_t>> ImageType_32;

    template <class T>
    void resize(T& input, int height, int width) {
        input.resize(height);
        for (int ii = 0; ii < height; ii++)
        {
            input[ii].resize(width);
        }
    }
    
    void median(const ImageType_8& input, ImageType_8& output);

    void sobel(const ImageType_8& input, ImageType_16& output, int& mean);

    void threshold(const ImageType_16& input, ImageType_8& output, int value);
}