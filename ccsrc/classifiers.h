#ifndef CLASSIFIERS_H
#define CLASSIFIERS_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include "linear_svm.h"

using namespace std;
using namespace cv;

class Classifiers {
private:
	CvSVMParams params;
public:
	//Constructores
	Classifiers(void);
	Classifiers(CvSVMParams);
	Classifiers(const Classifiers&);
	//Train & Save	
	vector<float> HogVectorSVMTrain(Mat, Mat, string);
	vector<float> HogVectorSVMTrain(Mat, Mat, CvSVMParams, string);
	//Load
	vector<float> HogVectorSVMLoad(string);
};


#endif // CLASSIFIERS_H
