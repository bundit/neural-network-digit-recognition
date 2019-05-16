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
int OUTPUT_NODES = 10;      // For digit recognition, 0-9 represents 10 different outputs possible

// Training and testing parameters
// Set these to INT_MAX to train or test the whole set,
// otherwise set to a smaller number to train or test only a specific amount
int TRAINING_COUNT = 60000;
int TESTING_COUNT = 10000;
int MAX_NUM_FILES = 30;

// Testing function declarations
void trainNetwork(std::string data);     //Train the network with the data input
void testNetwork(std::string data);      //Test the network with the data input
void printResults(int count, int total); //Print results after training or testing
void displayProgress(int current, int total); //Displays the progress during a training or testing
std::string* getFilesInDirectory(std::string* files, std::string directory); //Retrieve a list of files you can load from
void initNewNeuralNet();                 //User prompted new neural network initialization
void displayFiles(std::string* fileList);//Display files to user to choose from
void pickFileToLoadFrom(std::string* fileList); //Let the user choose a file

NeuralNetwork n;

int main(int argc, const char * argv[]) {
    using namespace std;
    // Start the program
    cout << endl << "Starting Convolutional Neural Network Program..." << endl;
    
    // User can make a new neural net or load an existing model
    char input;
    do {
        cout << "Enter 'n' to construct a new neural network or 'l' to load an existing model" << endl;
        cin.clear();
        cin >> input;
    } while (input != 'n' && input != 'l');
    
    // File list buffer
    std::string* files = new std::string[MAX_NUM_FILES];
    
    if (input == 'n') { // new net
        initNewNeuralNet();
    }
    else if (input == 'l') { // load net
        files = getFilesInDirectory(files, SERIALIZED_FOLDER);
        displayFiles(files);
        pickFileToLoadFrom(files);
    }
    
    delete[] files; // deallocate files
    
    do { //training or testing
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
// Also prints the list of files to the console
std::string* getFilesInDirectory(std::string* files, std::string directory) {
    using namespace std;
    DIR *dir; //directory
    struct dirent *ent;
    int count = 0;
    if ((dir = opendir (directory.c_str())) != NULL) { //open this directory
        while ((ent = readdir (dir)) != NULL) { //If null, end
            if (ent->d_name[0] != '.' && strncmp(ent->d_name, "README", 6)) { // ignore irrelevant files
                files[count] = ent->d_name;
                count++;
            }
        }
        closedir (dir); //close directory
    } else { //could not open directory
        perror ("EXIT_FAILURE");
        exit(1);
    }
    
    return files;
}

// Print the files to console from the fileList
void displayFiles(std::string* fileList) {
    using namespace std;
    cout << endl;
    
    int i = 0;
    while (fileList[i].length() != 0 && i < MAX_NUM_FILES) {
        if (i < 10)
            cout << " ";
        cout << i << " | " << fileList[i] << endl;
        i++;
    }
}

// Prompt for a file selection and load the file to neural net
void pickFileToLoadFrom(std::string* fileList) {
    using namespace std;
    
    string line; //buffer
    int fileNumber = 0;
    
    do {
        cout << "Choose a model indicated by their number. EX: 3" << endl;
        cin >> line;
        fileNumber = stoi(line);
    } while (!fileNumber);
    cout << "Loading model from file " << fileList[fileNumber] << endl;
    n.deserialize(SERIALIZED_FOLDER + fileList[fileNumber]);
}

// Init new neural net by user input
void initNewNeuralNet() {
    using namespace std;
    double lRate = 0.3; // default learning rate
    int nodes = 0; // number of hidden nodes
    string line; // cin buffer
    
    do {
        cout << "Enter a number of hidden nodes for the neural network greater than 0." << endl;
        cin >> line;
        nodes = stoi(line);
        cout << "Enter a learning rate for the neural network. (A number between 0.01 and 0.3 is recommended)" << endl;
        cin >> line;
        lRate = stod(line);
    } while (nodes == 0 && !lRate);
    
    cout << "Initializing neural network with: " << endl << INPUT_NODES << " input nodes, " << endl;
    cout << nodes << " hidden layer nodes, " << endl;
    cout << OUTPUT_NODES << " output nodes, and " << endl;
    cout << lRate << " learning rate..." << endl;
    
    n = NeuralNetwork(INPUT_NODES, nodes, OUTPUT_NODES, lRate);
}
