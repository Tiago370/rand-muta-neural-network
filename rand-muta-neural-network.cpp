//============================================================================
// Name        : rand-muta-neural-network.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <string>
//#include "Net.h"
//#include "Neuron.h"
//#include "square.h"
#include "square_training.h"
#include "Util.h"
//#include "compNumber.h"

#define DEBUG 0

using namespace std;
void run(int smaller, int bigger, int posX, int posY);
int main() {
	square_training();
	//run(1,100, 50, 50);
	//compNumber();
	return 0;
}
void run(int smaller, int bigger, int posX, int posY){
	Net net = Net(1,1,1,1);
	net.openNet("rand-muta-neural-network/champion_1332.txt");
	int nInputs = net.getNInputs();
	int nOutputs = net.getNOutput();
	Square square = Square(smaller, bigger);
	square.position(posX,posY);
	int nSteps = bigger - smaller + 5;
	//estruturas auxiliares
    vector<double> inputs(nInputs);
	vector<double> outputs(nOutputs);
	cout << "let bigSquare = " << bigger << endl;
	cout << "let smallerSquare = " << smaller << endl;
	cout << "let x = " << posX << endl;
	cout << "let y = " << posY << endl;

	cout << "let positions = [";
    for(int s = 0; s < nSteps; s++){
        inputs[0] = square.leftSensor();
        inputs[1] = square.rightSensor();
        inputs[2] = square.topSensor();
        inputs[3] = square.lowSensor();
		net.activateLayers(&(inputs), &outputs);
        if(outputs[0] > 0){
            square.turnLeft();
			cout << " 'L'";
        }else if(outputs[1] > 0){
            square.turnRight();
			cout << " 'R'";
        }else if(outputs[2] > 0){
            square.turnUp();
			cout << " 'U'";
        }else if(outputs[3] > 0){
            square.turnDown();
			cout << " 'D'";
        }else{
			cout << " 'P'";
		}
		if(s < nSteps - 1){
			cout << ",";
		}
    }
	cout << "]" << endl;
	//square.printPositions();
}