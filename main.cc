#include <stdio.h>
#include <string.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include "annotation.h"
#include "classifiers.h"
#include "descriptors.h"
#include "matrix_generator.h"
#include "neighbourhood_matrix.h"



using namespace std;
using namespace cv;

CvSVMParams get_default_svm_params();
//int printversion();

int main(int argc, char** argv)
{

	Descriptors dc;

	string filename_pos(argv[1]);	

	Mat hog_result_pos(dc.ComputeHOG(filename_pos));

	string filename_neg(argv[2]);

	Mat hog_result_neg(dc.ComputeHOG(filename_neg));

	int rows_pos = hog_result_pos.rows;
	int rows_neg = hog_result_neg.rows; 

	Mat hog_decriptors;
	Mat hog_labels;

	vconcat(hog_result_pos,hog_result_neg,hog_decriptors);

	float* hog_label_pos = new float[rows_pos];
	std::fill(hog_label_pos, hog_label_pos + rows_pos , 1);
	float* hog_label_neg = new float[rows_neg];
	std::fill(hog_label_neg, hog_label_neg + rows_neg , -1);

	Mat pos_label = Mat(rows_pos,1,CV_32FC1,hog_label_pos);
	Mat neg_label = Mat(rows_neg,1,CV_32FC1,hog_label_neg);

	vconcat(pos_label,neg_label,hog_labels);
	
	CvSVMParams params = get_default_params();	

	Classifiers classifier(CvSVM SVM, params);

	

	return 0;
	
}

CvSVMParams get_default_svm_params()
{
	CvSVMParams;
	params.svm_type = CvSVM::C_SVC;    
	params.kernel_type = CvSVM::LINEAR;    
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 1000, FLT_EPSILON);  
	params.C = 0.01;
	return params;
}