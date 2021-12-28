#pragma once

#include <vector>
#include <sstream>
#include <fstream>

class TrainingData
{
    public:
        TrainingData(const std::string filename);
        ~TrainingData() = default;

        bool isEof(void) const
        {
            return m_trainingDataFile.eof();
        }

        void getTopology(std::vector<unsigned> &topology);

        // Returns the number of input values read from the file:
        unsigned getNextInputs(std::vector<double> &inputVals);
        unsigned getTargetOutputs(std::vector<double> &targetOutputVals);

    private:
        std::ifstream m_trainingDataFile;
};


