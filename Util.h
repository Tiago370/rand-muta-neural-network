/*
 * Util.h
 *
 *  Created on: 12 de fev. de 2021
 *      Author: hokama
 */


#ifndef UTIL_H_
#define UTIL_H_

#include <vector>
#include <string>

using namespace std;

string vectorToString(vector<int>* v);
string doubleVectorToString(vector<double>* v);

void transferList(vector <int>* origem, vector <int>* destino);

#endif /* UTIL_H_ */
