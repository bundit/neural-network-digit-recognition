#include "stdafx.h"
#include "NetLayer.h"
#include "MatrixManipulation.h"
#include <iostream>
#include <random>

//using namespace std;

/*
int numInputs;
int numOutputs;

Matrix<T> inputs;
Matrix<T> weights;
Matrix<T> outputs;
*/

NetLayer::NetLayer(int iInput, int iOutput) {
	this->numInputs = iInput;
	this->numOutputs = iOutput;
	this->giveRandomWeights();
	//MM::printMatrix(this->weights);

}
//public functions
void NetLayer::setInput(Matrix<double> inputList) {
	this->inputs = inputList;
}

Matrix<double> NetLayer::computeOutput() {
	/*
	std::cout << "computing these matrices" << std::endl;
	MM::printMatrix(this->inputs);
	std::cout << std::endl;
	MM::printMatrix(this->weights);
	std::cout << std::endl;
	*/

	//matrix multiplication 
	//X = W*I
	this->outputs = this->weights*this->inputs;
	
	//apply activation function to the matrix
	activation(this->outputs);
	
	return this->outputs;
}

void NetLayer::activation(Matrix<double> col) {
	for (size_t i = 0; i < col.size(); i++) {
		for (size_t j = 0; j < col[0].size(); j++) {
			this->outputs[i][j] = NetLayer::sigmoid(col[i][j]);
		}
	}
}

double NetLayer::sigmoid(double x) {
	double y = 1 / (1 + std::exp(-x));
	return y;
}

//private functions
void NetLayer::giveRandomWeights() {
	//srand(1000);

	for (int i = 0; i < this->numInputs; i++) {
		this->weights.push_back({});
		for (int j = 0; j < this->numOutputs; j++) {
			double range = 1 / sqrt(this->numInputs);
			std::random_device rd;  //Will be used to obtain a seed for the random number engine
			std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
			//std::mt19937 gen(rand()); //my seed
			std::uniform_real_distribution<double> dis(-range, range);

			double rand = dis(gen); //Each call to dis(gen) generates a new random double		
			this->weights[i].push_back(rand);
		}
	}
}

//for testing purposes
void NetLayer::setWeights(Matrix<double> s) {
	this->weights = s;
}


/*
int main() {
Matrix<double> inputlist;
inputlist.push_back({ 1, 2, 3 });
//NetLayer l =
NetLayer l(5, 5, inputlist);
}
*/
