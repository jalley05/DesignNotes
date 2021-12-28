#pragma once

/*
 * Description: A neuron in a neural network

 */

#include <vector>
#include <cmath>

class Neuron;

// A layer is a list of neurons
typedef std::vector<Neuron> Layer;

class Neuron
{
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    ~Neuron() = default;

    // A connection to another neuron
    struct Connection
    {
        double weight;
        double deltaWeight;
    };

    // Get or set the neuron output value
    void setOutputVal(double val) { m_outputVal = val; }
    double getOutputVal(void) const { return m_outputVal; }

    // Feed forward previous neuron layer through this
    // layer
    void feedForward(const Layer &prevLayer);

    void calcOutputGradients(double targetVals);
    void calcHiddenGradients(const Layer &nextLayer);
    void updateInputWeights(Layer &prevLayer);

private:
    static double transferFunction(double x);
    static double transferFunctionDerivative(double x);

    // randomWeight: 0 - 1
    static double randomWeight(void) { return rand() / double(RAND_MAX); }
    double sumDOW(const Layer &nextLayer) const;

    static double eta;                          // [0.0...1.0] overall net training rate
    static double alpha;                        // [0.0...n] multiplier of last weight change [momentum]
    double m_outputVal;                         // Value out of the neuron
    std::vector<Connection> m_outputWeights;    // Connection weights from neuron to all other neurons in the next layer
    unsigned m_myIndex;                         // This neuron index in the chain
    double m_gradient;                          // Gradient for training

    // Save weight value after trainings
};
