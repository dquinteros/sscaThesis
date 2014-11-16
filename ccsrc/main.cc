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


vector<DescriptorVector> getDescriptors(string filename_pos, string filename_neg);
vector<string> trainClassifiers(vector<DescriptorVector> descriptors);
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

	vector<DescriptorVector> sasd = getDescriptors(l);


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
		Descriptors dc;		
		Mat hog_decriptors(dc.ComputeHOG(list_file_pos,list_file_neg));
		Mat hog_labels(dc.get_labels());

		v.labels = hog_labels
		v.descriptors = hog_decriptors;

		vector<string> sp_list_file;
		list_file.erase(list_file.find_last_of("."), string::npos);
		list_file.erase(0,list_file.find_last_of("/")+1);
		boost::split(sp_list_file,list_file,boost::is_any_of("_"));
		v.width = stoi(sp_list_file.at(2));
		v.height = stoi(sp_list_file.at(3));

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
		Classifiers ada;
		ada.AdaboostTrain(descriptor.descriptors,descriptors.labels,boostBasename);

		names.push_back;
	}

	return names;

}