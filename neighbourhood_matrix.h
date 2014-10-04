//Leer y Escribir Matrices de tamaño variable
#ifndef __NEIGHBOURHOOD_MATRIX_H__
#define __NEIGHBOURHOOD_MATRIX_H__

#include <fstream>
#include <iostream>
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
	//Constructor
	NeighbourhoodMatrix(void);
	NeighbourhoodMatrix(vector<vector<double>>);
	NeighbourhoodMatrix(vector<vector<double>>,int,int);
	NeighbourhoodMatrix(const NeighbourhoodMatrix&);
	//Getters
	vector<vector<double>> GetNeighbourhoodMatrix(void){return this->neighbourhood_matrix;}
	int GetHeight(void){return this->height;}
	int GetWidth(void){return this->width;}
	//Lectura & Escritura
	NeighbourhoodMatrix ReadNeighbourhoodMatrix(char*) const;
	void WriteNeigbourhoodMatrix(char*);
	//Sobrecarga de operador asignacion
	NeighbourhoodMatrix& operator= (const NeighbourhoodMatrix&);
	//Calculo de kurtosis & Skewness
	double CalculateKurtosis(void);
	double CalculateSkewness(void);
};

#endif