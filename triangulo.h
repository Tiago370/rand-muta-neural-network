#include "Net.h"
#include "Neuron.h"
#include "Util.h"
void triangulo();
bool trianguloCompareByFitness(Net &a, Net &b);
void trianguloRandom_mutation(int nInputs, int nHiddenLayers, int nHiddenNeurons, int nOutputs,
		int nPopulation, int nGenerations,
		vector<vector<double>> inputs_training, vector<vector<double>> outputs_training);