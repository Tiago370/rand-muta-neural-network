#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

class Neuron{
public:
	vector<double> weights;
	double bias;
	double output;

	vector<double>* getWeights();
	double getBias();
	void setBias(double pbias);
	double getOutput();
	double activation(vector<double>* inputs);


	string str();
	void mutation();
	void newWeights();


	Neuron(int nWeights);
	~Neuron();

private:
	double ReLU(double x);
	void summingJunction(vector<double>* inputs);
};
