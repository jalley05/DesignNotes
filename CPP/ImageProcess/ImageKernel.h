#pragma once

#include <vector>

template <class T>
class ImageKernel
{
public:
    ImageKernel(std::vector<T> coeffs);                         // Constructor
    ~ImageKernel() = default;                                   // Destructor
    ImageKernel(const ImageKernel& other) = delete;             // Copy constructor 
    ImageKernel& operator=(const ImageKernel& other) = delete;  // Copy assignment

    std::vector<T> run(std::vector<T> img);

private:
    std::vector<T> m_kernel;
};