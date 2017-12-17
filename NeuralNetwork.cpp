#include "stdafx.h"
#include "NeuralNetwork.h"

/*
NetLayer inputToHidden;
NetLayer hiddenToOutput;
double lRate;
*/
//constructors
NeuralNetwork::NeuralNetwork(int numInput, int numHidden, int numOutput, double learningRate) {
	//NetLayer(int iInput, int iOutput, Matrix<double> inputList)
	this->inputToHidden = NetLayer(numInput, numHidden);
	this->hiddenToOutput = NetLayer(numHidden, numOutput);
	this->lRate = learningRate;

}

void NeuralNetwork::train(std::vector<double> trainInput) {

}

Matrix<double> NeuralNetwork::query(std::vector<double> queryInput) {
	Matrix<double> qi;
	qi.push_back(queryInput);

	Matrix<double> outHidden, outFinal;

	this->inputToHidden.setInput(MM::transpose(qi));
	outHidden = this->inputToHidden.computeOutput();
	this->hiddenToOutput.setInput(outHidden);
	outFinal = this->hiddenToOutput.computeOutput();

	return outFinal;
}

