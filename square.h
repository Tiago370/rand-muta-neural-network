#include "Net.h"
class Square{
public:
    //controles    
    void turnRight();
    void turnLeft();
    void turnUp();
    void turnDown();

    //sensores
	int rightSensor();
    int leftSensor();
    int topSensor();
    int lowSensor();

    int getSize();
    double fitness();
    void printPositions();
    void clear();
    void position(int x, int y);
	Square(int smallerSide, int biggerSide);
	~Square();

private:
	int smallerSide;
	int biggerSide;
    vector <vector <int>> positions;
};
void square();
void squareRandom_mutation(int nInputs, int nHiddenLayers, int nHiddenNeurons, int nOutputs,
		int nPopulation, int nGenerations, vector<vector<int>> pair, vector<vector<vector<int>>>);
bool squareCompareByFitness(Net &a, Net &b);