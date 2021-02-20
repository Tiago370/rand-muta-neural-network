#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "Net.h"
#include "Neuron.h"
#include "Util.h"
#include "triangulo.h"

void triangulo(){

	srand(666); //Fixar uma seed para permitir a reprodutibulidade

	int nInputs = 3;
	int nHiddenLayers = 1;
	int nHiddenNeurons = 1;
	int nOutputs = 1;

	int nGenerations = 3000;
	int nPopulation = 500;


	//estruturas auxiliares
	//Criando o conjunto de treinamento, vou gerar 500 valores aleatorios
	int nTrainingSet = 500;
	vector<vector<double>> inputs_training(nTrainingSet);
	vector<vector<double>> outputs_training(nTrainingSet);

	for(int i = 0; i < nTrainingSet; i++){
		double value1 = rand()%1001;
		double value2 = rand()%1001;
        double value3 = rand()%1001;

		outputs_training[i].push_back(1);
	}
	//if(DEBUG) for(int i = 0; i < nTrainingSet; i++) cout << doubleVectorToString(&(inputs_training[i])) << " out: " << doubleVectorToString(&(outputs_training[i])) << endl;


	trianguloRandom_mutation(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs, nPopulation, nGenerations, inputs_training, outputs_training);

}

void trianguloRandom_mutation(int nInputs, int nHiddenLayers, int nHiddenNeurons, int nOutputs,
		int nPopulation, int nGenerations,
		vector<vector<double>> inputs_training, vector<vector<double>> outputs_training){

	Net champion(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs);
	vector<Net> populacao;
	for(int i = 0; i < nPopulation; i++){
		populacao.push_back(Net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs));
	}

	//estruturas auxiliares
	vector<double> inputs(nInputs);
	vector<double> outputs(nOutputs);

	int best_fitness = 0;
	int geneneration_number = 0;

	//Criterio de parada
	while(geneneration_number < nGenerations && best_fitness < (int) inputs_training.size()){
		//Para cada individuo da populacao
		for(int i = 0; i < nPopulation; i++){
			int fitness = 0;
			populacao[i].mutation();
			for(unsigned int in = 0; in < inputs_training.size(); in++){
				populacao[i].activateLayers(&(inputs_training[in]), &outputs);
				if((outputs[0] > 0) == outputs_training[in][0]) fitness++;
			}
			populacao[i].setFitness(fitness);
			if(fitness > best_fitness) {
				best_fitness = fitness;
				champion.copiar_rede(&(populacao[i]));
				cout << "Fitness atual " << best_fitness << endl;
			}
		}

		//Tentativa 1: os piores individuos serao refeitos, isso introduz aleatoriedade
		sort(populacao.begin(), populacao.end(), trianguloCompareByFitness);
		for(int i = nPopulation*0.9; i < nPopulation; i++){
			populacao[i].rerandom();
		}

		//Tentativa 2: a cada 100 geracoes eu coloco o campeao de volta na populacao
		if(geneneration_number%100 == 0){
			//campeao se reproduz
			populacao[nPopulation-1].copiar_rede(&champion);
		}

		geneneration_number++;
	}

	cout << "Numero de geracoes: " << geneneration_number << endl;
	cout<< "Rede Vencedora" << endl;
	champion.imprimeRede();
	int acertos = 0;
	for(int i = 0; i < 1000; i++){
    	inputs[0] = rand()%5;
        inputs[1] = rand()%5;
        //cout << "Entradas: " << inputs[0] << ", " << inputs[1] << " Saida: ";
    	champion.activateLayers(&inputs, &outputs);
	    if(outputs[0]>0){
			acertos++;
		}
	}
	double assertividade = (acertos/10);
	cout << "acertos: " << acertos << endl;
	cout << "Assertividade: " << assertividade << "%" << endl;
}
bool trianguloCompareByFitness(Net &a, Net &b){

	return a.getFitness() > b.getFitness();

}