#include "neighbourhood_matrix.h"

NeighbourhoodMatrix NeighbourhoodMatrix::NeighbourhoodMatrix(void)
{
	heigth = 0;
	width = 0;		
	neighbourhood_matrix = vector<vector<double>>(heigth, vector<double>(width));
}

NeighbourhoodMatrix NeighbourhoodMatrix::NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_)
{
	heigth = neighbourhood_matrix_.size();
	width = neighbourhood_matrix_.front().size();
	neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_);
}

NeighbourhoodMatrix NeighbourhoodMatrix::NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_,int height_,int width_)
{
	height = height_;
	width = width_;
	neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_);
}

void NeighbourhoodMatrix::ReadNeighbourhoodMatrix(char* filename){
	
	ifstream file(filename);

	if(!file)
	{
		fprintf( stderr, "ERROR: the specified file could not be loaded\n");
		return lines;
	}

	heigth = 0;
	width = 0;		
	neighbourhood_matrix = vector<vector<double>>(heigth, vector<double>(width));
	
	string file_line;	

	while (getline(file, file_line))
	{
		vector<double> matrix_line;
		if (line[0]=='#'|| line[0]=='\0') continue;        
		boost::split(matrix_line,file_line,boost::is_any_of(" "));
		neighbourhood_matrix.push_back(matrix_line);  
	}   
	
}