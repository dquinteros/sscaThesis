#include "matrix_generator.h"

#define M_PI 3.14159265358979323846

//Constructor vacío
MatrixGenerator::MatrixGenerator(void)
{
	this->matrix = vector<vector<double>>();
}

//Constructor con matriz
MatrixGenerator::MatrixGenerator(vector<vector<double>> matrix_)
{
	this->matrix = vector<vector<double>>(matrix_);
}

//Constructor copia
MatrixGenerator::MatrixGenerator(const MatrixGenerator& matrix_generator_)
{
	this->matrix = vector<vector<double>>(matrix_generator_.matrix);
}

//Calculate sigma
double MatrixGenerator::GaussianSigma(int radius)
{
	double radius_ = radius;
	return GaussianSigma(radius_); 
}

//Calculate sigma
double MatrixGenerator::GaussianSigma(double radius)
{
	return (0.3*(radius/2-1))+0.8;
}

//Gaussian
double MatrixGenerator::Gaussian(double x, double sigma)
{
	return exp( -(x*x)/(sigma*sigma*2.0))/(sigma*sqrt(2.0*M_PI));

}

//Matriz gaussiana
void MatrixGenerator::GenerateGaussian(int radius)
{
	double sigma = GaussianSigma(radius);
	GenerateGaussian(radius,sigma,"");
}

//Overload Matriz Gaussiana + Sigma
void MatrixGenerator::GenerateGaussian(int radius, double sigma)
{
	GenerateGaussian(radius,sigma,"");
}

//Overload Matriz Gaussiana + Print Mode
void MatrixGenerator::GenerateGaussian(int radius, string filename)
{
	double sigma = GaussianSigma(radius);	
	GenerateGaussian(radius,sigma,filename);
}

//Overload Matriz Gausiana + Sigma + Print Mode
void MatrixGenerator::GenerateGaussian(int radius, double sigma, string filename)
{
	int size =  2 * radius+1;	
	double w_sum = 0.0;
	vector<double> line = vector<double>();
	for (double y = 0.0; y < size; y++)
	{
		for (double x = 0.0; x < size; x++)
		{
			double w = Gaussian(x-radius,sigma) * Gaussian(y-radius,sigma);			
			w_sum += w;
			line.push_back(w);			
		}
		this->matrix.push_back(line);
		line.clear();
	}
	for (double y = 0.0; y < size; y++)
	{
		for (double x = 0.0; x < size; x++)
		{
			this->matrix[x][y] /= 1;//w_sum;		
		}
	}
	if(filename.size()>0)
	{
		WriteMatrix(filename);
	}	
}
//Student
double MatrixGenerator::Student2d(double x, double y, double freedom)
{
	return pow(1.0+((x*x+y*y)/freedom),-(freedom+2.0)/2.0)/(2.0 * M_PI);
}

//Generate Student
void MatrixGenerator::GenerateStudent(int radius, double freedom)
{
	GenerateStudent(radius,freedom,"");
}

//Generate Student + Print Mode
void MatrixGenerator::GenerateStudent(int radius, double freedom, string filename)
{
	int size = 2*radius+1;
	vector<double> line = vector<double>();
	for (double y = 0.0; y < size; y++)
	{
		for (double x = 0.0; x < size; x++)
		{
			double w = Student2d(x-radius, y-radius, freedom);
			line.push_back(w);
		}
		this->matrix.push_back(line);
		line.clear();
	}	
	
	if(filename.size()>0)
	{
		WriteMatrix(filename);
	}
}

//Generate 1D Exponential PDF
double MatrixGenerator::Exponential(int x, double lambda)
{
	return lambda * exp(-abs(x) * lambda);
}

//Generate Exponential
void MatrixGenerator::GenerateExponential(int radius, double lambda)
{
	GenerateExponential(radius, lambda,""); 
}

//Generate Exponential + Print Mode
void MatrixGenerator::GenerateExponential(int radius, double lambda, string filename)
{
	int size = 2 * radius + 1;
	vector<double> line  = vector<double>();
	this->matrix.clear();
	for (double y = 0.0; y < size; y++)
	{
		for (double x = 0.0; x < size; x++)
		{
			double w;
			double x1 = x-radius;
			double y1 = y-radius;
			w = Exponential(y1, lambda) * Exponential(x1, lambda);
			line.push_back(w);
		}
		this->matrix.push_back(line);
		line.clear();
	}

	if(filename.size()>0)
	{
		WriteMatrix(filename);
	}
}

//Escribir matrix
void MatrixGenerator::WriteMatrix(string filename)
{   
	ofstream file(filename);
	if(file)
	{		
		file << "# name: MAT\n# type: matrix\n# rows: " << matrix.size() << "\n# columns: " << matrix[0].size() << "\n";
		vector<vector<double>> matrix_(matrix);
		for(vector<double> matrix_line : matrix_) {
			for(double point : matrix_line) {
				file << point << " ";
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