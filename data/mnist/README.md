# MNIST Handwritten Digit Database

I have included here the first 100 lines of both the `mnist_train.csv` file and the `mnist_test.csv` file.
You may download the files in their entirety [here](https://pjreddie.com/projects/mnist-in-csv/) if you would like to run the model against the entire dataset. 

## mnist_train.csv

This is the dataset that is used to train the neural network model. The original set is 60,000 lines long.

## mnist_test.csv

This is the dataset that is used to test the neural network model. The original set is 10,000 lines long.

## Format

CSV files are formatted with 'comma-separated values.' One line of this file directly correlates to one input to the neural network. One line will look like this:
```
label, px-11, px12, px13, ...
```
* The label corresponds to the value that the rest of the input represents.
* The remaining px-ij correspond to individual pixel grayscale values of range 0-255 where 0 is white and 255 is black.  

## Additional Info

You can read more about the mnist dataset [here](https://pjreddie.com/projects/mnist-in-csv/).
