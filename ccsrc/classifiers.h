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
	CvSVMParams svm_params;
public:
	//Constructores
	Classifiers(void);
	Classifiers(CvSVMParams);
	Classifiers(const Classifiers&);
	//SVM default Params
	CvSVMParams LinearSVMDefaultParams(void);
	//Train & Save	
	void SVMTrain(Mat, Mat, string);
	void SVMTrain(Mat, Mat, CvSVMParams, string);
	//Adaboost default
	CvSVMParams AdaboostDefaultParams(void);
	//Train & Save	
	void AdaboostTrain(Mat, Mat, string);
	void AdaboostTrain(Mat, Mat, CvSVMParams, string);
};


#endif // CLASSIFIERS_H
