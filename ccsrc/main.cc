#include <stdio.h>
#include <string.h>
#include <omp.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include "annotation.h"
#include "classifiers.h"
#include "descriptors.h"
#include "detectors.h"
#include "matrix_generator.h"
#include "neighbourhood_matrix.h"

using namespace std;
using namespace cv;
namespace po = boost::program_options;

typedef struct TrainSet{
	Mat labels;
	Mat descriptors;
	int width;
	int height;
} TrainSet;

enum ClassifierSelector
{
	SVM_CLASSIFIER,
	BOOST_CLASSIFIER
};

vector<TrainSet> getDescriptors(string filename_pos, string filename_neg);
vector<string> trainClassifiers(vector<TrainSet> TrainSets, ClassifierSelector ml);
vector<Sigmoid> trainSigmoid(vector<TrainSet> TrainSets,  vector<string> models, ClassifierSelector ml);
void DetectionBucle(string img_list, vector<Sigmoid> sigmoids,vector<string> models, ClassifierSelector ml);
HOGDescriptor GenerateHOG(int width, int height);

int main(int argc, char** argv)
{

	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
	("help", "produce help message")
	("positive,p", po::value<string>(), "set positive training image list")
	("negative,n", po::value<string>(), "set negative training image list")
	("test,t", po::value<string>(), "set test file list")
	("classifier,c", po::value<string>(), "set classifiers, svm and boost are supported")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}

	if (!vm.count("positive")) {
		cout << "Positive training images file was not set\n" ;
		return 1;
	} else if(!vm.count("negative")) {
		cout << "Negative training images file was not set\n" ;
		return 1;
	}else if(!vm.count("test")) {
		cout << "Test images file was not set\n" ;
		return 1;
	}else if(!vm.count("classifier")) {
		cout << "Classifier was not set\n" ;
		return 1;
	}else{


		string clf = vm["classifier"].as<string>();
		ClassifierSelector ml;
		if(clf.compare("svm")==0)
		{
			ml = SVM_CLASSIFIER;
		}
		else if(clf.compare("boost")==0)
		{
			ml = BOOST_CLASSIFIER;
		}
		else
		{
			cout << "svm and boost classifiers are supported\n" ;
			return 1;
		}

		string pos = vm["positive"].as<string>();
		string neg = vm["negative"].as<string>();
		string test = vm["test"].as<string>();

		cout << "1.- Obtaninig Features...\n";
		vector<TrainSet> training_sets = getDescriptors(pos,neg);
		cout << "2.- Training Classifier...\n";
		vector<string> models = trainClassifiers(training_sets,ml);
		cout << "3.- Training Sigmoid...\n";
		vector<Sigmoid> sigmoids = trainSigmoid(training_sets,models,ml);
		cout << "4.- Detecting people...\n";
		DetectionBucle(test,sigmoids,models,ml);
	}

	return 0;
	
}

vector<TrainSet> getDescriptors(string filename_pos, string filename_neg)
{
	vector<TrainSet> vec;

	ifstream train_pos_list_files(filename_pos);
	ifstream train_neg_list_files(filename_neg);

	string list_file_pos;
	string list_file_neg;


	while(getline(train_pos_list_files,list_file_pos) && getline(train_neg_list_files,list_file_neg)) {

		TrainSet v;

		string positive = list_file_pos;

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
		cout << positive << endl;
		Mat hog_descriptors(dc.ComputeHOG(positive,list_file_neg));
		Mat hog_labels(dc.get_labels());

		v.labels = hog_labels;
		v.descriptors = hog_descriptors;

		vec.push_back(v);
	}

	return vec;
}

vector<string> trainClassifiers(vector<TrainSet> descriptors,ClassifierSelector ml)
{
	vector<string> names;

	string boostBasename = "adaboost_hog_";
	string svmBasename = "svm_hog_";

	for(TrainSet descriptor: descriptors) {


		string sizeName = to_string(descriptor.width) + string("x") + to_string(descriptor.height) + string(".xml");

		cout << "Training " << sizeName <<" model..." << endl; 
		
		if(ml==SVM_CLASSIFIER){
			string svmName  = svmBasename + sizeName;
			Classifiers svm;
			svm.SVMTrain(descriptor.descriptors,descriptor.labels, svmName);
			names.push_back(svmName);
		}else if(ml==BOOST_CLASSIFIER){
			string boostName = boostBasename + sizeName;
			Classifiers ada;
			ada.AdaboostTrain(descriptor.descriptors,descriptor.labels,boostName);
			names.push_back(boostName);
		}
	}

	return names;

}

vector<Sigmoid> trainSigmoid(vector<TrainSet> trainsets,  vector<string> models, ClassifierSelector ml)
{
	int count = 0;
	vector<Sigmoid> trained_sigmoids;
	for(TrainSet trainset: trainsets) {

		vector<float> results;//Results of the detections

		//Size of the detection window
		int rows = trainset.height;
		int cols = trainset.width;

		Mat hog_label_mat(trainset.labels);
		Mat hog_mat(trainset.descriptors);

		int prior1 = 0;
		int prior0 = 0;

		vector<bool> target(hog_mat.rows,false);
		
		CvSVM SVM;
		CvBoost boost;
		if(ml==SVM_CLASSIFIER){				
			SVM.load(models.at(count).c_str());
		} else if (ml == BOOST_CLASSIFIER){
			boost.load(models.at(count).c_str());
		}

		cout << "Evaluating " << cols << "x" << rows << " train set..." << endl; 
		for (int x = 0; x < hog_mat.rows; x++)
		{
			if(hog_label_mat.at<float>(x,0)==1){
				target[x] = true;
				prior1++;
			}else{
				prior0++;
			}

			Mat desc = hog_mat.row(x);

			if(ml==SVM_CLASSIFIER){
				float r = SVM.predict(desc,true);
				results.push_back(r);
			} else if (ml == BOOST_CLASSIFIER){
				float e = boost.predict(desc,Mat(),Range::all(),false,true);
				results.push_back(e);	
			}
		}		
		count++;
		cout << "Training using " << cols << "x" << rows << " train set..." << endl; 
		Sigmoid sigmoid(cols,rows);
		sigmoid.SigmoidTrainLin(results,target,prior1,prior0);	
		cout << "A: " << sigmoid.get_a() << " - B: " << sigmoid.get_b() << endl;
		trained_sigmoids.push_back(sigmoid);
	}
	return trained_sigmoids;	
}

void DetectionBucle(string img_list,vector<Sigmoid> sigmoids, vector<string> models, ClassifierSelector ml)
{
	int count = 0;
	ifstream img_files(img_list);
	string list_filename;
	vector<string> lists;
	while(getline(img_files,list_filename)) {
		lists.push_back(list_filename);
	}

	for(Sigmoid sigmoid : sigmoids) 
	{
		
		if(ml==SVM_CLASSIFIER)
		{	

			string folder = "svm_out_"+to_string(sigmoid.get_width())+"x"+to_string(sigmoid.get_height())+"/";
			string mkdir = "mkdir "+folder;
			int o = system(mkdir.c_str());
			HOGDescriptor hog = GenerateHOG(sigmoid.get_width(),sigmoid.get_height());
			Detectors detector(hog);
			cout << "Loading model " << models.at(count) << "..." << endl;
			detector.LoadSVM(models.at(count));	
			cout << "Detecting " << lists.at(count) << "..." << endl;		
			detector.HOGSVMDetectBuclePrint(lists.at(count), folder, sigmoid);
			count++;
		}
		else if(ml==BOOST_CLASSIFIER)
		{
			string folder = "boost_out_"+to_string(sigmoid.get_width())+"x"+to_string(sigmoid.get_height())+"/";
			string mkdir = "mkdir "+folder;
			int o = system(mkdir.c_str());
			HOGDescriptor hog = GenerateHOG(sigmoid.get_width(),sigmoid.get_height());
			Detectors detector(hog);
			cout << "Loading model " << models.at(count) << "..." << endl;
			detector.LoadAdaboost(models.at(count));
			cout << "Detecting " << lists.at(count) << "..." << endl;
			detector.HOGAdaboostDetectBuclePrint(lists.at(count),folder, sigmoid);
			count++;
		}
	}
}

HOGDescriptor GenerateHOG(int width, int height)
{
	HOGDescriptor hog;
	hog.winSize = Size(width, height) ;
	hog.blockSize = Size(16,16);
	hog.blockStride = Size(8,8);
	hog.cellSize = Size(8,8);
	int nbins = 9;
	return hog;
}