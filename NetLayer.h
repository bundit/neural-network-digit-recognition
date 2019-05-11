#pragma once
#include "MatrixManipulation.h"

// NetLayer defines a construct of input layer, weights, and output nodes
// We use two, one for input to hidden then another from hidden to output
class NetLayer
{
private:
    // Instance Variables
	int numInputs; 
	int numOutputs;
	Matrix<double> inputs; 
	Matrix<double> weights;
	Matrix<double> outputs;
	
    // Private functions
	void giveRandomWeights();

public:
	// Constructor
	NetLayer() {}
    NetLayer(int iInput, int iOutput);
    
    // Destructor
    ~NetLayer() {}

	//functions
	void activation(Matrix<double> col);
	Matrix<double> computeOutput();
    
    // Setters
    void setInput(Matrix<double>);
    void setWeights(Matrix<double>);
    
    // Getters
	Matrix<double> getInputs();
	Matrix<double> getWeights();
	Matrix<double> getOutput();
};
