/*
 * Net.cpp
 *
 *  Created on: 12 de fev. de 2021
 *      Author: hokama
 */
//v2
#include "Net.h"
#include <iostream>
#include <iomanip>

#define DEBUG 0

Net::Net(int nInputs, int nHiddenLayers, int nHiddenNeurons, int nOutput){
	this->nInputs = nInputs;
	this->nHiddenLayers = nHiddenLayers;
	this->nHiddenNeurons = nHiddenNeurons;
	this->nOutput = nOutput;
	fitness = 0;

	layers.resize(nHiddenLayers + 1);

	//Criar a primeira hidden layer
	for(int i = 0; i < nHiddenNeurons; i++){
		layers[0].push_back(nInputs);
		//Nota: isso eh equivalente a layers[0].push_back(Neuron(nInputs));
	}

	//Criar as demais hidden layers
	for(int l = 1; l < nHiddenLayers; l++){
		for(int i = 0; i < nHiddenNeurons; i++){
			layers[l].push_back(nHiddenNeurons);
		}
	}

	//Criar a camada de saida
	for(int i = 0; i < nOutput; i++){
		layers[nHiddenLayers].push_back(nHiddenNeurons);
	}
}

Net::~Net(){
}

void Net::rerandom(){
		//Aleatorizar as hidden layers
		for(int l = 0; l < nHiddenLayers; l++){
			for(int i = 0; i < nHiddenNeurons; i++){
				layers[l][i].newWeights();
			}
		}

		//Aleatorizar a camada de saida
		for(int i = 0; i < nOutput; i++){
			layers[nHiddenLayers][i].newWeights();
		}
}

void Net::activateLayers(vector<int>* inputs, vector<int>* poutputs){
	vector<vector<int>> layer_in_out(2);
	layer_in_out[0].resize(nHiddenNeurons);
	layer_in_out[1].resize(nHiddenNeurons);

	//camada de entrada
	for(int n = 0; n < nHiddenNeurons; n++){
		layer_in_out[0][n] = layers[0][n].activation(inputs);
	}
	if(DEBUG) {for(int n = 0; n < nHiddenNeurons; n++) cout << layer_in_out[0][n] << " "; cout << endl;}

	//demais camadas
	for(int l = 1; l < nHiddenLayers; l++){
		for(int n = 0; n < nHiddenNeurons; n++){
			layer_in_out[l%2][n] = layers[l][n].activation(&(layer_in_out[(l-1)%2]));
		}
		if(DEBUG) {for(int n = 0; n < nHiddenNeurons; n++) cout << layer_in_out[l%2][n] << " "; cout << endl;}
	}
    //camada de saida
	for(int n = 0; n < nOutput; n++){
		(*poutputs)[n] = layers[nHiddenLayers][n].activation(&(layer_in_out[(nHiddenNeurons-1)%2]));
	}
	if(DEBUG) {for(int n = 0; n < nOutput; n++) cout << (*poutputs)[n]<< " "; cout << endl;}
}

void Net::setFitness(int pfitness){fitness = pfitness;}
int Net::getFitness(){return fitness;}

vector<vector<Neuron>>* Net::getLayers(){
    return &layers;
}
int Net::getNInputs(){
    return nInputs;
}
int Net::getNHiddenLayers(){
    return nHiddenLayers;
}
int Net::getNHiddenNeurons(){
    return nHiddenNeurons;
}
int Net::getNOutput(){
    return nOutput;
}

void Net::mutation(){
    for(unsigned int i = 0; i < layers.size(); i++){
        for(unsigned int j = 0; j < layers[i].size(); j++){
            layers[i][j].mutation();
        }
    }
}

void Net::copiar_rede(Net * origem){
	if(nInputs != origem->getNInputs() || nHiddenLayers != origem->getNHiddenLayers() ||
			nHiddenNeurons != origem-> getNHiddenNeurons() || nOutput != origem->getNOutput()){
		cerr << "Falha para copiar rede. Redes incompativeis" << endl;
		exit(-1);
	}

    vector<vector<Neuron>>* layers_origem = origem->getLayers();

	//Copiar a primeira hidden layer
	for(int i = 0; i < nHiddenNeurons; i++){
		layers[0][i] = (*layers_origem)[0][i];
	}
	//Copiar as demais hidden layers
	for(int l = 1; l < nHiddenLayers; l++){
		for(int i = 0; i < nHiddenNeurons; i++){
			layers[l][i] = (*layers_origem)[l][i];
		}
	}
	//Copiar a camada de saida
	for(int i = 0; i < nOutput; i++){
		layers[nHiddenLayers][i] = (*layers_origem)[nHiddenLayers][i];
	}
}

void Net::imprimeCamada(unsigned int camada){
    unsigned int n_neuronios = layers[camada].size();
    unsigned int n_ant = layers[camada][0].getWeights()->size();
    cout << "Camada " << setw(2) << camada << "    Bias  ";
   for(unsigned int neuronio_ant = 0; neuronio_ant < n_ant; neuronio_ant++){
        cout << "w_."<< setw(2) << neuronio_ant << " ";
    }
    cout << endl;
    for(unsigned int neuronio = 0; neuronio < n_neuronios; neuronio++){
        cout << setw(10) << neuronio << ": "<< setw(5) << layers[camada][neuronio].getBias() << "  ";
        for(unsigned int neuronio_ant = 0; neuronio_ant < n_ant; neuronio_ant++){
            cout << setw(5) << layers[camada][neuronio].getWeights()->at(neuronio_ant) << " ";
        }
        cout << endl;
    }
}
void Net::imprimeRede(){
    for(int i = 0; i < nHiddenLayers+1; i++){
        imprimeCamada(i);
    }
}

