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

class Classifiers {
private:
	CvSVM SVM;
	CvSVMParams params;
public:
	//Constructores
	Classifiers(void);
	Classifiers(CvSVM,CvSVMParams);
	Classifiers(const Classifiers&);
	//Train & Save	
	vector<float> HogVectorSVMTrain(Mat, Mat, string);
	vector<float> HogVectorSVMTrain(Mat, Mat, CvSVMParams, string);
	//Load
	vector<float> HogVectorSVMLoad(string);
	//Detect 


};


#endif // CLASSIFIERS_H
