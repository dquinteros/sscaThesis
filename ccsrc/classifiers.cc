#include "classifiers.h"

//Constructor vacio
Classifiers::Classifiers(void)
{
	
}

//Construxtor General
Classifiers::Classifiers(CvSVMParams params_)
{
	this->params = params_;
}

//Cosntructor copia
Classifiers::Classifiers(const Classifiers& Classifiers_)
{
	this->params = Classifiers_.params;
}

//Entrenar y guardar modelo con parametros por defecto
vector<float> Classifiers::HogVectorSVMTrain(Mat descriptors, Mat labels, string filename)
{
	LinearSVM SVM;
	return HogVectorSVMTrain(descriptors, labels, SVM.get_params(), filename);
}

//Entrenar y guardar modelo
vector<float> Classifiers::HogVectorSVMTrain(Mat descriptors, Mat labels, CvSVMParams params_, string filename)
{
	LinearSVM SVM;

	SVM.train(descriptors, labels, Mat(), Mat(), params_);

	cout << descriptors.at<float>(0,0) << "-" << descriptors.rows << ","<< descriptors.cols << endl;
	cout << labels.at<float>(0,0) << "-" << labels.rows << ","<< labels.cols << endl;

	SVM.save(filename.c_str());

	//const float* support  = SVM.get_support_vector(0);
	
	vector<float> support_vector ;//= {support,support+descriptors.cols};

	SVM.getSupportVector(support_vector);

	return support_vector;
}

//Cargar Modelo SVM
vector<float> Classifiers::HogVectorSVMLoad(string filename){
	
	LinearSVM SVM;

	SVM.load(filename.c_str());

	vector<float> support_vector;	

	SVM.getSupportVector(support_vector);

	//return support_vector;
	return support_vector;

}