#include "neighbourhood_matrix.h"

NeighbourhoodMatrix neighbourhood_matrix::NeighbourhoodMatrix(void)
{
	heigth = 1;
	width = 1;		
	neighbourhood_matrix = vector<vector<double>>(heigth, vector<double>(width));
}

NeighbourhoodMatrix neighbourhood_matrix::NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_)
{
	heigth = neighbourhood_matrix_.size();
	width = neighbourhood_matrix_.front().size();
	neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_);
}

NeighbourhoodMatrix NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_,int height_,int width_)
{
	height = height_;
	width = width_;
	neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_);
}

void ReadNeighbourhoodMatrix(ifstream file);