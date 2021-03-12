#include <vector>
#include "Net.h"
#include "square.h"
void square_training();
void play(Net *net, Square *square, int nInputs, int nOutputs, int nSteps);
void squareRandom_mutation(int nInputs, int nHiddenLayers, int nHiddenNeurons, int nOutputs,
		int nPopulation, int nGenerations, vector<vector<int>> squareSizes, int nTrainingSet);
bool squareCompareByFitness(Net &a, Net &b);
void generateTrainingSet(vector<vector<int>>* squareSizes);