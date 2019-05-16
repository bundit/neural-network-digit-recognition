//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//                             //
// Vanilla C++ Neural Network  //
//  Author: Bundit Hongmanee   //
//                             //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//

// Project headers
#include "../include/MatrixManipulation.h"
#include "../include/NetLayer.h"
#include "../include/NeuralNetwork.h"
// Std includes
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <dirent.h>

// MNIST data files
std::string TRAIN_DATA = "../data/mnist/mnist_train.csv"; //Training data set
std::string TEST_DATA = "../data/mnist/mnist_test.csv";   //Testing data set

// Path to serialized folder
std::string SERIALIZED_FOLDER = "../data/serializable/";

// Neural Network parameters
int INPUT_NODES = 28 * 28;  // For grayscale images of length 28 and width 28 pixels
//int HIDDEN_NODES = 100;     // Arbitrary number, usually a number between OUTPUT_NODES and INPUT_NODES is recommended
int OUTPUT_NODES = 10;      // For digit recognition, 0-9 represents 10 different outputs possible
//double LEARNING_RATE = .2;  // Ratio used to prevent 'overstepping' in our weight adjustments

// Training and testing parameters
// Set these to INT_MAX to train or test the whole set,
// otherwise set to a smaller number to train or test only a specific amount
int TRAINING_COUNT = 60000;
int TESTING_COUNT = 10000;

// Testing function declarations
void trainNetwork(std::string data);
void testNetwork(std::string data);
void printResults(int count, int total);
void displayProgress(int current, int total);
std::string* getFilesInDirectory(std::string directory);
void initNewNeuralNet();

NeuralNetwork n;

int main(int argc, const char * argv[]) {
    using namespace std;
    
    cout << endl << "Starting Convolutional Neural Network Program..." << endl;
    char input;
    
    do {
        cout << "Enter 'n' to construct a new neural network or 'l' to load an existing model" << endl;
        cin.clear();
        cin >> input;
        
    } while (input != 'n' && input != 'l');
    
    string* files;//[20];
    string line;
    if (input == 'n') {
        initNewNeuralNet();
    } else if (input == 'l') {
        
        files = getFilesInDirectory(SERIALIZED_FOLDER);
        
        int fileNumber = 0;
        
        do {
            cout << "Choose a model indicated by their number. EX: 3" << endl;
            cin >> line;
            fileNumber = stoi(line);
        } while (!fileNumber);
        cout << "Loading model from file " << files[fileNumber] << endl;
        n.deserialize(SERIALIZED_FOLDER + files[fileNumber]);
        
        delete files; // de allocate mem
    }
    
    do {
        cout << "Enter 'f' to train the network or 't' to test the network or 'q' to quit" << endl;
        cin >> input;
        if (input == 'f') {
            trainNetwork(TRAIN_DATA);
        } else if (input == 't') {
            testNetwork(TEST_DATA);
        }
        
    } while (input != 'q');
    

    return 0;
}


// Reads from the file provided by 'data' and trains the neural network n
void trainNetwork(std::string data) {
    using namespace std;
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
        displayProgress(trainCount, TRAINING_COUNT);
        trainCount++; //increment number of times trained
    }
    f.close();
}

// Reads from the file 'data' and
void testNetwork(std::string data) {
    using namespace std;
    int correct = 0; //count of number of tests we've done
    int testCount = 0; //number of tests to do
    
    // IO variables
    string line; //string to hold one line
    ifstream f (data); //open the file
    
    if (!f.is_open()) {
        cout << "Error while opening file " << data << endl;
    }
    
    while (getline(f, line) && testCount < TESTING_COUNT) { //read a line
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
        displayProgress(testCount, TESTING_COUNT);
        testCount++;
    }
    f.close();
    
    // Print the results
    printResults(correct, testCount);
}

// Print the results given the count and total amount of inputs
void printResults(int count, int total) {
    using namespace std;
	cout << "Total of " << total << " inputs tested." << endl;
	cout << count << " verified correct." << endl;
	cout << (double)count / total * 100 << "% accuracy." << endl;
}

// Display the progress of a training set or a testing set
void displayProgress(int current, int total) {
    int percent = (double) current / total * 100.0;
    std::cout << current << " of " << total << " completed | " << percent << "%\r";
    std::cout.flush();
}

// Get the files in a directory and return the files in an array of strings
std::string* getFilesInDirectory(std::string directory) {
    using namespace std;
    std::string* files = new std::string[20];
    DIR *dir; //directory
    struct dirent *ent;
    int count = 0;
    if ((dir = opendir (directory.c_str())) != NULL) { //open this directory
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                if (count < 10) cout << " ";
                cout << count << " | " << ent->d_name << endl;
                files[count] = ent->d_name;
                count++;
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("EXIT_FAILURE");
        exit(1);
    }
    
    return files;
}

// Init new neural net by user input
void initNewNeuralNet() {
    using namespace std;
    double lRate = 0.3; // default learning rate
    int nodes = 0; // number of hidden nodes
    string line; // cin buffer
    
    do {
        cout << "Enter a number of hidden nodes for the neural network." << endl;
        cin >> line;
        nodes = stoi(line);
        cout << "Enter a learning rate for the neural network. (A number between 0.01 and 0.3 is recommended)" << endl;
        cin >> line;
        lRate = stod(line);
    } while (!nodes && !lRate);
    
    cout << "Initializing neural network with: " << endl << INPUT_NODES << " input nodes, " << endl;
    cout << nodes << " hidden layer nodes, " << endl;
    cout << OUTPUT_NODES << " output nodes, and " << endl;
    cout << lRate << " learning rate..." << endl;
    
    n = NeuralNetwork(INPUT_NODES, nodes, OUTPUT_NODES, lRate);
}
