#ifndef SIGMOID_H
#define SIGMOID_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <math.h>

class Sigmoid {
private:
	double A;
	double B;
public:
	Sigmoid(void);
	//Getters
	double get_a(void){return this->A}
	double get_b(void){return this->B}
	void SigmoidTrain(vector<float>,vector<bool>,int,int);
};


#endif // SIGMOID_H
