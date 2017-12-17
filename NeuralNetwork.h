#pragma once
#include "stdafx.h"
#include "NetLayer.h"
#include "MatrixManipulation.h"
#include <iostream>

template <typename T>
class NeuralNetwork
{
private:
	NetLayer<T> inputToHidden;
	NetLayer<T> hiddenToOutput;

public:
	//Constructors
	NeuralNetwork() {}
	~NeuralNetwork() {}
	NeuralNetwork(int numInput, int numHidden, int numOutput, double lRate);
	//main functions
	void train();
	void query(/*not sure input yet*/);
	//sub routines
	T sigmoid(Matrix hidden);
	void backpropogation();

};