#pragma once
#include "MatrixManipulation.h"
#include <vector>

//template<typename T>
//using Matrix = vector<vector<T>>;
//using namespace std;

//NetLayer defines a construct of input layer, weights, and output nodes
//We use two, one for input to hidden then another from hidden to output
class NetLayer
{
private:
	//number of input and output
	int numInputs; 
	int numOutputs;

	//Matrices for holding inputs, weights and output
	Matrix<double> inputs; 
	Matrix<double> weights;
	Matrix<double> outputs; 
	//Matrice holding output before applying sigmoid
	Matrix<double> beforeSig;
	
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

	//Getters
	Matrix<double> getInputs();
	Matrix<double> getWeights();
	Matrix<double> getOutput();
	Matrix<double> getOriginalOutput();

};