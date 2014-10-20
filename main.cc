#include <stdio.h>
#include <string.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "annotation.h"
#include "descriptors.h"
#include "matrix_generator.h"
#include "neighbourhood_matrix.h"



using namespace std;
using namespace cv;

int printversion();

int main(int argc, char** argv)
{
	printversion();

	for (int i = 50; i < 301; i=i+50)
	{
		string gfilename("pruebas/gauss"+to_string(i)+".mat");
		string efilename("pruebas/exp"+to_string(i)+".mat");
		MatrixGenerator mg;			
		mg.GenerateGaussian(i,i/10.0, gfilename);
		mg.GenerateExponential(i, i/100.0 , efilename);
	}
	return 0;

	/*
	string filename(argv[1]);

	Descriptors dc;

	vector<float> hog_result(dc.ComputeHOG(filename));

	cout << "Vector =" << endl; 
	
	for (int i = 0; i < hog_result.size(); i++)
	{
		cout << hog_result[i] << " ";
	}
	cout << endl;

	return 0;
	*/
}

/*Imprime la versión de las librerías no standar utilizadas*/
int printversion(){
    std::cout << "Boost Version "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minior version
          << BOOST_VERSION % 100                // patch level
          << std::endl;

          std::cout << "OpenCV Version "<< CV_VERSION << std::endl; 

      }
