#pragma once
#include "stdafx.h"
#include "NetLayer.h"
#include "MatrixManipulation.h"
#include <iostream>


class NeuralNetwork
{
private:
	NetLayer inputToHidden;
	NetLayer hiddenToOutput;
	double lRate;

public:
	//Constructors
	NeuralNetwork() {}
	~NeuralNetwork() {}
	NeuralNetwork(int numInput, int numHidden, int numOutput, double learningRate);
	//main functions
	void train(std::vector<double>);
	Matrix<double> query(std::vector<double>);
	//sub routines
	Matrix<double> sigmoid(Matrix<double> hidden);
	void backpropogate();

};