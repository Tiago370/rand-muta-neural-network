/*
 * Neuron.h
 *
 *  Created on: 12 de fev. de 2021
 *      Author:
 */
<<<<<<< HEAD
//main
=======
//v3
>>>>>>> v3
#ifndef NEURON_H_
#define NEURON_H_

#include <vector>
#include <string>
#include <stdlib.h>

//branch main
using namespace std;

class Neuron{
public:
	vector<double> weights;
	double bias;
	double output;

	vector<double>* getWeights();
	double getBias();
	double getOutput();
	double activation(vector<double>* inputs);


	string str();
	void mutation();
	void newWeights();


	Neuron(int nWeights);
	~Neuron();

private:
	double ReLU(double x);
	void summingJunction(vector<double>* inputs);
};

#endif /* NEURON_H_ */
