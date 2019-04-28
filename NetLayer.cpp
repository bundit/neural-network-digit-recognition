#include "stdafx.h"
#include "NetLayer.h"
#include "MatrixManipulation.h"
#include <iostream>
#include <random>

//	Private variables for reference
//
//	int numInputs;
//	int numOutputs;
//
//	Matrix<T> inputs;
//	Matrix<T> weights;
//	Matrix<T> outputs;
//

//Constructor for initializing the Layer 
NetLayer::NetLayer(int iInput, int iOutput) {
	this->numInputs = iInput;
	this->numOutputs = iOutput;
	this->giveRandomWeights();
	//MM::printMatrix(this->weights);

}
//public functions

//Compute the matrix multiplication and apply the sigmoid function to the output
Matrix<double> NetLayer::computeOutput() {
	//matrix multiplication 
	//X = W*I
	
	using namespace std;
	this->outputs = this->weights*this->inputs; //the work
	
	//save output before applying sigmoid for back propagation
	this->beforeSig = outputs; 

	//apply activation function to the matrix
	activation(this->outputs);
	
	return this->outputs;
}

//Applies the sigmoid function to every output node
//*note* this automatically sets the private variable list of output
void NetLayer::activation(Matrix<double> col) {
	for (size_t i = 0; i < col.size(); i++) {
		for (size_t j = 0; j < col[0].size(); j++) {
			this->outputs[i][j] = NetLayer::sigmoid(col[i][j]);
		}
	}
}

//Compute the sigmoid function
double NetLayer::sigmoid(double x) {
	double y = 1 / (1 + std::exp(-x));
	return y;
}

//private functions

//Generate and assign random weights for this layer
//Given a range from -1/sqrt(numInput) to +1/sqrt(numInput)
void NetLayer::giveRandomWeights() {
	//srand(1000); //can be used to generate a specific seed of random numbers 

	for (int i = 0; i < this->numOutputs; i++) {
		this->weights.push_back({});
		for (int j = 0; j < this->numInputs; j++) {
			double minmax = 1 / sqrt(this->numInputs); //define the + and - range
			std::random_device rd;   
			std::mt19937 gen(rd());
			//std::mt19937 gen(rand()); //my seed
			std::uniform_real_distribution<double> dis(-minmax, minmax);

			double rand = dis(gen); //Each call to dis(gen) generates a new random double		
			this->weights[i].push_back(rand);
		}
	}
}

//setters
//Set the input list to prepare for computing output
void NetLayer::setInput(Matrix<double> inputList) {
	this->inputs = inputList;
}
//Set your own weights, used for back propogation and adjusting weights
void NetLayer::setWeights(Matrix<double> s) {
	this->weights = s;
}

//getters
Matrix<double> NetLayer::getInputs() {
	return this->inputs;
}
Matrix<double> NetLayer::getWeights() {
	return this->weights;
}
Matrix<double> NetLayer::getOutput() {
	return this->outputs;
}
Matrix<double> NetLayer::getOriginalOutput() {
	return this->beforeSig;
}

/*
int main() {
	NetLayer n;
	Matrix<double> inputs;
	inputs.push_back({ 1.0 });
	inputs.push_back({ 0.5 });

	Matrix<double> weights;
	weights.push_back({ 0.9, 0.3 });
	weights.push_back({ 0.2, 0.8 });

	n.setInput(inputs);
	n.setWeights(weights);

	MM::printMatrix(inputs);
	std::cout << std::endl;
	MM::printMatrix(weights);
	std::cout << std::endl;

	MM::printMatrix(n.computeOutput());
}
*/