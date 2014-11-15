#include <stdio.h>
#include <string.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include "annotation.h"
#include "classifiers.h"
#include "descriptors.h"
#include "detectors.h"
#include "matrix_generator.h"
#include "neighbourhood_matrix.h"

using namespace std;
using namespace cv;

CvSVMParams get_default_svm_params();
HOGDescriptor get_default_hog_decriptor();
//int printversion();

int main(int argc, char** argv)
{
	
	/*cout << "Computing Descriptors..." << endl;

	Descriptors dc;
	string filename_pos(argv[1]);	
	string filename_neg(argv[2]);
	Mat hog_decriptors(dc.ComputeHOG(filename_pos,filename_neg));
	Mat hog_labels(dc.get_labels());
	
	cout << "Done." << endl;

	cout << "Training & Saving Classifiers..." << endl;	

	Classifiers svm;
	svm.SVMTrain(hog_decriptors,hog_labels,"hog_adaboost.xml");
	Classifiers ada;
	ada.AdaboostTrain(hog_decriptors,hog_labels,"hog_adaboost.xml");

	cout << "Done." << endl;*/
	
	cout << "Detecting People..." << endl;

	Descriptors cd;	
	Detectors detectors(cd.DefaultHOGDescriptor());
	detectors.LoadAdaboost("hog_adaboost.xml");
	string imgs(argv[3]);	
	detectors.HOGAdaboostDetectBucleShow(imgs);

	cout << "Done." << endl;

	return 0;
	
}
