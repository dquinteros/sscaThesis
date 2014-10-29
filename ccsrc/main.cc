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
	
	cout << "Computing Hog Descriptors..." << endl;
	Descriptors dc;

	string filename_pos(argv[1]);	
	string filename_neg(argv[2]);

	Mat hog_decriptors(dc.ComputeHOG(filename_pos,filename_neg));
	Mat hog_labels(dc.get_labels());

	cout << hog_decriptors.at<float>(0,0) << endl;
	
	cout << "Done." << endl;
	cout << "Training Linear SVM..." << endl;

	CvSVMParams params = get_default_svm_params();	

	Classifiers classifier;

	vector<float> peopleDetector = classifier.HogVectorSVMTrain(hog_decriptors,hog_labels, params,"hog_svm_3.xml");

	//vector<float> peopleDetector = classifier.HogVectorSVMLoad("hog_svm_2.xml");

	cout << "Done." << endl;	
	cout << "Detecting People..." << endl;

	HOGDescriptor hog = get_default_hog_decriptor();

	hog.setSVMDetector(peopleDetector);

	Detectors detectors(hog);

	string imgs(argv[3]); 
	string annotations(argv[4]);

	detectors.HogDetectBucleShow(imgs, annotations);
	cout << "Done." << endl;

	return 0;
	
}

CvSVMParams get_default_svm_params()
{
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC;    
	params.kernel_type = CvSVM::LINEAR;    
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 10000000, FLT_EPSILON);  
	params.C = 0.01;
	return params;
}
HOGDescriptor get_default_hog_decriptor()
{
	HOGDescriptor  hog;
	hog.winSize = Size(64,128);
	hog.blockSize  = Size(16,16);
	hog.blockStride = Size(8,8);
	hog.cellSize = Size(8,8);
	return hog;
}