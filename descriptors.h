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
public:
	//Constructores
	Descriptors(void);
	Descriptors(HOGDescriptor);
	Descriptors(const Descriptors&);
	//Getters
	HOGDescriptor get_hog(void){return this->hog;}
	//Compute HOG escriptors
	Mat ComputeHOG(string);
	
};

#endif // DESCRIPTORS_H
