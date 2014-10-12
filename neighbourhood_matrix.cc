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
void NeighbourhoodMatrix::ReadNeighbourhoodMatrix(string filename) {
	
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
void NeighbourhoodMatrix::WriteNeigbourhoodMatrix(string filename)
{   
	ofstream file(filename);
	if(height >= 0 && width >= 0 && file)
	{
		
		vector<vector<double>> neighbourhood_matrix_(neighbourhood_matrix);
		for(vector<double> matrix_line : neighbourhood_matrix_) 
		{
			for(double point_probability : matrix_line) 
			{
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

//Media de X
double NeighbourhoodMatrix::XMean(void)
{	
	return (width-1)/2;
}
//Media de Y
double NeighbourhoodMatrix::YMean(void)
{
	return (height-1)/2	;
}
//Media de Z
double NeighbourhoodMatrix::ZMean(void)
{
	double acumulador_mean_z = 0.0;
	for(vector<double> matrix_line : neighbourhood_matrix) 
	{
		for(double point_probability : matrix_line) 
		{
			acumulador_mean_z += point_probability;
		}
	}
	return acumulador_mean_z/(height*width);
}
//Coeficiente A
double NeighbourhoodMatrix::CoefficientA(void)
{
	return ZMean() - CoefficientB() * XMean() - CoefficientC() * YMean();
}
//Coeficiente B
double NeighbourhoodMatrix::CoefficientB(void)
{
	double coefficient_numerator = 0.0;
	double coefficient_denominator = 0.0;
	double z_mean = ZMean();
	double x_mean = XMean();
	for (double x = 0.0; x < width; x++)
	{
		for (double y = 0.0; y < height; y++)
		{
			coefficient_numerator += x * (neighbourhood_matrix[y][x] - z_mean);
			coefficient_denominator += x * (x - x_mean);
		}
	}
	return coefficient_numerator/coefficient_denominator;
}
//Coeficiente C
double NeighbourhoodMatrix::CoefficientC(void)
{
	double coefficient_numerator = 0.0;
	double coefficient_denominator = 0.0;
	double z_mean = ZMean();
	double y_mean = YMean();
	for (int x = 0.0; x < width; x++)
	{
		for (int y = 0.0; y < height; y++)
		{
			coefficient_numerator += y * (neighbourhood_matrix[y][x] - z_mean);
			coefficient_denominator += y * (y - y_mean);
		}
	}
	return coefficient_numerator/coefficient_denominator;
}

//Sumatoria de la Superficie Residual
double NeighbourhoodMatrix::ResidualSurfaceSum(void)
{
	double residual_surface = 0.0;
	for (int x = 0.0; x < width; x++)
	{
		for (int y = 0.0; y < height; y++)
		{
			residual_surface += neighbourhood_matrix[y][x] - CoefficientA() - CoefficientB() * x - CoefficientC() * y;
		}	
	}
	return residual_surface;
}

//Superficie residual
double NeighbourhoodMatrix::ResidualSurface(double x, double y)
{
	return neighbourhood_matrix[y][x] - CoefficientA() - CoefficientB() * x - CoefficientC() * y;
	//return neighbourhood_matrix[y][x];
}


//Calcular RMS Deviation
double NeighbourhoodMatrix::CalculateRMSDeviation(void){
	double nm = height*width;
	double acumulador_sq = 0.0;
	for (int x = 0.0; x < width; x++)
	{
		for (int y = 0.0; y < height; y++)
		{
			acumulador_sq += pow(ResidualSurface(x,y),2.0);
		}	
	}
	return sqrt((1/nm)*acumulador_sq);
}
//Mardias Kurtosis


//Calcular Kurtosis
double NeighbourhoodMatrix::CalculateKurtosis(void)
{
	double mn = height*width;
	double acumulador_sq = 0.0;
	double acumulador_sku = 0.0;
	for (int x = 0.0; x < width; x++)
	{
		for (int y = 0.0; y < height; y++)
		{
			acumulador_sku += pow(ResidualSurface(x,y),4.0);			
		}
	}
	double sq_4 = pow(CalculateRMSDeviation(),4.0);
	double sku = (1/(mn*sq_4))*acumulador_sku;
	return sku;
}

//Calcular Skewness
double NeighbourhoodMatrix::CalculateSkewness(void)
{
	double mn = height*width;
	double acumulador_sq = 0.0;
	double acumulador_ssk = 0.0;
	for (int x = 0.0; x < width; x++)
	{
		for (int y = 0.0; y < height; y++)
		{
			acumulador_ssk += pow(ResidualSurface(x,y),3.0);			
		}
	}
	double sq_3 = pow(CalculateRMSDeviation(),3.0);
	double sku = (1/(mn*sq_3))*acumulador_ssk;
	return sku;
}

//Calcular Kurtosis para la proyección de y
double NeighbourhoodMatrix::CalculateKurtosisY(void)
{
	vector<double> proyeccion_y;
	for (int y = 0.0; y < height; y++)
	{
		double suma_y = 0.0;
		for (int x = 0.0; x < width; x++)
		{	
			suma_y += neighbourhood_matrix[y][x];
		}
		proyeccion_y.push_back(suma_y);
	}
 
    double sum_y_py = 0.0;
    double sum_py = 0.0; 
	for(int i = 0; i < proyeccion_y.size(); i++) {
		sum_y_py += i * proyeccion_y[i];
		sum_py += proyeccion_y[i];
	}

	double centroid_y = sum_y_py/sum_py;

	double y_2 = pow(height - centroid_y,2.0);

	double sd_sum;
	for(double value : proyeccion_y) {
		sd_sum += value*y_2;		 
	}

	double sd_y = sqrt(sd_sum/sum_py);

	double y_4 = pow(height - centroid_y,4.0);

	double sku_sum = 0.0;
	for(double value : proyeccion_y) {
		sku_sum += value*y_4;		 
	}

	return sku_sum/(sum_py * pow(sd_y,4.0));	

}	 

//double CalculateKurtosisX(void);