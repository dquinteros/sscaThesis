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

#include <boost/lexical_cast.hpp>

#include "annotation.h"
#include "neighbourhood_matrix.h"
#include "sigmoid.h"

using namespace cv;

class Detectors{
private:
	CvSVM SVM;
	CvBoost boost;
	HOGDescriptor hog;
public:
	//Constructor
	Detectors(void);
	Detectors(HOGDescriptor);
	Detectors(const Detectors&);
	//Loaders
	void LoadSVM(string);
	void LoadAdaboost(string);
	//Deteccion con HOG+SVM unitaria
	Mat HOGSVMDetectShow(string);
	Mat HOGSVMDetectShow(string, string);
	NeighbourhoodMatrix HOGSVMDetectPrint(string, Sigmoid);
	NeighbourhoodMatrix HOGSVMDetectPrint(string, string, Sigmoid);
	//Deteccion con HOG+SVM bucle
	void HOGSVMDetectBucleShow(string);
	void HOGSVMDetectBuclePrint(string,string, Sigmoid);
	//Deteccion con HOG+Adaboost unitaria
	Mat HOGAdaboostDetectShow(string);
	Mat HOGAdaboostDetectShow(string, string);
	NeighbourhoodMatrix HOGAdaboostDetectPrint(string, Sigmoid);
	NeighbourhoodMatrix HOGAdaboostDetectPrint(string, string, Sigmoid);
	//Deteccion con HOG+Adaboost bucle
	void HOGAdaboostDetectBucleShow(string);
	void HOGAdaboostDetectBuclePrint(string,string, Sigmoid);
};

#endif // DETECTORS_H
