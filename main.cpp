#include "stdafx.h"
#include "MatrixManipulation.h"
#include "NetLayer.h"
#include "NeuralNetwork.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//Variables for main function testing of the neural network
string trainData = "mnist_train.csv"; //set the data file to train on
string testData = "mnist_test.csv"; //test file
int inputNodes = 28 * 28;
int hiddenLayersNodes = 100;
int outputNodes = 10;
double learnRate = 0.3;


void readFromFileAndTrain(string data, NeuralNetwork n);
void testNetwork(string data, NeuralNetwork n);
void printResults(int count, int total);

int main()
{
	//initalize the network
	cout << "Initialized neural network with: " <<endl << inputNodes << " input nodes, " << endl;
	cout << hiddenLayersNodes << " hidden layer nodes, " << endl;
	cout << outputNodes << " output nodes, and " << endl;
	cout << learnRate << " learning rate..." << endl;
	NeuralNetwork n(inputNodes, hiddenLayersNodes, outputNodes, learnRate);	

	
	//train the network
	cout << endl << "Training the network with " << trainData << "..." << endl;
	readFromFileAndTrain(trainData, n);

	//test the network 
	cout << endl << "Testing the network with " << testData << "..." << endl;
	testNetwork(testData, n);

	return 0;
}


//CSV file supplied as a variable on the top of the file
//Will read from 
void readFromFileAndTrain(string data, NeuralNetwork n) {
	int stop = 0;
	ifstream infile(data);
	while (infile)
	{
		string s;
		if (!getline(infile, s)) break;

		istringstream ss(s);
		vector <double> dataPoints;

		double ans = 0; //stores the data to compare the result to
		int c = 0;
		while (ss && c < 785)
		{
			string s;
			if (!getline(ss, s, ',')) break;
			if (c == 0) {
				ans = std::stoi(s);
			}
			else
			{
				dataPoints.push_back(((std::stoi(s)/255.0)*0.99)+0.01);
			}
			c++;
		}
		
		//call the training routine now that our datapoints have been parsed
		n.train(ans, dataPoints);
		stop++;
		if (stop > 100) return;
	}

	if (!infile.eof())
	{
		cerr << "END OF FILE!" << endl;
	}
}

//test the data from the file given using the trained neural network
void testNetwork(string data, NeuralNetwork n) {
	int count = 0; //counts the number of correct inputs
	int total = 0; //total number of tests
	int stop = 0;

	ifstream infile(data);
	while (infile)
	{
		string s;
		if (!getline(infile, s)) break;

		istringstream ss(s);
		vector <double> dataPoints;

		int ans = 0; //stores the data to compare the result to
		int c = 0;
		while (ss && c < 785)
		{
			string s;
			if (!getline(ss, s, ',')) break;
			if (c == 0) ans = std::stoi(s);
			else
			{
				dataPoints.push_back(((std::stoi(s) / 255.0)*0.99) + 0.01);
			}
			c++;
		}
		//cout << "ans ===" << ans << endl;
		//call the test routine
		count += n.test(ans, dataPoints);
		total++;

		stop++;
		if (stop > 20) break;
	}

	printResults(count, total);
}

//print the results given the count and total amount of inputs
void printResults(int count, int total) {
	cout << "Total of " << total << " inputs tested." << endl;
	cout << count << " verified correct." << endl;
	cout << (double)count / total *100 << "% accuracy." << endl;
}