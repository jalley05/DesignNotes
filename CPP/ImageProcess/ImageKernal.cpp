#include "ImageKernal.h"
#include <math.h>

ImageKernel::ImageKernel(std::vector<T> coeffs)
    m_kernel(coeffs)
{
}

std::vector<T> ImageKernel::run(std::vector<T> img)
{
    bool isEven = (m_kernel % 2) == 0;
    int size = sqrt(m_kernel.size());

    if (isEven)
    {

    }
    else
    {
        for (ii = 0; ii < img.size(); ii++)
        {
            T value = 0;
            for (kk = 0; kk < m_kernel.size(); kk++)
            {
                
            }
        }
    }
}