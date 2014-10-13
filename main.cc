#include <stdio.h>

#include "annotation.h"
#include "matrix_generator.h"
#include "neighbourhood_matrix.h"


using namespace std;

int main(int argc, char** argv)
{

	for (int i = 6; i < 15; i++)
	{
		string filename("gauss"+to_string(i)+".txt");
		MatrixGenerator mg;
		mg.GenerateGaussian(i,1.0, filename);

		NeighbourhoodMatrix nm;
		nm.ReadNeighbourhoodMatrix(filename);
		cout << filename << endl;
		cout << setprecision(3) << fixed << "Superficie: " << nm.ResidualSurfaceSum() << endl;
		cout << setprecision(3) << "Sigma: " << nm.CalculateRMSDeviation() << endl;			
		cout << setprecision(3) <<  "U: " << nm.CoefU() << endl;
		cout << setprecision(3) <<  "V: " << nm.CoefV() << endl;
		cout << setprecision(3) <<  "W: " << nm.CoefW() << endl;	
		cout << setprecision(3) <<  "A: " << nm.CoefficientA() << endl;
		cout << setprecision(3) <<  "B: " << nm.CoefficientB() << endl;
		cout << setprecision(3) <<  "C: " << nm.CoefficientC() << endl;
		cout << setprecision(3) <<  "Skewness: " << nm.CalculateSkewnessY() << endl;
		cout << setprecision(3) << "CurtosisY: " << nm.CalculateKurtosisY() << endl;
		cout << setprecision(3) << "Curtosis: " << nm.CalculateKurtosis() << endl;
	} 
	return 0;
}
