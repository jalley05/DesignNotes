Credit: https://github.com/huangzehao/SimpleNeuralNetwork

# Create training modules
g++ trainingSamples/makeTrainingSamples.cpp -o makeTrainingSamples
trainingSamples/makeTrainingSamples > ./trainingData.txt

# Build using the provided makefile
make

# Run the neural network
./neuralNet

