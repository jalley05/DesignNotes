#include <vector>
#include <chrono>
#include <iostream>

#include "ImageFilters.h"

int main()
{
    // Create a random "image" 10x10 8 bits
    const int WIDTH = 660;
    const int HEIGHT = 396;
    ImageFilters::ImageType_8 image;
    //ImageFilters::ImageType_8 outputImage;

    for(int ii = 0; ii < HEIGHT; ii++)
    {
        std::vector<uint8_t> vec;

        for(int jj = 0; jj < WIDTH; jj++)
        {
            vec.push_back(rand());
        }

        image.push_back(vec);
        //outputImage.push_back(vec);
    }

    int foo[100];
    int bla[100];

    #pragma clang loop vectorize(enable) interleave(enable)
    for(int ii = 0; ii < 100; ii++) {
        foo[ii] = ii;
        bla[ii] = ii +5;
    }

    //FILE* f = fopen("original", "wb");
    //fwrite(image.data(), sizeof(uint8_t), ROW*COL, f);
    //fclose(f);

#if 0
    for(int ii = 0; ii < image.size(); ii++)
    {
        for(int jj = 0; jj < image.at(0).size(); jj++)
        {
            printf("%d\t", image[ii][jj]);
        }
        printf("\n");
    } 

    printf("\n\n");
#endif

    ImageFilters::ImageType_8 medianImage;
    ImageFilters::resize(medianImage, HEIGHT, WIDTH);

    auto start = std::chrono::high_resolution_clock::now();
    ImageFilters::median(image, medianImage);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << "Median filter in us: " << duration.count() << std::endl;

#if 0
    for(int ii = 0; ii < medianImage.size(); ii++)
    {
        for(int jj = 0; jj < medianImage.at(0).size(); jj++)
        {
            printf("%d\t", medianImage[ii][jj]);
        }
        printf("\n");
    } 

    printf("\n\n");
#endif

    ImageFilters::ImageType_16 sobelImage;
    ImageFilters::resize(sobelImage, HEIGHT, WIDTH);

    int threshold = 0;
    ImageFilters::sobel(medianImage, sobelImage, threshold);

#if 0
    for(int ii = 0; ii < sobelImage.size(); ii++)
    {
        for(int jj = 0; jj < sobelImage.at(0).size(); jj++)
        {
            printf("%d\t", sobelImage[ii][jj]);
        }
        printf("\n");
    } 

    printf("\n\n");
#endif

    ImageFilters::ImageType_8 outputImage;
    ImageFilters::resize(outputImage, HEIGHT, WIDTH);
    ImageFilters::threshold(sobelImage, outputImage, threshold);



#if 0

    int kernelSize = 3; // keep odd
    int kernelOffset = (kernelSize-1)/2;
    int kernelCount = 0;
    int kernelSqr = kernelSize * kernelSize;
    static std::vector<uint8_t> kernel(kernelSize * kernelSize);

    auto start = std::chrono::high_resolution_clock::now();

    // Filter kernel 3x3
    for(int row = kernelOffset; row < WIDTH - kernelOffset; row++)
    {
        for(int col = kernelOffset; col < HEIGHT - kernelOffset; col++)
        {
            int rowIndex = row;
            int colIndex = col;

            // Build kernel with surounding pixels
            int kIndex = 0;
            for(int kk = -kernelOffset; kk <= kernelOffset; kk++)
            {
                for(int ll = -kernelOffset; ll <= kernelOffset; ll++)
                {
                    kernel[kIndex++] = (image[rowIndex + kk][colIndex + ll]);
                }
            }

            
            std::sort(kernel.begin(), kernel.end());
            outputImage[rowIndex][colIndex] = kernel.at(4);
        
            /*
            if(image[rowIndex][colIndex] == kernel.at(0))
            {
                outputImage[rowIndex][colIndex] = kernel.at(4);
            }
            else if(image[rowIndex][colIndex] == kernel.at(8))
            {
                outputImage[rowIndex][colIndex] = kernel.at(4);
            }
            else
            {
                outputImage[rowIndex][colIndex] = image[rowIndex][colIndex];
            }
            


            const auto& [g_min, g_max] = std::minmax_element(kernel.begin(), kernel.end());

            //uint8_t g_max = kernel.at(std::distance(kernel.begin(), std::max_element(kernel.begin(), kernel.end())));
            //uint8_t g_min = kernel.at(std::distance(kernel.begin(), std::min_element(kernel.begin(), kernel.end())));
            uint8_t& pixel = image[rowIndex][colIndex];

            if(pixel == *g_max || pixel == *g_min) {
                //kernelCount++;
                // This is a noise pixel

                // 1. Sort the kernel
                std::sort(kernel.begin(), kernel.end());

                uint8_t& replacePix = kernel[kernelSqr / 2];
                outputImage[rowIndex][colIndex] = replacePix;
            }
            else {
                outputImage[rowIndex][colIndex] = image[rowIndex][colIndex];
            }
            */
            //printf("%d\t", outputImage[ii][jj]);
        }
        //printf("\n");
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    //std::cout << duration.count() << std::endl;
    //std::cout << kernelCount << std::endl;
#endif

#if 0
    for(int ii = 0; ii < outputImage.size(); ii++)
    {
        for(int jj = 0; jj < outputImage.at(0).size(); jj++)
        {
            printf("%d\t", outputImage[ii][jj]);
        }
        printf("\n");
    } 

    printf("\n\n");
#endif

    return 0;

}