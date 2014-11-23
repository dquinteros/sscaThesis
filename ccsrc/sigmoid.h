#ifndef SIGMOID_H
#define SIGMOID_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class Sigmoid {
private:
	double A;
	double B;
	int width;
	int height;
public:
	//Constructors
	Sigmoid(void);
	Sigmoid(int,int);
	Sigmoid(const Sigmoid&);
	//Getters
	double get_a(void){return this->A;}
	double get_b(void){return this->B;}
	int get_width(void){return this->width;}
	int get_height(void){return this->height;}
	//Training & Evaluate
	void SigmoidTrain(vector<float>,vector<bool>,int,int);
	float EvaluateSigmoid(float f);
};

#endif // SIGMOID_H
