#pragma once
#include "NetLayer.h"
#include "MatrixManipulation.h"

class NeuralNetwork
{
private:
	// Each connecting layer
    NetLayer inputToHidden;
    NetLayer hiddenToOutput;
    // Learning rate for adjusting weights
	double lRate;

public:
	//Constructors
	NeuralNetwork() {}
	~NeuralNetwork() {} 
	NeuralNetwork(int numInput, int numHidden, int numOutput, double learningRate);
    
	// Query Functions
	void query(std::vector<double>);
    bool test(int ans, std::vector<double>);
    
    // Training Functions
    void train(int answer, std::vector<double>);
	void backpropagation(int answer, Matrix<double> tOut);
	void adjustWeights(Matrix<double> oError, Matrix<double> hError);
};
