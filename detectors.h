#ifndef DETECTORS_H
#define DETECTORS_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include "annotation.h"
#include "neighbourhood_matrix.h"

class Detectors {
private:
	HOGDescriptor hog;
public:
	//Constructor
	Detectors(void);
	Detectors(HOGDescriptor);
	Detectors(const Detectors&);
	//Deteccion con hog
	Mat HogDetectShow(string, string);
	Mat HogDetectShow(string, string, HOGDescriptor);
	Mat HogDetectShow(string, string, vector<float>);
	NeighbourhoodMatrix HogDetectPrint(string, string);
	NeighbourhoodMatrix HogDetectPrint(string, string, HOGDescriptor);
	NeighbourhoodMatrix HogDetectPrint(string, string, vector<float>);
	void HogDetectBucleShow(string, string);
	void HogDetectBuclePrint(string, string);

};

#endif // DETECTORS_H
