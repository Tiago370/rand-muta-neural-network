#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <algorithm>
#include "square.h"
#include "Net.h"



using namespace std;


Square::Square(int smallerSide, int biggerSide){
    this->smallerSide = smallerSide;
	this->biggerSide = biggerSide;
    vector<int> position(2);
    position[0] = 0;
    position[1] = 0;
    positions.push_back(position);
}

//Destrutor
Square::~Square(){
}
void Square::printPositions(){
    for(unsigned int i = 0; i < positions.size(); i++){
        cout << "(" << positions[i][0] << ", " << positions[i][1] << ")" << endl;
    }
}
void Square::turnRight(){
    int last = positions.size() - 1;
    int posX = positions[last][0];
    int posY = positions[last][1];
    vector<int> proximo(2);
    if(posX + smallerSide < biggerSide){
        proximo[0] = posX + 1;
    }else{
        proximo[0] = posX;
    }
    proximo[1] = posY;
    positions.push_back(proximo);
}
void Square::turnLeft(){
    int last = positions.size() - 1;
    int posX = positions[last][0];
    int posY = positions[last][1];
    vector<int> proximo(2);
    if(posX > 0){
        proximo[0] = posX - 1;
    }else{
        proximo[0] = posX;
    }
    proximo[1] = posY;
    positions.push_back(proximo);
}

void Square::turnUp(){
    int last = positions.size() - 1;
    int posX = positions[last][0];
    int posY = positions[last][1];
    vector<int> proximo(2);
    proximo[0] = posX;
    if(posY + smallerSide < biggerSide){
        proximo[1] = posY + 1;
    }else{
        proximo[1] = posY;
    }
    positions.push_back(proximo);
}

void Square::turnDown(){
    int last = positions.size() - 1;
    int posX = positions[last][0];
    int posY = positions[last][1];
    vector<int> proximo(2);
    proximo[0] = posX;
    if(posY > 0){
        proximo[1] = posY - 1;
    }else{
        proximo[1] = posY;
    }
    positions.push_back(proximo);
}
int Square::rightSensor(){
    int last = positions.size() - 1;
    int posX = positions[last][0];
    return biggerSide - (posX+smallerSide);
}
int Square::leftSensor(){
    int last = positions.size() - 1;
    int posX = positions[last][0];
    return posX;
}
int Square::topSensor(){
    int last = positions.size() - 1;
    int posY = positions[last][1];
    return biggerSide - (posY+smallerSide);
}
int Square::lowSensor(){
    int last = positions.size() - 1;
    int posY = positions[last][1];
    return posY;
}
double Square::fitness(){
    int last = positions.size() - 1;
    int posX = positions[last][0];
    int posY = positions[last][1];
    
    int objX = floor((biggerSide - smallerSide)/2);
    int objY = objX;
/*
    int sqX = pow(objX-posX,2);
    int sqY = pow(objY-posY,2);

    double d = sqrt(sqX+sqY);
    return d;
*/
    return abs(objX-posX) + abs(objY-posY);
}
void Square::clear(){
    positions.clear();
    vector<int> position(2);
    position[0] = 0;
    position[1] = 0;
    positions.push_back(position);
}
void Square::position(int x, int y){
    positions.clear();
    vector<int> position(2);
    position[0] = x;
    position[1] = y;
    positions.push_back(position);
}
int Square::getSize(){
    return biggerSide;
}