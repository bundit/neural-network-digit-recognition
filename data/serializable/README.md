# Serialization
Serialization is converting an object to a format to be stored in a database or file. <br> 
In my case, I have serialized already trained neural network models to text files. 
___
### Why?
This allows me to save models for later use, such as continue training it again or evaluating it against other models.

### What do these files contain?
These files save these values from a neural network: <br>
<br>
`lRate` the learning rate, <br>
`inputToHidden->weights` the weight matrix connecting the input layer to the hidden layer, and <br> 
`hiddenToOutput->weights` the weight matrix connecting the hidden layer to the output layer.  <br>
<br>
These are the only values needed to re-construct a neural network model.

### What do the file names mean?
The file names are representative of the values of the neural network model. <br>
For example, lets take look at this file, `784x100x10-0.2x2.txt`. <br>
<br>
`784`: the number of input nodes <br>
`100`: the number of hidden nodes <br>
`10`: the number of output nodes <br>
`0.2`: the learning rate used to train this model <br>
`2`: the number of epochs trained <br>
<br>
This file contains the model of a `784` input by `100` hidden by `10` output layer trained with a `0.2` learning rate for a number of `2` epochs 
