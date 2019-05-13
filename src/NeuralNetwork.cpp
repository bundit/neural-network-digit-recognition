//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//                           //
//     NeuralNetwork.cpp     //
//  Author: Bundit Hongmanee //
//                           //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
#define NUM_DIGITS 10
#include "../include/NeuralNetwork.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

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

// Query the neural network
// queryInput - the vector of input to the neural net
// Saves the output to this->hiddenToOut.output
void NeuralNetwork::query(std::vector<double> queryInput) {
	// Set the input to column vector - necessary in order to appropriately perform matrix multiplication
    Matrix<double> qi;
    qi.push_back(queryInput);
    qi = MM::transpose(qi);
    
    // Feed forward through neural net
    this->inputToHidden.setInput(qi);
    this->inputToHidden.computeOutput();
    this->hiddenToOutput.setInput(inputToHidden.getOutput());
    this->hiddenToOutput.computeOutput();
}

// Train the network for one input
// answer - the expected answer
// trainInput - the vector of input to the neural network
void NeuralNetwork::train(int answer, std::vector<double> trainInput) {
	//calculate the output
    query(trainInput);

	//backpropagate errors and then within adjust weights
	this->backpropagation(answer, this->hiddenToOutput.getOutput());
}

// Back propogate errors from the output layer to the hidden layer
// Calculate errors to use to adjust the weight matrices
void NeuralNetwork::backpropagation(int answer, Matrix<double> tOut) {
	// Calculate the error for output layer
	Matrix<double> outputError;
	for (size_t i = 0; i < tOut.size(); i++) {
		if (i == (size_t) answer) {
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
// oError - error column vector for output layer
// hError - error column vector for hidden layer
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

// Query an input and test it against the answer given
// Returns 1 if the output is correct
// Returns 0 if the output is incorrect
bool NeuralNetwork::test(int ans, std::vector<double> input) {
    // Query the neural network
    query(input);
    Matrix<double> results = this->hiddenToOutput.getOutput();

    // Find the answer output by neural net
    double max = results[0][0];
	size_t answerIndex = 0;
	for (size_t i = 0; i < results.size(); i++) {
		if (results[i][0] > max) {
			answerIndex = (size_t) i;
			max = results[i][0];
		}
	}
    
    // Compare the answer to the answer given
	if (answerIndex == (size_t) ans)
        return true;
    
	return false;
}

// Save the neural network's weight matrices to file
// Only the weight matrices are needed to reproduce the same neural network
// This method will completely overwrite an existing file
void NeuralNetwork::serialize(std::string file) {
    using namespace std;
    
    Matrix<double> i2h = this->inputToHidden.getWeights();
    Matrix<double> h2o = this->hiddenToOutput.getWeights();
    
    // Open file stream to write to
    ofstream fout;
    fout.open(file);
    
    if (!fout.is_open()) {
        cout << "Error opening file " << file << endl;
    }
    
    fout << this->lRate << endl;
    // Print one empty line in between
    fout << endl;
    
    // Print input-hidden weight matrix first
    for (size_t i = 0; i < i2h.size(); i++) {
        for (size_t j = 0; j < i2h[0].size(); j++) {
            // Print to file values separated by spaces
            fout << i2h[i][j] << " ";
        }
        fout << endl;
    }
    // Print one empty line in between
    fout << endl;
    
    // Print hidden-output weight matrix second
    for (size_t i = 0; i < h2o.size(); i++) {
        for (size_t j = 0; j < h2o[0].size(); j++) {
            // Print to file values separated by spaces
            fout << h2o[i][j] << " ";
        }
        fout << endl;
    }
    
    fout.close();
}

// Load neural network weights from file
// The exact reverse operations as NeuralNetwork::serialize method
void NeuralNetwork::deserialize(std::string file) {
    using namespace std;
    
    double learningRate = 0.3; // Default
    Matrix<double> i2h;
    Matrix<double> h2o;
    
    string line;
    ifstream fin (file);
    
    if (!fin.is_open()) {
        cout << "Error opening file " << file << endl;
    }
    
    // First get the learning rate
    while (getline(fin, line)) {
        if (line.length() == 0) break;
//        getline(fin, line);
        learningRate = stod(line);
    }
    
    int row = 0;
    while (getline(fin, line)) {
        if (line.length() == 0) break;
        string val;
        stringstream s(line);
        i2h.push_back({});
        
        
        while (getline(s, val, ' ')) {
            i2h[row].push_back(stod(val));
        }
        row++;
    }
    row = 0;
    while (getline(fin, line)) {
        string val;
        stringstream s(line);
        h2o.push_back({});
        
        while (getline(s, val, ' ')) {
            h2o[row].push_back(stod(val));
        }
        row++;
    }
    fin.close();
    
    // Set the instance variables
    this->lRate = learningRate;
    this->inputToHidden.setWeights(i2h);
    this->hiddenToOutput.setWeights(h2o);
}

