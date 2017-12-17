#pragma once
#include "MatrixManipulation.h"
#include <vector>

//template<typename T>
//using Matrix = vector<vector<T>>;
//using namespace std;

//Layer can be input layer, hidden, or output layer
class NetLayer
{
private:

	int numInputs;
	int numOutputs;

	Matrix<double> inputs;
	Matrix<double> weights;
	Matrix<double> outputs;

	void giveRandomWeights();

public:
	//constructors
	NetLayer() {}
	~NetLayer() {}
	NetLayer(int iInput, int iOutput);

	//functions
	void setInput(Matrix<double>);
	void setWeights(Matrix<double>);
	double sigmoid(double x);
	void activation(Matrix<double> col);
	Matrix<double> computeOutput();

};