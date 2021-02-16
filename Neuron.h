/*
 * Neuron.h
 *
 *  Created on: 12 de fev. de 2021
 *      Author:
 */

#ifndef NEURON_H_
#define NEURON_H_

#include <vector>
#include <string>
#include <stdlib.h>


using namespace std;

class Neuron{
public:
	vector<int> weights;
	int bias;
	int output;

	vector<int>* getWeights();
	int getBias();
	int getOutput();
	int activation(vector<int>* inputs);


	string str();
	void mutation();
	void newWeights();


	Neuron(int nWeights);
	~Neuron();

private:
	int ReLU(int x);
	void summingJunction(vector<int>* inputs);
};

#endif /* NEURON_H_ */
