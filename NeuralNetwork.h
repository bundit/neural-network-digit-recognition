#pragma once
#include "stdafx.h"
#include "NetLayer.h"
#include "MatrixManipulation.h"
#include <iostream>


class NeuralNetwork
{
private:
	//Each connecting layer
	//NetLayer inputToHidden;
	//NetLayer hiddenToOutput;
	//learning rate
	double lRate;

public:
	//Constructors
	NetLayer inputToHidden;
	NetLayer hiddenToOutput;

	NeuralNetwork() {} //empty
	~NeuralNetwork() {} 
	NeuralNetwork(int numInput, int numHidden, int numOutput, double learningRate);

	//functions
	void train(double answer, std::vector<double>);
	Matrix<double> query(std::vector<double>);

	void backpropagation(double, Matrix<double> tOut);
	void adjustWeights(Matrix<double> oError, Matrix<double> hError);
	int test(int ans, std::vector<double>);

};