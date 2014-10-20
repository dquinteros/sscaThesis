//Genenrador de Matrices en archivo de texto
#ifndef MATRIX_GENERATOR_H
#define MATRIX_GENERATOR_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class MatrixGenerator
{
private:
	vector<vector<double>> matrix;
public:
	//Constructores
	MatrixGenerator(void);
	MatrixGenerator(vector<vector<double>>);
	MatrixGenerator(const MatrixGenerator&);
	//Getter
	vector<vector<double>> get_matrix(void){return this->matrix;}
	//Generadores Gaussianos
	double GaussianSigma(int);
	double GaussianSigma(double);
	double Gaussian(double, double);
	void GenerateGaussian(int);
	void GenerateGaussian(int, double);
	void GenerateGaussian(int, string);
	void GenerateGaussian(int, double, string);
	//Generador Tstudent
	double Student2d(double, double, double);
	void GenerateStudent(int, double);
	void GenerateStudent(int, double, string);
	//Generate Exponential
	double Exponential(int, double);
	void GenerateExponential(int, double);
	void GenerateExponential(int, double, string);
	//Escritura
	void WriteMatrix(string);

};

#endif // MATRIX_GENERATOR_H
