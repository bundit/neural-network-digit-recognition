#pragma once
#include "MatrixManipulation.h"
#include <vector>

//template<typename T>
//using Matrix = vector<vector<T>>;
using namespace std;

//Layer can be input layer, hidden, or output layer
template<typename T>
class NetLayer
{
private:

	int numInputs;
	int numOutputs;

	vector<T> inputs;
	Matrix<T> weights;
	vector<T> outputs;

	void giveRandomWeights();

public:
	//constructors
	NetLayer() {}
	~NetLayer() {}
	NetLayer(int iInput, int iOutput, vector<T> inputList);

	//functions
	void computeOutput();

};