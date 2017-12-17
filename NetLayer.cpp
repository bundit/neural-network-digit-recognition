#include "stdafx.h"
#include "NetLayer.h"
#include "MatrixManipulation.h"
#include <iostream>

using namespace std;
/*
int numInputs;
int numOutputs;

Matrix<T> inputs;
Matrix<T> weights;
Matrix<T> outputs;
*/
template<typename T>
NetLayer<T>::NetLayer(int iInput, int iOutput, vector<T> inputList) {
	numInputs = iInput;
	numOutputs = iOutput;
	inputs = inputList;
}

template<typename T>
void NetLayer<T>::giveRandomWeights() {
	
}
