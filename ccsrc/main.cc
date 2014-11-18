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

typedef struct DescriptorVector{
	Mat labels;
	Mat decriptors;
	int width;
	int height; 
} DescriptorVector;


typedef struct SigmoidConstants{
	double A;
	double B;
	int width;
	int height; 
} SigmoidConstants;


vector<DescriptorVector> getDescriptors(string filename_pos, string filename_neg);
vector<string> trainClassifiers(vector<DescriptorVector> descriptors);
vector<string> traingSigmoid(vector<DescriptorVector> descriptors,  vector<string> models);
//int printversion();

int main(int argc, char** argv)
{
	/*cout << "Computing Descriptors..." << endl;

	cout << "Done." << endl;

	cout << "Training & Saving Classifiers..." << endl;	

	cout << "Done." << endl;
	
	cout << "Detecting People..." << endl;

	Descriptors cd;	
	Detectors detectors(cd.DefaultHOGDescriptor());
	detectors.LoadAdaboost("hog_adaboost.xml");
	string imgs(argv[3]);	
	detectors.HOGAdaboostDetectBucleShow(imgs);

	cout << "Done." << endl;*/

	string l(argv[4]);

	vector<DescriptorVector>  = getDescriptors(l);


	return 0;
	
}

vector<DescriptorVector> getDescriptors(string filename_pos, string filename_neg)
{
	vector<DescriptorVector> vec;

	ifstream train_pos_list_files(filename_pos);
	ifstream train_neg_list_files(filename_neg);

	string list_file_pos;
	string list_file_neg;


	while(getline(train_pos_list_files,list_file_pos) && getline(train_neg_list_files,list_file_neg)) {

		DescriptorVector v;

		string name_pos = list_file_pos;

		vector<string> sp_list_file;
		list_file_pos.erase(list_file_pos.find_last_of("."), string::npos);
		list_file_pos.erase(0,list_file_pos.find_last_of("/")+1);
		boost::split(sp_list_file,list_file_pos,boost::is_any_of("_"));
		v.width = stoi(sp_list_file.at(2));
		v.height = stoi(sp_list_file.at(3));

		HOGDescriptor  hog;
		hog.winSize = Size(v.width,v.height);
		hog.blockSize  = Size(16,16);
		hog.blockStride = Size(8,8);
		hog.cellSize = Size(8,8);

		Descriptors dc(hog);		
		Mat hog_decriptors(dc.ComputeHOG(name_pos,list_file_neg));
		Mat hog_labels(dc.get_labels());

		v.labels = hog_labels
		v.descriptors = hog_decriptors;

		vec.push_back(v);
	}

	return vec;
}

vector<string> trainClassifiers(vector<DescriptorVector> descriptors)
{
	vector<string> names;

	string boostBasename = "adaboost_hog_";
	string svmBasename = "svm_hog_";

	for(DescriptorVector descriptor: descriptors) {

		string sizeName = to_string(descriptor.width) + string("x") + to_string(descriptor.height) + string(".xml");
		
		string svmName  = svmBasename + sizeName;
		string boostName = boostBasename + sizeName;

		Classifiers svm;
		svm.SVMTrain(descriptor.descriptors,descriptor.labels, svmName);
		names.push_back(svmName);
		Classifiers ada;
		ada.AdaboostTrain(descriptor.descriptors,descriptors.labels,boostName);
		names.push_back(boostName);
		
	}

	return names;

}

vector<string> traingSigmoid(vector<DescriptorVector> descriptors,  vector<string> models)
{
	int count = 0;

	vector<SigmoidConstants> sc;

	for(DescriptorVector d: descriptors) {

		SigmoidConstants aux_sc_svm;
		SigmoidConstants aux_sc_boost;

		vector<float> svm_results;
		vector<float> boost_results;

		int rows = d.height;
		int cols = d.width;

		aux_sc_svm.width = cols;
		aux_sc_svm.height = height;
		aux_sc_boost.width = cols;
		aux_sc_boost.height = height;

		Mat hog_label_mat = d.labels;
		Mat hog_mat = d.descriptors;

		int prior1 = 0;
		int prior0 = 0;

		vector<vector<float>> descriptor_vector(rows, vector<float>(cols,0.0));
		vectr<bool> target(rows,false);

		for (int x = 0; x < rows; x++)
		{
			if(target_mat.at<float>(x,0)==1){
				target[x] = true;
				prior1++;
			}else{
				prior0++;
			}

			Mat desc = hog_mat.row(0);

			CvSVMParams svm_params;
			params.svm_type = CvSVM::C_SVC;    
			params.kernel_type = CvSVM::LINEAR;    
			params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 10000, FLT_EPSILON);  
			params.C = 0.002;

			CvBoostParams boost_params;
			params.boost_type = CvBoost::REAL;
			params.weak_count = 100;
			params.weight_trim_rate = 0.95;
			params.cv_folds = 0;
			params.max_depth = 1;

			CvSVM SVM;
			CvBoost boost;

			SVM.load(models.at(i).c_str());
			float r = SVM.predict(desc,true);
			svm_results.push_back(r);

			boost.load(models.at(i+1));
			float e = boost.predict(desc,Mat(),Range::all(),false,true);
			boost_results.push_back(e);	
		}

		Sigmoid svm_sig;
		Sigmoid boost_sig;

		svm_sig.SigmoidTrain(svm_results,target,prior1,prior0);
		svm_sig.SigmoidTrain(boost_results,target,prior1,prior0);

		count++;
		
	}
	
}