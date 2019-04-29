//#include "stdafx.h"
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

//\/\/\/\/\/\/\/\/\/\/
// public functions //
//\/\/\/\/\/\/\/\/\/\/

//Compute the matrix multiplication and apply the sigmoid function to the output
Matrix<double> NetLayer::computeOutput() {
	//matrix multiplication 
	//X = W * I
	
	using namespace std;
	this->outputs = this->weights*this->inputs; //the work
	
	//save output before applying sigmoid for back propagation
//    this->setOriginalOutput(outputs);
	this->beforeSig = this->outputs;

	//apply activation function to the matrix
	activation(this->outputs);
    
    
//    this->setOutput()
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

//\/\/\/\/\/\/\/\/\/\//
// private functions //
//\/\/\/\/\/\/\/\/\/\//

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


int main() {
    
    // Testing case 1
    /////////////////
	NetLayer n;
    Matrix<double> inputs{ {1.0}, {0.5} };
    Matrix<double> weights{ {0.9, 0.3}, {0.2, 0.8}};

	n.setInput(inputs);
    n.setWeights(weights);
    
    std::cout << "Case #1 -Input and weights before computation-" << std::endl;
    std::cout << "Input vector:" << std::endl;
	MM::printMatrix(n.getInputs());
	std::cout << std::endl;
    std::cout << "Weight matrix:" << std::endl;
	MM::printMatrix(n.getWeights());
	std::cout << std::endl;

    std::cout << "Case #1 -Outputs after computation-" << std::endl;
    n.computeOutput();
    std::cout << "Original output before sigmoid function: " << std::endl;
    MM::printMatrix(n.getOriginalOutput());
    std::cout << std::endl;
    std::cout << "Output after sigmoid function: " << std::endl;
    MM::printMatrix(n.getOutput());
    
    // Testing case 2
    /////////////////
    NetLayer n2;
    Matrix<double> i{ {0.9},{0.1},{0.8} };
    Matrix<double> w{ {0.9,0.3,0.4}, {0.2,0.8,0.2}, {0.1,0.5,0.6} };
    n2.setInput(i);
    n2.setWeights(w);
    
    std::cout << "Case #2 -Input and weights before computation-" << std::endl;
    std::cout << "Input vector:" << std::endl;
    MM::printMatrix(n2.getInputs());
    std::cout << std::endl;
    std::cout << "Weight matrix:" << std::endl;
    MM::printMatrix(n2.getWeights());
    std::cout << std::endl;
    
    std::cout << "Case #2 -Outputs after computation-" << std::endl;
    n2.computeOutput();
    std::cout << "Original output before sigmoid function: " << std::endl;
    MM::printMatrix(n2.getOriginalOutput());
    std::cout << std::endl;
    std::cout << "Output after sigmoid function: " << std::endl;
    MM::printMatrix(n2.getOutput());
    
    // Testing case 3
    /////////////////
    NetLayer n3;
    Matrix<double> i2 = n2.getOutput();
    Matrix<double> w2{ {0.3,0.7,0.5}, {0.6,0.5,0.2}, {0.8,0.1,0.9} };
    n3.setInput(i2);
    n3.setWeights(w2);
    
    std::cout << "Case #3 -Input and weights before computation-" << std::endl;
    std::cout << "Input vector:" << std::endl;
    MM::printMatrix(n3.getInputs());
    std::cout << std::endl;
    std::cout << "Weight matrix:" << std::endl;
    MM::printMatrix(n3.getWeights());
    std::cout << std::endl;
    
    std::cout << "Case #2 -Outputs after computation-" << std::endl;
    n3.computeOutput();
    std::cout << "Original output before sigmoid function: " << std::endl;
    MM::printMatrix(n3.getOriginalOutput());
    std::cout << std::endl;
    std::cout << "Output after sigmoid function: " << std::endl;
    MM::printMatrix(n3.getOutput());
}

