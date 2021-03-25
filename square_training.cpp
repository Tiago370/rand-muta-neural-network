#include <iostream>
#include <algorithm>
#include <limits.h>
#include "square_training.h"
//#include "square.h"
#include "Net.h"
using namespace std;
void play(Net *net, Square *square, int nInputs, int nOutputs, int nSteps){
	//estruturas auxiliares
    vector<double> inputs(nInputs);
	vector<double> outputs(nOutputs);
    for(int s = 0; s < nSteps; s++){
        inputs[0] = square->leftSensor();
        inputs[1] = square->rightSensor();
        inputs[2] = square->topSensor();
        inputs[3] = square->lowSensor();
		net->activateLayers(&(inputs), &outputs);
        if(outputs[0] > 0){
            square->turnLeft();
        }else if(outputs[1] > 0){
            square->turnRight();
        }else if(outputs[2] > 0){
            square->turnUp();
        }else if(outputs[3] > 0){
            square->turnDown();
        }else{}
    }
//    cout << "fitness net: " << net->getFitness() << endl;
//    cout << "fitness square: " << square->fitness() << endl;
    //double fitness = (double)net->getFitness() + (double)(square->fitness()/square->getSize());
    double fitness = (double)net->getFitness() + (double)square->fitness();
//    cout << fitness << endl; 
    net->setFitness(fitness);
//    cout << "fitness net: " << (double)net->getFitness() << endl;

}

void square_training(){
	srand(666); //Fixar uma seed para permitir a reprodutibulidade

	int nInputs = 4;
	int nHiddenLayers = 4;
	int nHiddenNeurons = 4;
	int nOutputs = 4;

	int nGenerations = 1000;
	int nPopulation = 50;

    //criar o conjuto de pares
    unsigned int nTrainingSet = 24; // 3 * 8
    vector<vector<int>> squareSizes(nTrainingSet);
    generateTrainingSet(&squareSizes);
	squareRandom_mutation(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs, nPopulation, nGenerations, squareSizes, nTrainingSet);
}
void squareRandom_mutation(int nInputs, int nHiddenLayers, int nHiddenNeurons, int nOutputs,
		int nPopulation, int nGenerations, vector<vector<int>> squareSizes, int nTrainingSet){
	Net champion(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs);
    champion.setFitness(__DBL_MAX__);
	vector<Net> populacao;
	for(int i = 0; i < nPopulation; i++){
		populacao.push_back(Net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs));
	}
	int generation_number = 0;
    double fitness = __DBL_MAX__;
    int nElite = nPopulation*0.05;
	//Criterio de parada
	while(generation_number < nGenerations && champion.getFitness() > 0.1){
        //cerr << "aqui começo" << endl;
		//Para cada individuo da populacao
		for(int i = 0; i < nPopulation; i++){
			if(i >= nElite) populacao[i].mutation();
            populacao[i].setFitness(0);
            //Para cada caso de teste
            for(unsigned j = 0; j < squareSizes.size(); j++){
                Square square = Square(squareSizes[j][0], squareSizes[j][1]);
                square.position(squareSizes[j][2], squareSizes[j][3]);
                play(&populacao[i], &square, nInputs, nOutputs, squareSizes[j][1]-squareSizes[j][0]+5);
                //if(j == 0) exit(0);
            }
            if(populacao[i].getFitness() < fitness){
                champion.copiar_rede(&populacao[i]);
                champion.setFitness(populacao[i].getFitness());
                fitness = populacao[i].getFitness();
                cout << "Melhor Fitness: " << fitness << endl;
            }

        } 
		//Tentativa 1: os piores individuos serao refeitos, isso introduz aleatoriedade
		sort(populacao.begin(), populacao.end(), squareCompareByFitness);
        for(int i = 0 ; i < populacao.size(); i++){
            //cout << i << ": "<< populacao[i].getFitness() << endl;
        }
        double rDesc = (double)generation_number/nGenerations;
        if(rDesc < 0.1) rDesc = 0.1;
        if(rDesc > 0.9) rDesc = 0.9;
        cout << "Relite: " << rDesc << endl;
		for(int i = nElite; i < (int)nPopulation*rDesc; i++){
            populacao[i].copiar_rede(&(populacao[i%nElite]));
		}
		for(int i = (int)nPopulation*rDesc; i < nPopulation; i++){
			populacao[i].rerandom();
		}

		//Tentativa 2: a cada 100 geracoes eu coloco o campeao de volta na populacao
		if(generation_number%1 == 0){
			//campeao se reproduz
			//populacao[nPopulation-1].copiar_rede(&champion);
		}

		generation_number++;
        //cerr << "aqui fim" << endl;
	}
    cout << "Fitness do campeão " << champion.getFitness() << endl;
    champion.saveNet("champion.txt");
}

bool squareCompareByFitness(Net &a, Net &b){
    if(a.getFitness() < b.getFitness()){
        return true;
    }
	return false;
}

void generateTrainingSet(vector<vector<int>>* squareSizes){
    //square 1, caso de treino 1
    squareSizes->at(0).push_back(1);
    squareSizes->at(0).push_back(10);
    squareSizes->at(0).push_back(0);
    squareSizes->at(0).push_back(0);
    //square 1, caso de treino 2
    squareSizes->at(1).push_back(1);
    squareSizes->at(1).push_back(10);
    squareSizes->at(1).push_back(5);
    squareSizes->at(1).push_back(0);
    //square 1, caso de treino 3
    squareSizes->at(2).push_back(1);
    squareSizes->at(2).push_back(10);
    squareSizes->at(2).push_back(9);
    squareSizes->at(2).push_back(0);
    //square 1, caso de treino 4
    squareSizes->at(3).push_back(1);
    squareSizes->at(3).push_back(10);
    squareSizes->at(3).push_back(9);
    squareSizes->at(3).push_back(5);
    //square 1, caso de treino 5
    squareSizes->at(4).push_back(1);
    squareSizes->at(4).push_back(10);
    squareSizes->at(4).push_back(9);
    squareSizes->at(4).push_back(9);
    //square 1, caso de treino 6
    squareSizes->at(5).push_back(1);
    squareSizes->at(5).push_back(10);
    squareSizes->at(5).push_back(5);
    squareSizes->at(5).push_back(9);
    //square 1, caso de treino 7
    squareSizes->at(6).push_back(1);
    squareSizes->at(6).push_back(10);
    squareSizes->at(6).push_back(0);
    squareSizes->at(6).push_back(9);
    //square 1, caso de treino 8
    squareSizes->at(7).push_back(1);
    squareSizes->at(7).push_back(10);
    squareSizes->at(7).push_back(0);
    squareSizes->at(7).push_back(5);

    //square 2, caso de treino 1
    squareSizes->at(8).push_back(10);
    squareSizes->at(8).push_back(100);
    squareSizes->at(8).push_back(0);
    squareSizes->at(8).push_back(0);
    //square 2, caso de treino 2
    squareSizes->at(9).push_back(10);
    squareSizes->at(9).push_back(100);
    squareSizes->at(9).push_back(45);
    squareSizes->at(9).push_back(0);
    //square 2, caso de treino 3
    squareSizes->at(10).push_back(10);
    squareSizes->at(10).push_back(100);
    squareSizes->at(10).push_back(90);
    squareSizes->at(10).push_back(90);
    //square 2, caso de treino 4
    squareSizes->at(11).push_back(10);
    squareSizes->at(11).push_back(100);
    squareSizes->at(11).push_back(90);
    squareSizes->at(11).push_back(45);
    //square 2, caso de treino 5
    squareSizes->at(12).push_back(10);
    squareSizes->at(12).push_back(100);
    squareSizes->at(12).push_back(90);
    squareSizes->at(12).push_back(90);
    //square 2, caso de treino 6
    squareSizes->at(13).push_back(10);
    squareSizes->at(13).push_back(100);
    squareSizes->at(13).push_back(45);
    squareSizes->at(13).push_back(90);
    //square 2, caso de treino 7
    squareSizes->at(14).push_back(10);
    squareSizes->at(14).push_back(100);
    squareSizes->at(14).push_back(0);
    squareSizes->at(14).push_back(90);
    //square 2, caso de treino 8
    squareSizes->at(15).push_back(10);
    squareSizes->at(15).push_back(100);
    squareSizes->at(15).push_back(0);
    squareSizes->at(15).push_back(45);

    //square 3, caso de treino 1
    squareSizes->at(16).push_back(200);
    squareSizes->at(16).push_back(1000);
    squareSizes->at(16).push_back(0);
    squareSizes->at(16).push_back(0);

    //square 3, caso de treino 1
    squareSizes->at(17).push_back(200);
    squareSizes->at(17).push_back(1000);
    squareSizes->at(17).push_back(0);
    squareSizes->at(17).push_back(0);
    //square 3, caso de treino 1
    squareSizes->at(18).push_back(200);
    squareSizes->at(18).push_back(1000);
    squareSizes->at(18).push_back(0);
    squareSizes->at(18).push_back(400);
    //square 3, caso de treino 1
    squareSizes->at(19).push_back(200);
    squareSizes->at(19).push_back(1000);
    squareSizes->at(19).push_back(800);
    squareSizes->at(19).push_back(0);
    //square 3, caso de treino 1
    squareSizes->at(20).push_back(200);
    squareSizes->at(20).push_back(1000);
    squareSizes->at(20).push_back(800);
    squareSizes->at(20).push_back(400);
    //square 3, caso de treino 1
    squareSizes->at(21).push_back(200);
    squareSizes->at(21).push_back(1000);
    squareSizes->at(21).push_back(800);
    squareSizes->at(21).push_back(800);
    //square 3, caso de treino 1
    squareSizes->at(22).push_back(200);
    squareSizes->at(22).push_back(1000);
    squareSizes->at(22).push_back(400);
    squareSizes->at(22).push_back(800);
    //square 3, caso de treino 1
    squareSizes->at(23).push_back(200);
    squareSizes->at(23).push_back(1000);
    squareSizes->at(23).push_back(0);
    squareSizes->at(23).push_back(800);
}