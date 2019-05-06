//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//                           //
//     NeuralNetwork.cpp     //
//                           //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
#include "NeuralNetwork.h"
#define NUM_DIGITS 10

//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//	Private Variables        //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//	NetLayer inputToHidden;  //
//	NetLayer hiddenToOutput; //
//	double lRate;            //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\//

// Neural Network Constructor
// Defines a 3-layer neural network
// Defined by number of input nodes, hidden nodes, and output nodes
// Output usually defined as 10 nodes for digit recognition (0 - 9)
NeuralNetwork::NeuralNetwork(int numInput, int numHidden, int numOutput, double learningRate) {
	this->inputToHidden = NetLayer(numInput, numHidden);
	this->hiddenToOutput = NetLayer(numHidden, numOutput);
	this->lRate = learningRate;
}

//
void NeuralNetwork::query(std::vector<double> queryInput) {
	// Set the input to column vector
    Matrix<double> qi;
    qi.push_back(queryInput);
    qi = MM::transpose(qi);
    
    this->inputToHidden.setInput(qi);
    this->inputToHidden.computeOutput();
    this->hiddenToOutput.setInput(inputToHidden.getOutput());
    this->hiddenToOutput.computeOutput();
}

//train the network for one input
void NeuralNetwork::train(int answer, std::vector<double> trainInput) {
	//calculate the output
    query(trainInput);

	//backpropagate errors and then within adjust weights
	this->backpropagation(answer, this->hiddenToOutput.getOutput());
}

//Back propogate errors from the output layer to the hidden layer
void NeuralNetwork::backpropagation(int answer, Matrix<double> tOut) {
	// Calculate the error for output layer
	Matrix<double> outputError;
	for (size_t i = 0; i < tOut.size(); i++) {
		if (i == answer) {
			outputError.push_back({ 0.99 - tOut[i][0] });
		}
		else {
			outputError.push_back({ 0.01 - tOut[i][0] });
		}
	}
    
	// Calculate the error for hidden layer
	Matrix<double> hiddenError =  MM::transpose(this->hiddenToOutput.getWeights()) * outputError;
    
	//adjust the weights using the error calculated
	this->adjustWeights(outputError, hiddenError);
}

// Adjust the weights according to the output error and the hidden layer error
void NeuralNetwork::adjustWeights(Matrix<double> oError, Matrix<double> hError) {
    Matrix<double> temph2o;
    Matrix<double> tempi2h;

    Matrix<double> h2oOutput = this->hiddenToOutput.getOutput();
    Matrix<double> i2hOutput = this->inputToHidden.getOutput();

    for (size_t i = 0; i < oError.size(); i++) {
        double si = h2oOutput[i][0];
        temph2o.push_back({ -1 * (this->lRate) * oError[i][0] * (si * ((double)1 - si)) });
    }
    for (size_t i = 0; i < hError.size(); i++) {
        double si = i2hOutput[i][0];
        tempi2h.push_back({ -1 * (this->lRate) * hError[i][0] * (si * ((double)1 - si)) });
    }
    Matrix<double> deltaWh2o; //hidden to output
    Matrix<double> deltaWi2h; //input to hidden

    deltaWh2o = temph2o * MM::transpose(this->hiddenToOutput.getInputs());
    deltaWi2h = tempi2h * MM::transpose(this->inputToHidden.getInputs());

    this->hiddenToOutput.setWeights(this->hiddenToOutput.getWeights() - deltaWh2o);
    this->inputToHidden.setWeights(this->inputToHidden.getWeights() - deltaWi2h);
}

//returns 1 if the output is correct
//returns 0 if the output is incorrect
bool NeuralNetwork::test(int ans, std::vector<double> input) {
    // Query the neural network
    query(input);
    Matrix<double> results = this->hiddenToOutput.getOutput();

    // Find the answer output by neural net
    double max = results[0][0];
	size_t answerIndex = 0;
	for (size_t i = 0; i < results.size(); i++) {
		if (results[i][0] > max) {
			answerIndex = i;
			max = results[i][0];
		}
	}
    
    // Compare the answer to the answer given
	if (answerIndex == ans)
        return true;
    
	return false;
}
