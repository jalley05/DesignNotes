#pragma once

#include <vector>
#include "neuron.h"

class Net
{
public:
    Net(const std::vector<unsigned> &topology);
    ~Net() = default;

    void feedForward(const std::vector<double> &inputVals);
    void backProp(const std::vector<double> &targetVals);
    void getResults(std::vector<double> &resultVals) const;
    double getRecentAverageError(void) const { return m_recentAverageError; }

    void printLayerOutputs() const;
private:
    std::vector<Layer> m_layers; //m_layers[layerNum][neuronNum]
    double m_recentAverageError;
    static double m_recentAverageSmoothingFactor;

};

