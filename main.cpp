//#include "stdafx.h"
#include "MatrixManipulation.h"
#include "NetLayer.h"
#include "NeuralNetwork.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// MNIST data files
string TRAIN_DATA = "/Users/bundit/code/neural-net/neural-net/mnist_train.csv"; //set the data file to train on
string TEST_DATA = "/Users/bundit/code/neural-net/neural-net/mnist_test.csv"; //test file

// Neural Network parameters
int INPUT_NODES = 28 * 28;
int HIDDEN_NODES = 100;
int OUTPUT_NODES = 10;
double LEARNING_RATE = .3;

// Training and testing parameters
int TRAINING_COUNT = INT_MAX;
int TESTING_COUNT = INT_MAX;

// Testing function declarations
void readFromFileAndTrain(string data);
void testNetwork(string data);
void printResults(int count, int total);

NeuralNetwork n;

//\/\/\/\/\/\/\/\/\//
//       Main      //
//\/\/\/\/\/\/\/\/\//
int main()
{
    //initalize the network
    cout << "Initialized neural network with: " << endl << INPUT_NODES << " input nodes, " << endl;
    cout << HIDDEN_NODES << " hidden layer nodes, " << endl;
    cout << OUTPUT_NODES << " output nodes, and " << endl;
    cout << LEARNING_RATE << " learning rate..." << endl;
    // NeuralNetwork(int numInput, int numHidden, int numOutput, double learningRate)
    n = NeuralNetwork(INPUT_NODES, HIDDEN_NODES, OUTPUT_NODES, LEARNING_RATE);
    
//    cout << endl << endl << "I2H ------------------------" << endl;
//    MM::printMatrix(n.getI2H().getWeights());
//    cout << endl << endl << "h2O ------------------------" << endl;
//    MM::printMatrix(n.getH2O().getWeights());
    
    //train the network
    cout << endl << "Training the network with " << TRAIN_DATA << "..." << endl;
    readFromFileAndTrain(TRAIN_DATA);
    
    
//    cout << endl << endl << "I2H ------------------------" << endl;
//    MM::printMatrix(n.getI2H().getWeights());
//    cout << endl << endl << "h2O ------------------------" << endl;
//    MM::printMatrix(n.getH2O().getWeights());

    //test the network
    cout << endl << "Testing the network with " << TEST_DATA << "..." << endl;
    testNetwork(TEST_DATA);

    return 0;
}

void readFromFileAndTrain(string data) {
    string line; //to hold each line
    ifstream f (data); //open the file
    if (!f.is_open()) {
        cout << "Error while opening file " << data << endl;
    }
    int trainCount = 0; //train counter
    while (getline(f, line) && trainCount < TRAINING_COUNT) { //while has line
        string val; //to hold value read in
        stringstream s (line);
        vector<double> row; //to hold input values 
        
        getline (s, val, ','); //get first value separated by comma and store it in val
        int ans = stoi(val); //cast to
        
        while (getline (s, val, ',')) {
            row.push_back(((stod(val) / 255.0 * 0.99) + 0.01));
        }
        
        // check that we are reading in the appropriate number of values
        if (row.size() != INPUT_NODES) {
            cout << "Error with input size" << endl;
        }
        
        n.train(ans, row);
        trainCount++; //increment number of times trained
    }
    f.close();
}

void testNetwork(string data) {
    int correct = 0; //count of number of tests we've done
    int numTest = 0; //number of tests to do
    
    string line; //string to hold one line
    ifstream f (data); //open the file
    if (!f.is_open()) {
        cout << "Error while opening file " << data << endl;
    }
    
    while (getline(f, line) && numTest < TESTING_COUNT) { //read a line
        string val; //to hold one value at a time
        stringstream s (line);
        vector<double> row; //to hold one set of input
        
        getline (s, val, ','); //get the first value
        int ans = stoi(val); //store it as the answer
        
        while (getline (s, val, ',')) { //get the rest of the line
            row.push_back(((stod(val) / 255.0 * 0.99) + 0.01));
            
        }
        
        if (row.size() != INPUT_NODES) {
            cout << "Error with input size" << endl;
        }
        
        int isCorrect = n.test(ans, row);
        
        if (isCorrect) {
             correct++;
        }
        numTest++;
    }
    f.close();
    
    printResults(correct, numTest);
}

//CSV file supplied as a variable on the top of the file
//Will read from
//void readFromFileAndTrain(string data, NeuralNetwork n) {
//    int stop = 0;
//    ifstream infile(data);
//    while (infile)
//    {
//        string s;
//        if (!getline(infile, s)) break;
//
//        istringstream ss(s);
//        vector <double> dataPoints;
//
//        double ans = 0; //stores the data to compare the result to
//        int c = 0;
//        while (ss && c < 785)
//        {
//            string s;
//            if (!getline(ss, s, ',')) break;
//            if (c == 0) {
//                ans = std::stoi(s);
//            }
//            else {
//                dataPoints.push_back(((std::stoi(s)/255.0)*0.99)+0.01);
//            }
//            c++;
//        }
//
//        //call the training routine now that our datapoints have been parsed
//        n.train(ans, dataPoints);
//        stop++;
//        if (stop > 100) return;
//    }
//    cout << stop << endl;
//
//    if (!infile.eof())
//    {
//        cerr << "END OF FILE!" << endl;
//    }
//}

//test the data from the file given using the trained neural network
//void testNetwork(string data, NeuralNetwork n) {
//    int count = 0; //counts the number of correct inputs
//    int total = 0; //total number of tests
//    int stop = 0;
//
//    ifstream infile(data);
//    while (infile)
//    {
//        string s;
//        if (!getline(infile, s)) break;
//
//        istringstream ss(s);
//        vector <double> dataPoints;
//
//        int ans = 0; //stores the data to compare the result to
//        int c = 0;
//        while (ss && c < 785)
//        {
//            string s;
//            if (!getline(ss, s, ',')) break;
//            if (c == 0) ans = std::stoi(s);
//            else
//            {
//                dataPoints.push_back(((std::stoi(s) / 255.0)*0.99) + 0.01);
//            }
//            c++;
//        }
//        //cout << "ans ===" << ans << endl;
//        //call the test routine
//        count += n.test(ans, dataPoints);
//        total++;
//
//        stop++;
//        if (stop > 20) break;
//    }
//
//    printResults(count, total);
//}

//print the results given the count and total amount of inputs
void printResults(int count, int total) {
	cout << "Total of " << total << " inputs tested." << endl;
	cout << count << " verified correct." << endl;
	cout << (double)count / total * 100 << "% accuracy." << endl;
}
