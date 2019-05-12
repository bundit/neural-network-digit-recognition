//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//                             //
// Vanilla C++ Neural Network  //
//  Author: Bundit Hongmanee   //
//                             //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//

#include "../include/MatrixManipulation.h"
#include "../include/NetLayer.h"
#include "../include/NeuralNetwork.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;

// MNIST data files
string TRAIN_DATA = "/Users/bundit/code/neural-net/neural-net/mnist_train.csv"; //Training data set
string TEST_DATA = "/Users/bundit/code/neural-net/neural-net/mnist_test.csv";   //Testing data set

// Neural Network parameters
int INPUT_NODES = 28 * 28;  // For grayscale images of length 28 and width 28 pixels
int HIDDEN_NODES = 100;     // Arbitrary number, usually a number between OUTPUT_NODES and INPUT_NODES is recommended
int OUTPUT_NODES = 10;      // For digit recognition, 0-9 represents 10 different outputs possible
double LEARNING_RATE = .2;  // Ratio used to prevent 'overstepping' in our weight adjustments

// Training and testing parameters
// Set these to INT_MAX to train or test the whole set,
// otherwise set to a smaller number to train or test only a specific amount
int TRAINING_COUNT = INT_MAX;
int TESTING_COUNT = INT_MAX;

// Testing function declarations
void trainNetwork(string data);
void testNetwork(string data);
void printResults(int count, int total);

NeuralNetwork n;

int main (int argc, const char * argv[]) {
    
    string directory(argv[0]);
    // And we want to get rid of the program name `test`
    directory = directory.substr(0, directory.find_last_of("/"));
    // Point the directory to the program directory
    chdir(directory.c_str());
    
    cout << "Current directory is: " << getcwd(NULL, 0) << endl;
    // Print the arguments
    cout << "Initialized neural network with: " << endl << INPUT_NODES << " input nodes, " << endl;
    cout << HIDDEN_NODES << " hidden layer nodes, " << endl;
    cout << OUTPUT_NODES << " output nodes, and " << endl;
    cout << LEARNING_RATE << " learning rate..." << endl;
//    cout << full_path;
    n = NeuralNetwork(INPUT_NODES, HIDDEN_NODES, OUTPUT_NODES, LEARNING_RATE);
    // Initialize the neural network
    
    // Test the network
    cout << endl << "Testing 0.05x5" << endl;
    n = NeuralNetwork(INPUT_NODES, HIDDEN_NODES, OUTPUT_NODES, 0.05);
    n.serialize("test.txt");
    n.deserialize("serializable/784x100x10-0.05x4.txt");
//    trainNetwork(TRAIN_DATA);
//    n.serialize("/Users/bundit/code/neural-net/neural-net/serializable/784x100x10-0.05x5.txt");
//    testNetwork(TEST_DATA);
//
//    cout << endl << "Testing 0.1x5" << endl;
//    n = NeuralNetwork(INPUT_NODES, HIDDEN_NODES, OUTPUT_NODES, 0.1);
//    n.deserialize("/Users/bundit/code/neural-net/neural-net/serializable/784x100x10-0.1x4.txt");
//    trainNetwork(TRAIN_DATA);
//    n.serialize("/Users/bundit/code/neural-net/neural-net/serializable/784x100x10-0.1x5.txt");
//    testNetwork(TEST_DATA);
    
//    cout << endl << "Testing 0.2x4" << endl;
//    n = NeuralNetwork(INPUT_NODES, HIDDEN_NODES, OUTPUT_NODES, 0.2);
//    n.deserialize("/Users/bundit/code/neural-net/neural-net/serializable/784x100x10-0.2x4.txt");
//    testNetwork(TEST_DATA);
//
//    cout << endl << "Testing 0.3x4" << endl;
//    n = NeuralNetwork(INPUT_NODES, HIDDEN_NODES, OUTPUT_NODES, 0.3);
//    n.deserialize("/Users/bundit/code/neural-net/neural-net/serializable/784x100x10-0.3x4.txt");
//    testNetwork(TEST_DATA);

    return 0;
}


// Reads from the file provided by 'data' and trains the neural network n
void trainNetwork(string data) {
    int trainCount = 0; //train counter
    // IO variables
    string line; //to hold each line
    ifstream f (data); //open the file
    
    if (!f.is_open()) {
        cout << "Error while opening file " << data << endl;
    }
    while (getline(f, line) && trainCount < TRAINING_COUNT) { //while has line
        string val; //to hold value read in
        stringstream s (line);
        vector<double> row; //to hold input values 
        
        getline (s, val, ','); //get first value separated by comma and store it in val
        int ans = stoi(val); //cast to
        
        while (getline (s, val, ',')) {
            double input = ((stod(val) / 255.0 * 0.99) + 0.01); //make input from range 0.01-0.99
            row.push_back(input);
        }
        
        n.train(ans, row);
        trainCount++; //increment number of times trained
    }
    f.close();
}

// Reads from the file 'data' and
void testNetwork(string data) {
    int correct = 0; //count of number of tests we've done
    int numTest = 0; //number of tests to do
    
    // IO variables
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
            double input = ((stod(val) / 255.0 * 0.99) + 0.01); //make input from range 0.01-0.99
            row.push_back(input);
            
        }
        
        if ( n.test(ans, row) ) {
             correct++;
        }
        numTest++;
    }
    f.close();
    
    // Print the results
    printResults(correct, numTest);
}

//print the results given the count and total amount of inputs
void printResults(int count, int total) {
	cout << "Total of " << total << " inputs tested." << endl;
	cout << count << " verified correct." << endl;
	cout << (double)count / total * 100 << "% accuracy." << endl;
}
