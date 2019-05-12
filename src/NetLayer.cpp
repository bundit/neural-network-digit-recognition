//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//                           //
//       NetLayer.cpp        //
//  Author: Bundit Hongmanee //
//                           //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
#include "../include/NetLayer.h"
#include "../include/MatrixManipulation.h"
#include <random>
#include <iostream>


//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//  Private variables        //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//  int numInputs;           //
//  int numOutputs;          //
//  Matrix<T> inputs;        //
//  Matrix<T> weights;       //
//  Matrix<T> outputs;       //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\//

// Constructor for initializing the Layer
// iInput - number of input nodes
// iOutput - number of output nodes
NetLayer::NetLayer(int iInput, int iOutput) {
	this->numInputs = iInput;
	this->numOutputs = iOutput;
	this->giveRandomWeights();
}

// Compute the matrix multiplication and apply the sigmoid function to the output
// The core function of a layer to feed forward input through the network
Matrix<double> NetLayer::computeOutput() {
    // X = W * I
    this->outputs = this->weights * this->inputs;
    // Apply sigmoid to output
    activation(this->outputs);
    
    return this->outputs;
}

// Compute the sigmoid function
// Standard sigmoid function
double sigmoid(double x) {
    return 1 / (1 + std::exp(-x));
}

// Applies the sigmoid function to every output node of this->outputs
void NetLayer::activation(Matrix<double> col) {
	for (size_t i = 0; i < col.size(); i++) {
        this->outputs[i][0] = sigmoid(col[i][0]);
	}
}

// Generate and assign random weights for this layer
// Given a range from -1/sqrt(numInput) to +1/sqrt(numInput)
void NetLayer::giveRandomWeights() {
//    srand(1000); //can be used to generate a specific seed of random numbers
    double minmax = 1 / sqrt(this->numInputs); //define the + and - range
    double rand; // hold the next random weight value
    
	for (int i = 0; i < this->numOutputs; i++) {
		this->weights.push_back({});
		for (int j = 0; j < this->numInputs; j++) {
            //generate
			std::random_device rd;   
			std::mt19937 gen(rd());
			//std::mt19937 gen(rand()); //my seed
			std::uniform_real_distribution<double> dis(-minmax, minmax);

			rand = dis(gen); //Generate a new random value
			this->weights[i].push_back(rand);
		}
	}
}

// Set the input list to prepare for computing output
void NetLayer::setInput(Matrix<double> inputList) {
	this->inputs = inputList;
}
// Set your own weights, used for back propogation and adjusting weights
void NetLayer::setWeights(Matrix<double> s) {
	this->weights = s;
}

// Getters
Matrix<double> NetLayer::getInputs() {
	return this->inputs;
}
Matrix<double> NetLayer::getWeights() {
	return this->weights;
}
Matrix<double> NetLayer::getOutput() {
	return this->outputs;
}


// Testing method - not paramount to neural network functionality
void testSingleLayer() {
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
    std::cout << std::endl;
    std::cout << "Output after sigmoid function: " << std::endl;
    MM::printMatrix(n3.getOutput());
    std::cout << "Expected Output:" << std::endl;
    std::cout << "0.726" << std::endl << "0.708" << std::endl << "0.778" << std::endl;
}

//int main() {
//    testSingleLayer();
//}
