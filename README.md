# Convolution Neural Network Implementation in Vanilla C++

This is a repository for a neural network implementation built from the ground up with pure C++ and no external libraries. 
___
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
$ git clone https://github.com/bunditHongmanee/Neural-Network-Digit-Recognition-.git
```
Navigate to the project directory
```
$ cd Neural-Network-Digit-Recognition
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

## Reflection
...to be done...
