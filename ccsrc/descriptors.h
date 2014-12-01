#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
#include <omp.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class Descriptors
{
private:
	HOGDescriptor hog;
	Mat hog_descriptors;
	Mat hog_labels;
public:
	//Constructores
	Descriptors(void);
	Descriptors(HOGDescriptor);
	Descriptors(const Descriptors&);
	//Getters
	HOGDescriptor get_hog(void){return this->hog;}
	Mat get_descriptors(void){return this->hog_descriptors;}
	Mat get_labels(void){return this->hog_labels;}
	//Hog Default Size
	HOGDescriptor DefaultHOGDescriptor(void);
	//Compute HOG escriptors
	Mat ComputeHOG(string,string);
	
};

#endif // DESCRIPTORS_H
