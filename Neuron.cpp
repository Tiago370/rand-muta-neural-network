/*
 * Neuron.cpp
 *
 *  Created on: 12 de fev. de 2021
 *      Author:
 */

#include "Neuron.h"
#include "Util.h"
#include <iostream>
#include <random>

#define MIN_BIAS -1000
#define MAX_BIAS 1000

#define MIN_WEIGHT -1000
#define MAX_WEIGHT 1000

//Construtor
Neuron::Neuron(int nWeights){
	weights.resize(nWeights);
	newWeights(); //preenche com pesos aleatorios
	output = -1;
}

//Destrutor
Neuron::~Neuron(){
}

vector<double>* Neuron::getWeights(){
	return &weights;
}
double Neuron::getBias(){
	return bias;
}
void Neuron::setBias(double pbias){
	bias = pbias;
}
double Neuron::getOutput(){
	return output;
}

double Neuron::activation(vector<double>* inputs){
	if((*inputs).size() != weights.size() || (*inputs).size() == 0){
		cout << "Erro: input recebido tem " << (*inputs).size() << " elementos, mas deveria ter " << weights.size() << endl;
		exit(1);
	}
	double sum = bias;
	for(unsigned int i = 0; i < weights.size();i++){
		sum += weights[i] * (*inputs)[i];
	}
	output = ReLU(sum);
	return output;
}

double Neuron::ReLU(double x){
	if(x > 0) return x;
	return 0;
}

string Neuron::str(){
	std::string str_bias = std::to_string(bias);
	std::string str_output = std::to_string(output);
	string out ="\n\nBias = "+ str_bias +"\nw = " + doubleVectorToString(&weights) +  "\noutput: " + str_output + "\n";
	return out;
}

void Neuron::newWeights(){
	constexpr int MIN_BIAS_CONS = MIN_BIAS;
	constexpr int MAX_BIAS_CONS = MAX_BIAS;
	constexpr int MIN_WEIGHT_CONS = MIN_WEIGHT;
	constexpr int MAX_WEIGHT_CONS = MAX_WEIGHT;

	std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distrBias(MIN_BIAS_CONS, MAX_BIAS_CONS);
    std::uniform_real_distribution<double> distrWeight(MIN_WEIGHT_CONS, MAX_WEIGHT_CONS);
	bias =  distrBias(eng);
	//bias = MIN_BIAS + rand() % (MAX_BIAS - MIN_BIAS + 1);
	for(unsigned int i = 0; i < weights.size(); i++){
		weights[i] = distrWeight(eng);
		//weights[i] = MIN_WEIGHT + rand() % (MAX_WEIGHT - MIN_WEIGHT);
	}
}

void Neuron::mutation(){
	std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(-1, 1);

	//bias += -1+rand()%3;//(-1,1)
	bias += distr(eng);
	for(unsigned int i = 0; i < weights.size(); i++){
		double & elemRef = weights.at(i);
		//elemRef += (-1+rand()%3);
		elemRef += distr(eng);
	}
}

