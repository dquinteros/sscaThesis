#include "neighbourhood_matrix.h"

//Constructor vacio
NeighbourhoodMatrix::NeighbourhoodMatrix(void)
{
	this->height = 0;
	this->width = 0;		
	this->neighbourhood_matrix = vector<vector<double>>(height, vector<double>(width, 0.0));
}

//Constructor solo con el vector
NeighbourhoodMatrix::NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_)
{
	this->height = neighbourhood_matrix_.size();
	this->width = neighbourhood_matrix_.front().size();
	this->neighbourhood_matrix = neighbourhood_matrix_;
}

//Constructor con vector y tamaño
NeighbourhoodMatrix::NeighbourhoodMatrix(vector<vector<double>> neighbourhood_matrix_,int height_,int width_)
{
	this->height = height_;
	this->width = width_;
	this->neighbourhood_matrix = neighbourhood_matrix_;
}
//Constructor copia
NeighbourhoodMatrix::NeighbourhoodMatrix(const NeighbourhoodMatrix& neighbourhood_matrix_)
{
	this->height = neighbourhood_matrix_.height;
	this->width = neighbourhood_matrix_.width;
	this->neighbourhood_matrix = neighbourhood_matrix_.neighbourhood_matrix;
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
	if(!file)	{
		fprintf( stderr, "ERROR: the specified file could not be loaded\n");
	}else{
		if(this->height >= 0 && this->width >= 0)
		{
			file << "# name: MAT\n# type: matrix\n# rows: " << height << "\n# columns: " << width << "\n";
			vector<vector<double>> neighbourhood_matrix_(this->neighbourhood_matrix);
			for(vector<double> matrix_line : neighbourhood_matrix_) 
			{
				for(double point_probability : matrix_line) 
				{
					file << " " << point_probability ;
				}
				file << endl;
			}
			file.close();
		}
		else
		{
			fprintf( stderr, "ERROR: Empty matrix\n");
		}
	}
}

//Sobrecarga operador asignación
NeighbourhoodMatrix& NeighbourhoodMatrix::operator= (const NeighbourhoodMatrix &neighbourhood_matrix_){
	height = neighbourhood_matrix_.height;
	width = neighbourhood_matrix_.width;
	neighbourhood_matrix = vector<vector<double>>(neighbourhood_matrix_.neighbourhood_matrix);
	return (*this); 
}

/*//Coefficients u, v, w
double NeighbourhoodMatrix::CoefU(void)
{
	double sum_coef = 0.0;
	for (int x = 1; x <= width; x++)
	{
		for (int y = 1; y <= height; y++)
		{
			sum_coef += (x-1)*neighbourhood_matrix[y-1][x-1];
		}	
	}
	return sum_coef;
}
//Coefficients u, v, w
double NeighbourhoodMatrix::CoefV(void)
{
	double sum_coef = 0.0;
	for (int x = 1; x <= width; x++)
	{
		for (int y = 1; y <= height; y++)
		{
			sum_coef += (y-1)*neighbourhood_matrix[y-1][x-1];
		}	
	}
	return sum_coef;
}

//Coefficients u, v, w
double NeighbourhoodMatrix::CoefW(void)
{
	double sum_coef = 0.0;
	for (int x = 1; x <= width; x++)
	{
		for (int y = 1; y <= height; y++)
		{
			sum_coef += neighbourhood_matrix[y-1][x-1];
		}	
	}
	return sum_coef;
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
	double n = width;
	double m = height;
	double up = (7*m*n+m+n-5) * CoefW() - 6*(n+1) * CoefU() - 6*(m+1) * CoefV();
	double down = m*n*(m+1)*(n+1);
	return up/down;
}
//Coeficiente B
double NeighbourhoodMatrix::CoefficientB(void)
{
	double n = width;
	double m = height;
	double up = CoefU()-((m-1)/2) * CoefW();
	double down = m*n*(m-1)*(n+1);
	return 12.0 * (up/down);
}
//Coeficiente C
double NeighbourhoodMatrix::CoefficientC(void)
{
	double n = width;
	double m = height;
	double up = CoefV()-((m-1)/2) * CoefW();
	double down = m*n*(m+1)*(n-1);
	return 12.0 * (up/down);
}

//Sumatoria de la Superficie Residual
double NeighbourhoodMatrix::ResidualSurfaceSum(void)
{
	double residual_surface = 0.0;
	for (int x = 0.0; x < width; x++)
	{
		for (int y = 0.0; y < height; y++)
		{
			residual_surface += neighbourhood_matrix[y][x] - (CoefficientA() + CoefficientB() * x + CoefficientC() * y);
		}	
	}
	return residual_surface;
}

//Superficie residual
double NeighbourhoodMatrix::ResidualSurface(double x, double y)
{
	return neighbourhood_matrix[y][x] - (CoefficientA() + CoefficientB() * x + CoefficientC() * y);
	//return neighbourhood_matrix[y][x];
}

//Calcular RMS Deviation
double NeighbourhoodMatrix::CalculateRMSDeviation(void){
	double nm = neighbourhood_matrix.size()*neighbourhood_matrix[0].size();
	double acumulador_sq = 0.0;
	for (double x = 0.0; x < width; x++)
	{
		for (double y = 0.0; y < height; y++)
		{
			acumulador_sq += pow(ResidualSurface(x,y),2.0);
		}	
	} 
	return sqrt(acumulador_sq/(nm-1));
}

//Calcular Kurtosis
double NeighbourhoodMatrix::CalculateKurtosis(void)
{
	double mn = height*width;
	double acumulador_sq = 0.0;
	double acumulador_sku = 0.0;
	for (double x = 0.0; x < width; x++)
	{
		for (double y = 0.0; y < height; y++)
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
	for (double x = 0.0; x < width; x++)
	{
		for (double y = 0.0; y < height; y++)
		{
			acumulador_ssk += pow(ResidualSurface(x,y),3.0);			
		}
	}
	double sq_3 = pow(CalculateRMSDeviation(),3.0);
	double sku = (1/(mn*sq_3))*acumulador_ssk;
	return sku;
}

//Proyeccion eje Y
vector<double> NeighbourhoodMatrix::ProjectionY(void)
{
	vector<double> projection_y;
	for (int y = 0; y < height; y++)
	{
		double suma_y = 0.0;
		for (int x = 0; x < width; x++)
		{	
			suma_y += neighbourhood_matrix[y][x];
		}
		projection_y.push_back(suma_y);
	}
	return projection_y;
}

//Proyeccion eje X
vector<double> NeighbourhoodMatrix::ProjectionX(void)
{
	vector<double> projection_x;
	for (int x = 0; x < width; x++)
	{
		double suma_x = 0.0;
		for (int y = 0; y < height; y++)
		{	
			suma_x += neighbourhood_matrix[y][x];
		}
		projection_x.push_back(suma_x);
	}
	return projection_x;
}

//Centroide eje Y
double NeighbourhoodMatrix::CentroidY(void)
{
	vector<double> projection_y = vector<double>(ProjectionY());
	int count = 0;
	double upper_sum;
	double bottom_sum;
	for(double val : projection_y) {
		upper_sum += val * count;
		bottom_sum += val;
		count++;
	}

	return upper_sum/bottom_sum;
}

//Centroide eje Y
double NeighbourhoodMatrix::CentroidX(void)
{
	vector<double> projection_x = ProjectionX();
	int count = 0;
	double upper_sum;
	double bottom_sum;
	for(double val : projection_x) {
		upper_sum += val * count;
		bottom_sum += val;
		count++;
	}

	return upper_sum/bottom_sum;
}

//Desviacion Estandar eje Y
double NeighbourhoodMatrix::StandardDeviationY(void)
{
	double centroid_y = CentroidY();
	vector<double> y2;
	for (int i = 0; i < height; i++)
	{
		y2.push_back(pow(i - centroid_y,2.0));
	}

	vector<double> projection_y = vector<double>(ProjectionY());

	double upper_sum;
	double bottom_sum;
	for (int i = 0; i < height; i++)
	{
		upper_sum += y2[i]*projection_y[i];
		bottom_sum += projection_y[i];
	}
		
	return sqrt(upper_sum/bottom_sum);

}

//Desviacion Estandar eje X
double NeighbourhoodMatrix::StandardDeviationX(void)
{
	double centroid_x = CentroidX();
	vector<double> x2;
	for (int i = 0; i < width; i++)
	{
		x2.push_back(pow(i - centroid_x,2.0));
	}

	vector<double> projection_x = ProjectionX();

	double upper_sum;
	double bottom_sum;
	for (int i = 0; i < width; i++)
	{
		upper_sum += x2[i] * projection_x[i];
		bottom_sum += projection_x[i];
	}
		
	return sqrt(upper_sum/bottom_sum);
}

//Calcular Kurtosis para la proyección del eje y
double NeighbourhoodMatrix::CalculateSkewnessY(void)
{
	double centroid_y = CentroidY();
    
    vector<double> y4;
	for (int i = 0; i < height; i++)
	{
		y4.push_back(pow(i - centroid_y,3.0));
	}

	vector<double> projection_y = vector<double>(ProjectionY());

	double upper_sum = 0.0;
	double bottom_sum = 0.0;
	for (int i = 0; i < height; i++)
	{
		upper_sum += y4[i] * projection_y[i];
		bottom_sum += projection_y[i];
	}

	double sd_y = StandardDeviationY();

	return 	upper_sum/(bottom_sum * pow(sd_y,3.0));
}

//Calcular Kurtosis para la proyección del eje y
double NeighbourhoodMatrix::CalculateSkewnessX(void)
{	
	double centroid_x = CentroidX();
	   
    vector<double> x4;
	for (int i = 0; i < width; i++)
	{
		x4.push_back(pow(i - centroid_x,3.0));
	}

	vector<double> projection_x = ProjectionX();

	double upper_sum;
	double bottom_sum;
	for (int i = 0; i < width; i++)
	{
		upper_sum += x4[i]*projection_x[i];
		bottom_sum += projection_x[i];
	}

	double sd_x = StandardDeviationX();

	return 	upper_sum/(bottom_sum * pow(sd_x,3.0));

}	

//Calcular Kurtosis para la proyección del eje y
double NeighbourhoodMatrix::CalculateKurtosisY(void)
{
	double centroid_y = CentroidY();
    
    vector<double> y4;
	for (int i = 0; i < height; i++)
	{
		y4.push_back(pow(i - centroid_y,4.0));
	}

	vector<double> projection_y = vector<double>(ProjectionY());

	double upper_sum = 0.0;
	double bottom_sum = 0.0;
	for (int i = 0; i < height; i++)
	{
		upper_sum += y4[i] * projection_y[i];
		bottom_sum += projection_y[i];
	}

	double sd_y = StandardDeviationY();

	return 	upper_sum/(bottom_sum * pow(sd_y,4.0));
}	

//Calcular Kurtosis para la proyección del eje x
double NeighbourhoodMatrix::CalculateKurtosisX(void)
{	
	double centroid_x = CentroidX();
	   
    vector<double> x4;
	for (int i = 0; i < width; i++)
	{
		x4.push_back(pow(i - centroid_x,4.0));
	}

	vector<double> projection_x = ProjectionX();

	double upper_sum;
	double bottom_sum;
	for (int i = 0; i < width; i++)
	{
		upper_sum += x4[i]*projection_x[i];
		bottom_sum += projection_x[i];
	}

	double sd_x = StandardDeviationX();

	return 	upper_sum/(bottom_sum * pow(sd_x,4.0));

}

/*
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
*/