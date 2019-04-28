#include "stdafx.h"
#include "NeuralNetwork.h"
#define NUM_DIGITS 10
//	Private variables for reference
//	NetLayer inputToHidden;
//	NetLayer hiddenToOutput;
//	double lRate;

using namespace std;
//constructors
NeuralNetwork::NeuralNetwork(int numInput, int numHidden, int numOutput, double learningRate) {
	this->inputToHidden = NetLayer(numInput, numHidden);
	this->hiddenToOutput = NetLayer(numHidden, numOutput);
	this->lRate = learningRate;
}

Matrix<double> NeuralNetwork::query(std::vector<double> queryInput) {
	
	Matrix<double> qi; //create matrix out of input vector
	qi.push_back(queryInput);

	Matrix<double> outHidden, outFinal;

	//connect the layers and run the inputs through to create output
	this->inputToHidden.setInput(MM::transpose(qi));
	outHidden = this->inputToHidden.computeOutput();
	this->hiddenToOutput.setInput(outHidden);
	outFinal = this->hiddenToOutput.computeOutput();

	return outFinal;
}

//train the network for one input
void NeuralNetwork::train(double answer, std::vector<double> trainInput) {
	//calculate the output
	Matrix<double> trainOutput = query(trainInput);
	//cout << "tout" << endl;
	//MM::printMatrix(trainOutput);
	//cout << endl << endl;

	//backpropagate errors and then within adjust weights
	//cout << "before weight changes" << endl;
	//MM::printMatrix(this->hiddenToOutput.getWeights());
	backpropagation(answer, trainOutput);
	//cout << "after weight changes" << endl;
	//ZXMM::printMatrix(this->hiddenToOutput.getWeights());

	
}

//Back propogation to generate error rate for output layer and hidden layer
void NeuralNetwork::backpropagation(double answer, Matrix<double> tOut) {
	//calculate the error for output layer
	//cout << "answer = " << answer << endl << endl;

	//cout << "train output" << endl;
	//MM::printMatrix(tOut);
	//cout << endl;

	Matrix<double> outputError;
	for (int i = 0; i < NUM_DIGITS; i++) { //calculate error rate for each digit
		if (i == answer) {
			outputError.push_back({ 0.99 - tOut[i][0] });
		}
		else {
			outputError.push_back({ 0.01 - tOut[i][0] });
		}
	}
	
	//cout << "output error" << endl;
	//MM::printMatrix(outputError);

	//calculate the error for hidden layer
	Matrix<double> errorsHidden =  MM::transpose(this->hiddenToOutput.getWeights()) * outputError;
	//cout << "here";
	//adjust the weights using the error calculated
	adjustWeights(outputError, errorsHidden);
}

//adjust the weights according to the output error and the hidden layer error
void NeuralNetwork::adjustWeights(Matrix<double> oError, Matrix<double> hError) {
	Matrix<double> deltaW; //hidden to output
	Matrix<double> deltaW2; //input to hidden

	Matrix<double> temp;
	Matrix<double> temp2;

	//cout << "oerror" << endl;
	//MM::printMatrix(oError);
	//cout << endl << "herror" << endl;
	//MM::printMatrix(hError);
	//cout << endl;

	for (size_t i = 0; i < oError.size(); i++) {
		double currentOut = this->hiddenToOutput.getOutput()[i][0];
		temp.push_back({-1*(this->lRate) * oError[i][0] * currentOut * (1 - currentOut)});
		//cout << "before " << oError[i][0] << " after " << -1 * (this->lRate) * oError[i][0] * currentOut * (1 - currentOut) << endl;
	}
	for (size_t i = 0; i < hError.size(); i++) {
		double currentOut2 = this->inputToHidden.getOutput()[i][0];
		temp2.push_back({-1*(this->lRate) * hError[i][0] * currentOut2 * (1 - currentOut2)});
	}

	//deltaW = temp * MM::transpose(this->inputToHidden.getOriginalOutput());
	deltaW = temp * MM::transpose(this->hiddenToOutput.getInputs());
	deltaW2 = temp2 * MM::transpose(this->inputToHidden.getInputs());

	this->hiddenToOutput.setWeights(this->hiddenToOutput.getWeights() - deltaW);
	this->inputToHidden.setWeights(this->inputToHidden.getWeights() - deltaW2);
}

//returns 1 if the output is correct
//returns 0 if the output is incorrect
int NeuralNetwork::test(int ans, std::vector<double> input) {
	Matrix<double> results = query(input);
	//cout << "target: " << ans << endl;
	//MM::printMatrix(results);
	//cout << endl;
	int index = 0;
	double max = 0;
	for (size_t i = 0; i < results.size(); i++) {
		if (results[i][0] > max) {
			index = i;
			max = results[i][0];
		}
	}
	if (index == ans) return 1;
	//cout << ans << " ans -- index  " << index << endl;
	return 0;
}
/*
int main() {
	//NeuralNetwork::NeuralNetwork(int numInput, int numHidden, int numOutput, double learningRate) {
	NeuralNetwork nn(2,2,2,1);

	Matrix<double> input;
	input.push_back({ 0.9 });
	input.push_back({ 0.1 });
	input.push_back({ 0.8 });
	//input.push_back({ { { 0.9 }, { 0.1 }, { 0.8 } } });
	nn.inputToHidden.setInput(input);

	Matrix<double> weights;
	weights.push_back({ 0.9, 0.3, 0.4 });
	weights.push_back({ 0.2, 0.8, 0.2 });
	weights.push_back({ 0.1, 0.5, 0.6 });
	nn.inputToHidden.setWeights(weights);

	Matrix<double> weights2;
	weights2.push_back({ 0.3, 0.7, 0.5 });
	weights2.push_back({ 0.6, 0.5, 0.2 });
	weights2.push_back({ 0.8, 0.1, 0.9 });
	nn.hiddenToOutput.setWeights(weights2);
	
	std::cout << "output matrix: " << endl;
	MM::printMatrix(nn.query({ 0.9,0.1,0.8 }));
}

*/