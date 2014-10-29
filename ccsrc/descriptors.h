#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class Descriptors
{
private:
	HOGDescriptor hog;
	Mat decriptors;
	Mat labels;
public:
	//Constructores
	Descriptors(void);
	Descriptors(HOGDescriptor);
	Descriptors(const Descriptors&);
	//Getters
	HOGDescriptor get_hog(void){return this->hog;}
	Mat get_decriptors(void){return this->decriptors;}
	Mat get_labels(void){return this->labels;}
	//Compute HOG escriptors
	Mat ComputeHOG(string,string);
	
};

#endif // DESCRIPTORS_H
