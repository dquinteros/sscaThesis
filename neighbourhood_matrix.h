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
	NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix);
	NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix,int height,int width);
	//Getters
	vector<vector<double>> GetNeighbourhoodMatrix(void){return neighbourhood_matrix;}
	int GetHeight(void){return height;}
	int GetWidth(void){return width;}
	//Lectura & Escritura
	void ReadNeighbourhoodMatrix(char* filename) const;
	void WriteNeigbourhoodMatrix(char* filename);
	//Sobrecarga de operador asignacion
	NeighbourhoodMatrix& operator= (const NeighbourhoodMatrix&);
	//Calculo de kurtosis & Skewness
	double CalcularKurtosis(void);
	double CalcularSkewness(void);
};

#endif