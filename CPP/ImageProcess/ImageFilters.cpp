#include "ImageFilters.h"
#include <iostream>
#include <climits>

void ImageFilters::median(const ImageType_8& input, ImageType_8& output)
{
    // Image is defined as [row][col]
    int height = input.size();
    int width = input.at(0).size();

    int kernelSize = 3; // keep odd
    int kernelOffset = (kernelSize-1)/2;
    int kernelMiddle = (kernelSize*kernelSize - 1) / 2;
    int kernelCount = 0;
    int kernelSqr = kernelSize * kernelSize;
    static std::vector<uint8_t> kernel(kernelSize * kernelSize);

    // Filter kernel 3x3
    #pragma clang loop vectorize(enable) interleave(enable)
    for(int row = 0; row < height; row++)
    {
        #pragma clang loop vectorize(enable) interleave(enable)
        for(int col = 0; col < width; col++)
        {
            // Build kernel with surounding pixels
            int kIndex = 0;
            for(int kRow = -kernelOffset; kRow <= kernelOffset; kRow++)
            {
                for(int kCol = -kernelOffset; kCol <= kernelOffset; kCol++)
                {
                    // Handle edge case, if off the edge just duplicate the middle pixel
                    int readRow = (kRow+row < 0) ? 0 : (kRow+row > height-1) ? row : kRow+row;
                    int readCol = (kCol+col < 0) ? 0 : (kCol+col > width-1) ? col : kCol+col;

                    //std::cout << "kCol " << kCol << std::endl;
                    //std::cout << "Row: " << row << " Col " << col << " ReadRow " << readRow << " Read Col " << readCol << std::endl;
                    kernel[kIndex++] = (input[readRow][readCol]);
                }
            }

            #if 0
            for(int ii = 1; ii <= kernelSize*kernelSize; ii++)
            {
                std::cout << (int)kernel.at(ii-1) << " ";
                if (ii % kernelSize == 0) {
                    std::cout << "\n";
                }
            }
            std::cout << "\n";
            std::cout << "\n";
            std::cout << "\n";
            #endif

            std::sort(kernel.begin(), kernel.end());
            output[row][col] = kernel.at(kernelMiddle);
        }
    }
}

void ImageFilters::sobel(const ImageType_8& input, ImageType_16& output, int& mean)
{
    // Image is defined as [row][col]
    int height = input.size();
    int width = input.at(0).size();
    mean = 0;
    //std::cout << height  << "  " << width << std::endl;

    int rowOffset[2];
    int colOffset[2];

    int maxNormalize = 0;

    #pragma clang loop vectorize(enable) interleave(enable)
    for(int row = 0; row < height; row++)
    {
        int minVal = 0;
        int maxVal = 0;

        #pragma clang loop vectorize(enable) interleave(enable)
        for(int col = 0; col < width; col++)
        {
            rowOffset[1] = row < height-2 ? 2 : row < height-1 ? 1 : 0;
            rowOffset[0] = row < height-1 ? 1 : 0;
            colOffset[1] = col < width-2 ? 2 : col < width-1 ? 1 : 0;
            colOffset[0] = col < width-1 ? 1 : 0; 

            int c0 = input[rowOffset[1] + row][colOffset[1] + col] - input[0 + row][0             + col];
            int c1 = input[rowOffset[1] + row][0            + col] - input[0 + row][colOffset[1]  + col];

            int V = std::abs(c0 - c1 + (input[rowOffset[1]+row][colOffset[0]+col] - input[0           + row][colOffset[0] + col]) * 2);
            int H = std::abs(c0 - c1 + (input[rowOffset[0]+row][colOffset[1]+col] - input[rowOffset[0]+ row][0            + col]) * 2);

            minVal = std::min(H, V);
            maxVal = std::max(H, V);

            //std::cout << minVal << " " << maxVal << " " << V << " " << H << std::endl;
            int value = maxVal + (minVal / 4);
            mean += value;
            output[row][col] = value;
        }
    }

    mean = mean / (width * height) * 1;
}

void ImageFilters::threshold(const ImageType_16& input, ImageType_8& output, int value)
{
    int height = input.size();
    int width = input.at(0).size();
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            output[row][col] = input[row][col] > value ? 255 : 0;
        }
    }
}