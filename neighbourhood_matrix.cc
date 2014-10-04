#include "neighbourhood_matrix.h"

//Constructor vacio
NeighbourhoodMatrix::NeighbourhoodMatrix(void)
{
	heigth = 0;
	width = 0;		
	neighbourhood_matrix = vector<vector<double>>(heigth, vector<double>(width));
}

//Constructor solo con el vector
NeighbourhoodMatrix::NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_)
{
	heigth = neighbourhood_matrix_.size();
	width = neighbourhood_matrix_.front().size();
	neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_);
}

//Constructor con vector y tamaño
NeighbourhoodMatrix::NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_,int height_,int width_)
{
	height = height_;
	width = width_;
	neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_);
}
//Lectura
NeighbourhoodMatrix NeighbourhoodMatrix::ReadNeighbourhoodMatrix(char* filename) const {
	
	NeighbourhoodMatrix read_matrix;
	ifstream file(filename);

	if(!file)
	{
		fprintf( stderr, "ERROR: the specified file could not be loaded\n");
		return read_matrix;
	}

	
	vector<double> matrix_line;
	string file_line;	

	while (getline(file, file_line))
	{		
		if (file_line[0]=='#'|| file_line[0]=='\0') continue;
		istringstream is(file_line);
		double point_probability;
		while(is >> point_probability)
		{
		   matrix_line.push_back(point_probability);
		}
		read_matrix.neighbourhood_matrix.push_back(matrix_line); 
		matrix_line.clear(); 
	}   
	read_matrix.width =  neighbourhood_matrix.front().size();
	read_matrix.heigth = neighbourhood_matrix.size();

	return read_matrix;
}

//Escritura
void WriteNeigbourhoodMatrix(char* filename)
{

}