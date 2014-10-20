//Leer y Escribir Matrices de tamaño variable
#ifndef __NEIGHBOURHOOD_MATRIX_H__
#define __NEIGHBOURHOOD_MATRIX_H__

#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class NeighbourhoodMatrix
{
private:
	vector<vector<double>> neighbourhood_matrix;
	int height;
	int width;
public:
	//Constructores
	NeighbourhoodMatrix(void);
	NeighbourhoodMatrix(vector<vector<double>>);
	NeighbourhoodMatrix(vector<vector<double>>,int,int);
	NeighbourhoodMatrix(const NeighbourhoodMatrix&);
	//Getters
	vector<vector<double>> get_neighbourhood_matrix(void){return this->neighbourhood_matrix;}
	int get_height(void){return this->height;}
	int get_width(void){return this->width;}
	//Lectura & Escritura
	void ReadNeighbourhoodMatrix(string);
	void WriteNeigbourhoodMatrix(string);
	//Sobrecarga de operador asignacion
	NeighbourhoodMatrix& operator= (const NeighbourhoodMatrix&);
/*	//Calculo de la superficie residual
	double CoefU(void);
	double CoefV(void);
	double CoefW(void);
	double XMean(void);
	double YMean(void);
	double ZMean(void);
	double CoefficientA(void);
	double CoefficientB(void);
	double CoefficientC(void);
	double ResidualSurfaceSum(void);
	double ResidualSurface(double,double);
	//Calculo de RMS Deviation, Kurtosis & Skewness
	double CalculateRMSDeviation(void);
	double CalculateKurtosis(void);
	double CalculateSkewness(void);	
	//Proyecciones por eje;
	vector<double> ProjectionY(void);
	vector<double> ProjectionX(void);
	//Centroide por eje
	double CentroidY(void);
	double CentroidX(void);
	//Desviacion standar por eje
	double StandardDeviationY(void);
	double StandardDeviationX(void);
	//Skewness por eje
	double CalculateSkewnessY(void);
	double CalculateSkewnessX(void);
	//Kurtosis por eje
	double CalculateKurtosisY(void);
	double CalculateKurtosisX(void);*/
};

#endif