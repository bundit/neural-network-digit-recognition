![Image of neural network](https://raw.githubusercontent.com/bundit/Neural-Network-Digit-Recognition/master/images/NeuralNet.png)
# Convolution Neural Network Implementation in Vanilla C++

This is a repository for a neural network implementation built from the ground up with pure C++ and no external libraries. 
___ 
## Neural Networks

### What are they and how do they work?
Neural networks are networks that are a simplified model of connections in the human brain. They are designed to recognize patterns and "learn" from them.
<br><br>
On a basic level, we can look at a neural network and simply view them as a black box that takes some input, performs some calculations or "thinking" and produce some output. Given some output and knowing what we expect the output should be, we can calculate errors and have the neural network "learn" from it, so that next time it will be more accurate in its output. We call this iterative learning because we repeatedly train the neural network one step at a time.

### About this Neural Network
This part references the image above. <br>
* The brown lines represent input signals coming into the neural network. In this project we initialize this number to be 784 to represent a 28 by 28 pixel grayscale image. 
* The green circles represent the input layer nodes to the network. The number of nodes needs to be equivalent to the number of input signals, 784.
* The blue circles represent the hidden layer nodes in the network. We use a hidden layer between the input and output layer to allow the network to reduce generalization and process more details. Typically, a more complex problem may require more than one hidden layer.
* The red circles represent our output layer nodes. The number of nodes will depend on what type of output you are expecting from the neural network. In our case we want to recognize digits 0-9 so we use 10 output nodes. 
* The yellow lines represent connections with weights associated with them connecting the input nodes to the hidden nodes. They allow us to calculate the signals going into the hidden layer.
* The pink lines represent connections with weights connecting the hidden nodes to the output nodes. Similar to the input to hidden connections, we use them to calculate the next layer of signals to output. They are calculated in the same fashion. 
* The black line represents the actual output of the neural network. There is one output associated with each output node, so 10 output signals.

### More about neural networks

You can learn more about neural networks [here](https://en.wikipedia.org/wiki/Convolutional_neural_network). 

## Dataset
This project utilized the [MNIST handwritten digit database](http://yann.lecun.com/exdb/mnist/). These are grayscale images of size 28 pixels by 28 pixels with a label of what number they represent.
* The training set contains 60,000 images
* The testing set contains 10,000 images

# Run This Project

## Requirements
To run this on your local machine you will need the following installed:
* CMake (Version 2.8+)
* Make
* C++ Compiler (Version 11+)

### MacOS
On MacOS you will need to install Xcode Command Line Tools which will install both Make and a C++ Compiler (Clang) for you. To do this, open your terminal and type this command:
```
$ xcode-select --install
```
Then you can install CMake using Homebrew. If you don't have Homebrew already, you can install it with this command in your terminal:
```
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
Then you can install CMake with Homebrew using this command in your terminal:
```
$ brew install cmake
```
### Linux Distributions
On Linux systems you will need to install g++ as your C++ compiler. You can do this by entering this command in your terminal:
```
$ sudo apt-get update
```
Followed by:
```
$ sudo apt-get install g++
```
Then install Make which is included in build-essentials:
```
$ sudo apt-get install build-essential
```
And finally install CMake with this:
```
$ sudo apt-get -y install cmake
```
### Windows
For Windows you will need CygWin, get it [http://www.cygwin.com/install.html](here). When installing CygWin make sure you install these packages: `g++`, `gdb`, and `make`.

Lastly, install CMake with the installer from [this page](https://cmake.org/download/).

## Project Installation and Setup
Clone the repository
```
$ git clone https://github.com/bundit/neural-network-digit-recognition.git
```
Navigate to the project directory
```
$ cd neural-network-digit-recognition
```
Run CMake. H targets the source directory "." which is our current directory and B targets where to output the build files. This will create a folder called "_build" and create the build files there
```
$ cmake -H. -B_build
```
Navigate to the "_build" folder
```
$ cd _build
```
Compile the build with Make. This will output an executable file called "neural-net-app"
```
$ make
```
Run the program
```
$ ./neural-net-app
```

# Future Ideas
* Add canvas to draw your own digits to be tested
* Train the neural network on an alphabet dataset to recognize letters 
