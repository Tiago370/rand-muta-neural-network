/*
 * Net.h
 *
 *  Created on: 12 de fev. de 2021
 *      Author:
 */

#ifndef NET_H_
#define NET_H_

#include "Neuron.h"
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

class Net{
public:
	int nInputs;
	int nHiddenLayers;
	int nHiddenNeurons;
	int nOutput;
	double fitness;

	vector<vector<Neuron>> layers;

	Net(int nInputs, int nHiddenLayers, int nHiddenNeurons, int nOutput);

	~Net();

	void setFitness(double pfitness);
	double getFitness();
	int getNInputs();
	int getNHiddenLayers();
	int getNHiddenNeurons();
	int getNOutput();

	void mutation();

	//activerLayers recebe um vetor de entrada, ativa todas as camadas e
	//devolve o resultado no vetor poutputs, que deve ser passado previamente alocado
	void activateLayers(vector<double>* inputs, vector<double>* poutputs);
	void copiar_rede(Net * origem);
	void imprimeRede();
	void rerandom();
	void openNet(string arquivo);
	void saveNet(string arquivo);

private:
	vector<vector<Neuron>>* getLayers();
	void imprimeCamada(unsigned int i);
};

#endif /* NET_H_ */