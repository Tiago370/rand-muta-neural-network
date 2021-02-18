/*
 * Util.cpp
 *
 *  Created on: 12 de fev. de 2021
 *      Author: hokama
 */

#include "Util.h"

string vectorToString(vector<int>* v){
    string out = "[";
    for(unsigned int i = 0; i < v->size(); i++){
        std::string str_vi = std::to_string(v->at(i));
        out += str_vi + ", ";
    }
    return out + "]";
}
string doubleVectorToString(vector<double>* v){
    string out = "[";
    for(unsigned int i = 0; i < v->size(); i++){
        std::string str_vi = std::to_string(v->at(i));
        out += str_vi + ", ";
    }
    return out + "]";
}
void transferList(vector <int>* origem, vector <int>* destino){
    for(unsigned int i = 0; i < origem->size(); i++){
        int a = origem->at(i);
        destino->push_back(a);
    }
}
