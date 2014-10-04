//Leer y Escribir Matrices de tamaño variable
#ifndef __NEIGHBOURHOOD_MATRIX_H__
#define __NEIGHBOURHOOD_MATRIX_H__

#include <iostream.h>
#include <fstream.h>
#include <vector.h>

#include <boost/algorithm/string/split.hpp>

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
	NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix);
	NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix,int height,int width);
	//Lectura & Escritura
	void ReadNeighbourhoodMatrix(char* filename);
	void WriteNeigbourhoodMatrix(char* filename);
	//Sobrecarga de operador asignacion
	NeighbourhoodMatrix& operator= (const NeighbourhoodMatrix&);
	//Calculo de kurtosis & Skewness
	double CalcularKurtosis(void);
	double CalcularSkewness(void);
};

#endif