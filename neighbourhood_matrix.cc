#include "neighbourhood_matrix.h"

//Constructor vacio
NeighbourhoodMatrix::NeighbourhoodMatrix(void)
{
	this->height = 0;
	this->width = 0;		
	this->neighbourhood_matrix = vector<vector<double>>(height, vector<double>(width));
}

//Constructor solo con el vector
NeighbourhoodMatrix::NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_)
{
	this->height = neighbourhood_matrix_.size();
	this->width = neighbourhood_matrix_.front().size();
	this->neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_);
}

//Constructor con vector y tamaño
NeighbourhoodMatrix::NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_,int height_,int width_)
{
	this->height = height_;
	this->width = width_;
	this->neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_);
}
//Constructor copia
NeighbourhoodMatrix::NeighbourhoodMatrix(const NeighbourhoodMatrix& neighbourhood_matrix_)
{
	this->height = neighbourhood_matrix_.height;
	this->width = neighbourhood_matrix_.width;
	this->neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_.neighbourhood_matrix);
}
//Lectura
void NeighbourhoodMatrix::ReadNeighbourhoodMatrix(char* filename) {
	
	ifstream file(filename);

	if(!file)
	{
		fprintf( stderr, "ERROR: the specified file could not be loaded\n");
		
	}else{
		
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
			neighbourhood_matrix.push_back(matrix_line); 
			matrix_line.clear(); 
		}
		file.close();   
		width =  neighbourhood_matrix.front().size();
		height = neighbourhood_matrix.size();
	}
}

//Escritura
void NeighbourhoodMatrix::WriteNeigbourhoodMatrix(char* filename)
{   
	ofstream file(filename);
	if(height >= 0 && width >= 0 && file)
	{
		
		vector<vector<double>> neighbourhood_matrix_(neighbourhood_matrix);
		for(vector<double> matrix_line : neighbourhood_matrix_) {
			for(double point_probability : matrix_line) {
				file << point_probability << " ";
			}
			file << endl;
		}
		file.close();
	}
	else
	{
		fprintf( stderr, "ERROR: the specified file could not be loaded or neighbourhood matrix is empty\n");
	}
}

//Sobrecarga operador asignación
NeighbourhoodMatrix& NeighbourhoodMatrix::operator= (const NeighbourhoodMatrix &neighbourhood_matrix_){
	height = neighbourhood_matrix_.height;
	width = neighbourhood_matrix_.width;
	neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_.neighbourhood_matrix);
	return (*this); 
}

//Calcular Kurtosis
double NeighbourhoodMatrix::CalculateKurtosis(void)
{
	return 0.0;
}

double NeighbourhoodMatrix::CalculateSkewness(void)
{
	return 0.0;
}