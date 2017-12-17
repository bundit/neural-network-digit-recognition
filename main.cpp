#include "stdafx.h"
#include "MatrixManipulation.h"
#include "NetLayer.h"
#include "NeuralNetwork.h"

using namespace std;

int main()
{
	//X = W * I
	/*
	Matrix<double> weights;
	weights.push_back({0.9, 0.3, 0.4});
	weights.push_back({0.2, 0.8, 0.2});
	weights.push_back({0.1, 0.5, 0.6});

	//cout << "length is " << m.size() << endl;
	//cout << "length[] is " << m[0].size() << endl;
	cout << "weights " << endl;
	MM::printMatrix(weights);
	cout << endl;

	Matrix<double> inputs;
	inputs.push_back({ 0.9, 0.1, 0.8 });


	cout << "inputs" << endl;
	MM::printMatrix(inputs);
	cout << endl;

	Matrix<double> X = weights*MM::transpose(inputs);
	cout << "X = W * I" << endl;
	MM::printMatrix(X);
	cout << endl;
	*/
	/////////
	//Netlayer testing
	/*
	Matrix<double> inputlist;
	inputlist.push_back({ 1, 2, 3 });
	//NetLayer l = 
	NetLayer l(3, 3);
	*/

	//NeuralNet testing
	NeuralNetwork n(3, 3, 3, 0);
	vector<double> in{ 0.9, 0.1, 0.8 };
	//in.push_back({ 0.9, 0.1, 0.8 });
	n.query( in );
	cout << "ended" << endl;
	return 0;
}

