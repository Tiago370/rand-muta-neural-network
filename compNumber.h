#include "Net.h"
//#include "Neuron.h"
#include "Util.h"
void compNumber();
bool compNumbercompareByFitness(Net &a, Net &b);
void compNumberrandom_mutation(int nInputs, int nHiddenLayers, int nHiddenNeurons, int nOutputs,
		int nPopulation, int nGenerations,
		vector<vector<double>> inputs_training, vector<vector<double>> outputs_training);