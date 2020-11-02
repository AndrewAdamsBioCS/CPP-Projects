import random
import math
import time
import copy

#####################################################
#####################################################
# Please enter the number of hours you spent on this
# assignment here
num_hours_i_spent_on_this_assignment = 10
#####################################################
#####################################################


def logistic(x):
    return 1.0 / (1.0 + math.exp(-x))

def logistic_derivative(x):
    return logistic(x) * (1-logistic(x))

class Neuron:
    def __init__(self, attribute_weights, neuron_weights, bias_weight):
        # neuron.attribute_weights[i] = Weight of input attribute i as input to this neuron
        self.attribute_weights = attribute_weights
        # neuron.neuron_weights[i] = Weight of neuron j as input to this neuron
        self.neuron_weights = neuron_weights
        self.bias_weight = bias_weight

    def print_neuron(self):
        print(self.attribute_weights)
        print(self.neuron_weights)
        print(self.bias_weight)

class ANN:
    def __init__(self, num_attributes, neurons):
        # Number of input attributes.
        self.num_attributes = num_attributes
        # Number of neurons. neurons[-1] is the output neuron.
        self.neurons = neurons
        for neuron_index, neuron in enumerate(self.neurons):
            for input_neuron, input_weight in neuron.neuron_weights.items():
                assert(input_neuron < neuron_index)

    # Calculates the output of the output neuron for given input attributes.
    # Also calculates intermediate input and output values for neurons, for
    # use in back-propagation
    def calculate(self, attributes):
        num_hidden = len(self.neurons) - 1      # Number of hidden neurons
        bias = -1                               # Defined bias value
        neuron_values = []                      # Output values of neurons
        in_values = []                          # Input values of neurons
        # Calculate input/output values for hidden neurons
        for neuron in range(num_hidden):
            neuron_value = bias * self.neurons[neuron].bias_weight
            for value in range(len(attributes)):
                neuron_value += attributes[value] * self.neurons[neuron].attribute_weights[value]
            in_values.append(neuron_value)
            # Calculate output value using logistic function on input value
            neuron_value = logistic(neuron_value)
            neuron_values.append(neuron_value)
        # Calculate input value to output neuron
        output_neuron_value = bias * self.neurons[len(self.neurons) - 1].bias_weight
        for neuron,value in enumerate(neuron_values):
            output_neuron_value += value * self.neurons[len(self.neurons) - 1].neuron_weights[neuron]
        in_values.append(output_neuron_value)
        # Calculate output of output neuron using logistic function
        output_neuron_value = logistic(output_neuron_value)
        neuron_values.append(output_neuron_value)
        # Return a list of input values and output values for all neurons
        results = [in_values, neuron_values]
        return results


    # Returns the squared error of a collection of examples:
    # Error = 0.5 * sum_i ( example_labels[i] - ann.calculate(example_attributes[i]) )**2
    def squared_error(self, example_attributes, example_labels):
        sum_differences = 0
        # Calculate difference of expected result and actual outcome for each output neuron,
        # and sum the squares of the differences
        for i in range(len(example_labels)):
            # Calculate output
            results = self.calculate(example_attributes[i])
            outputs = results[1]
            # Get value of output neuron
            output_neuron_value = outputs[len(outputs) - 1]
            # Take difference of expected result and actual value
            expected_result = example_labels[i]
            sum_differences += ((expected_result - output_neuron_value) ** 2)
        # Multiply by 0.5 to get error; return error
        error = 0.5 * sum_differences
        return error


    # Runs backpropagation on a single example in order to
    # update the network weights appropriately.
    def backpropagate_example(self, attributes, label, learning_rate=1.0):
        # Calculate input and output values for all neurons in the network
        network_values = self.calculate(attributes)
        # Calculate delta values for all neurons
        delta_values = self.delta(network_values, label)
        # Update neuron weights, beginning with output neuron
        neuron_index = len(self.neurons) - 1
        num_hidden = len(self.neurons) - 1
        for i in range(num_hidden):
            old_weight = self.neurons[neuron_index].neuron_weights[i]
            new_weight = old_weight + (learning_rate * network_values[1][i] * delta_values[neuron_index])
            self.neurons[neuron_index].neuron_weights[i] = new_weight
        # Update output neuron bias weight
        old_bias = self.neurons[neuron_index].bias_weight
        new_bias = old_bias + (learning_rate * -1 * delta_values[neuron_index])
        self.neurons[neuron_index].bias_weight = new_bias
        # Update hidden neuron weights
        neuron_index += -1
        while neuron_index > -1:
            for i in range(len(attributes)):
                old_weight = self.neurons[neuron_index].attribute_weights[i]
                new_weight = old_weight + (learning_rate * attributes[i] * delta_values[neuron_index])
                self.neurons[neuron_index].attribute_weights[i] = new_weight
            # Update bias weight
            old_bias = self.neurons[neuron_index].bias_weight
            new_bias = old_bias + (learning_rate * -1 * delta_values[neuron_index])
            self.neurons[neuron_index].bias_weight = new_bias
            neuron_index += -1


    # Runs backpropagation on each example, repeating this process
    # num_epochs times.
    def learn(self, example_attributes, example_labels, learning_rate=1.0, num_epochs=100):
        epoch_count = 0
        while epoch_count < num_epochs:
            for i in range(len(example_attributes)):
                self.backpropagate_example(example_attributes[i], example_labels[i], learning_rate)
            epoch_count += 1

    # Calculates delta values for all neurons in the network (both output neuron
    # and hidden neurons), for use in backpropagation
    def delta(self, network_values, label):
        input_values = network_values[0]            # Input values of neurons
        output_values = network_values[1]           # Output values of neurons
        delta_values = []                           # Calculated delta values
        delta_index = len(output_values) - 1        # Index of neuron being calculated
        # Calculate delta for output neuron
        # delta = (expected output - actual output) * g'(input)
        output_delta = (label - output_values[delta_index]) * logistic_derivative(input_values[delta_index])
        delta_values.append(output_delta)
        delta_index += -1
        # Calculate delta for hidden neurons
        # delta = g'(input) * weight(hidden->output) * delta of output
        while delta_index > -1:
            neuron_delta = logistic_derivative(input_values[delta_index]) \
                           * self.neurons[len(self.neurons) - 1].neuron_weights[delta_index] * output_delta
            delta_values.insert(0, neuron_delta)
            delta_index += -1
        # Return delta values
        return delta_values


example_attributes = [ [0,0], [0,1], [1,0], [1,1] ]
example_labels = [0,1,1,0]

def random_ann(num_attributes=2, num_hidden=2):
    neurons = []
    # hidden neurons
    for i in range(num_hidden):
        attribute_weights = {attribute_index: random.uniform(-1.0,1.0) for attribute_index in range(num_attributes)}
        bias_weight = random.uniform(-1.0,1.0)
        neurons.append(Neuron(attribute_weights,{},bias_weight))
    # output neuron
    neuron_weights = {input_neuron: random.uniform(-1.0,1.0) for input_neuron in range(num_hidden)}
    bias_weight = random.uniform(-1.0,1.0)
    neurons.append(Neuron({},neuron_weights,bias_weight))
    ann = ANN(num_attributes, neurons)
    return ann

best_ann = None
best_error = float("inf")
for instance_index in range(10):
    ann = random_ann()
    ann.learn(example_attributes, example_labels, learning_rate=10.0, num_epochs=10000)
    error = ann.squared_error(example_attributes, example_labels)
    if error < best_error:
        best_error = error
        best_ann = ann


#####################################################
#####################################################
# Please hard-code your learned ANN here:
learned_ann = random_ann()
learned_ann.neurons[0].attribute_weights[0] = -6.1
learned_ann.neurons[0].attribute_weights[1] = -6.1
learned_ann.neurons[0].bias_weight = -9.1
learned_ann.neurons[1].attribute_weights[0] = -7.6
learned_ann.neurons[1].attribute_weights[1] = -7.6
learned_ann.neurons[1].bias_weight = -3.3
learned_ann.neurons[2].neuron_weights[0] = 12.5
learned_ann.neurons[2].neuron_weights[1] = -12.6
learned_ann.neurons[2].bias_weight = 6.0
# Enter the squared error of this network here:
final_squared_error = 2.5e-05
#####################################################
#####################################################


