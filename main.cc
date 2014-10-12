#include <stdio.h>

#include "annotation.h"
#include "matrix_generator.h"
#include "neighbourhood_matrix.h"


using namespace std;

int main(int argc, char** argv)
{

	for (int i = 1; i < 6; i++)
	{
		string filename("gauss"+to_string(i)+".txt");
		MatrixGenerator mg;
		mg.GenerateGaussian(i,1.0, filename);
		cout << "Sigma: " << mg.GaussianSigma(i) << endl;

		NeighbourhoodMatrix nm;
		nm.ReadNeighbourhoodMatrix(filename);
		cout << setprecision(5) << fixed << "Suma superficie residual: " << nm.ResidualSurfaceSum() << endl;
		cout << setprecision(5) << "Curtosis: " << nm.CalculateKurtosisY() << endl;
	}


		NeighbourhoodMatrix nm;
		nm.ReadNeighbourhoodMatrix("gauss.out");
		cout << setprecision(5) << fixed << "Suma superficie residual: " << nm.ResidualSurfaceSum() << endl;
		cout << setprecision(5) << "Curtosis: " << nm.CalculateKurtosisY() << endl;

	return 0;
}
