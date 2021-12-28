#include "trainingData.h"
#include "neuralNet.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <unistd.h>

using namespace std;

double Net::m_recentAverageSmoothingFactor = 1.0; // Number of training samples to average over

Net::Net(const vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();
    printf("Number of neural layers %d\n", numLayers);

    for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
    {
        // Create a layer
        m_layers.push_back(Layer());

        // numOutputs of layer[i] is the numInputs of layer[i+1]
        // numOutputs of last layer is 0
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        printf("NumOutputs for layer %d: %d\n", layerNum, numOutputs);
        printf("Numer of neurons in layer %d: %d\n", layerNum, topology[layerNum]);

        // We have made a new Layer, now fill it with neurons, and
        // add a bias neuron to the layer:
        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
        {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));
        }

        // Force the bias node's output value to 1.0. It's the last neuron created above
        m_layers.back().back().setOutputVal(1.0);
    }

}

void Net::getResults(vector<double> &resultVals) const
{
    resultVals.clear();

    for(unsigned n = 0; n < m_layers.back().size() - 1; ++n)
    {
        resultVals.push_back(m_layers.back()[n].getOutputVal());
    }
}


void Net::printLayerOutputs(void) const
{
    for(unsigned layerNum = 0; layerNum < m_layers.size(); ++layerNum)
    {
        auto& layer = m_layers[layerNum];

        for(unsigned neuronNum = 0; neuronNum < layer.size(); ++ neuronNum)
        {
            printf("Layer %d, Neuron %d, output %f\n", layerNum, neuronNum, layer[neuronNum].getOutputVal());
        }
        printf("\n");
    }
}

void Net::backProp(const std::vector<double> &targetVals)
{
    // Calculate overal net error (RMS of output neuron errors)

    Layer &outputLayer = m_layers.back();
    double error = 0.0;

    for(unsigned n = 0; n < outputLayer.size() - 1; ++n)
    {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        error += delta *delta;
    }
    error /= outputLayer.size() - 1; // get average error squared
    error = sqrt(error); // RMS

    // Implement a recent average measurement:
    //
    m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + error)
        / (m_recentAverageSmoothingFactor + 1.0);

    // Calculate output layer gradients
    //
    for(unsigned n = 0; n < outputLayer.size() - 1; ++n)
    {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    // Calculate gradients on hidden layers
    //
    for(unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum)
    {
        Layer &hiddenLayer = m_layers[layerNum];
        Layer &nextLayer = m_layers[layerNum + 1];

        for(unsigned n = 0; n < hiddenLayer.size(); ++n)
        {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    // For all layers from outputs to first hidden layer,
    // update connection weights
    //
    for(unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum)
    {
        Layer &layer = m_layers[layerNum];
        Layer &prevLayer = m_layers[layerNum - 1];

        for(unsigned n = 0; n < layer.size() - 1; ++n)
        {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

void Net::feedForward(const vector<double> &inputVals)
{
    // Check the num of inputVals euqal to neuronnum expect bias
    assert(inputVals.size() == m_layers[0].size() - 1);

    // Assign {latch} the input values into the input neurons
    // This is the first layer
    for(unsigned i = 0; i < inputVals.size(); ++i)
    {
        m_layers[0][i].setOutputVal(inputVals[i]); 
    }

    // Forward propagate to each neuron. From the input layer
    // Feed the data forward to the next layer.
    for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum)
    {
        Layer &prevLayer = m_layers[layerNum - 1];
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
        {
            m_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}


void showVectorVals(string label, vector<double> &v)
{
    cout << label << " ";
    for(unsigned i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main()
{
    TrainingData trainData("trainingData.txt");
    //e.g., {3, 2, 1 }
    vector<unsigned> topology;

    trainData.getTopology(topology);
    Net myNet(topology);
    //myNet.printLayerOutputs();

    vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;

    int rightCount = 0;
    int wrongCount = 0;
    int wrongStall = 0;

    while(!trainData.isEof())
    {
        ++trainingPass;

        // Get new input data and feed it forward:
        if(trainData.getNextInputs(inputVals) != topology[0])
        {
            break;
        }


        //showVectorVals(": Inputs :", inputVals);
        myNet.feedForward(inputVals);

        // Collect the net's actual results:
        myNet.getResults(resultVals);
        //showVectorVals("Outputs:", resultVals);

        // Train the net what the outputs should have been:
        trainData.getTargetOutputs(targetVals);
        //showVectorVals("Targets:", targetVals);
        assert(targetVals.size() == topology.back());

        myNet.backProp(targetVals);

        if(targetVals[0] == (int)round(resultVals[0]))
        {
            rightCount++;
        }
        else
        {
            wrongCount++;
        }

        //myNet.printLayerOutputs();

        // Report how well the training is working, average over recnet
        cout << "Pass: " << setw(8) << trainingPass
            << "  Net RAE: " << fixed << setprecision(5) << myNet.getRecentAverageError()
            << "  Right " << setw(8) << rightCount << ", Wrong " << setw(8) << wrongCount;

        cout << " Intelligence: ";
        double intelligence = 0;
        if(rightCount > 0 && wrongCount > 0)
            intelligence = ((double)rightCount / (rightCount + wrongCount)) * 100.0;
        cout << intelligence << "     ";
        for(int ii = 50; ii < intelligence; ii+=1)
        {
            cout << "|";
        }

        cout << flush;
        cout << "\r";

        if(trainingPass % 20000 == 0)
        {
            cout << endl;

            static int wrongCountOld = 0;
            if(wrongCountOld == wrongCount)
                wrongStall++;
            else
                wrongStall = 0;

            wrongCountOld = wrongCount;
            if(wrongStall == 10)
                break;
        }

#if 0
        if(intelligence < 50) 
            usleep(5000);
        else if(intelligence < 80)
            usleep(5000);
        else
            usleep(10);
#endif
    }

    cout << endl << "Done" << endl;
}

