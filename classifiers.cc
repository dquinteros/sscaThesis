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
vector<float> Classifiers::HogVectorSVMTrain(Mat decriptors, Mat labels, string filename)
{
	LinearSVM SVM;
	return HogVectorSVMTrain(decriptors, labels, SVM.get_params(), filename);
}

//Entrenar y guardar modelo
vector<float> Classifiers::HogVectorSVMTrain(Mat decriptors, Mat labels, CvSVMParams params_, string filename)
{
	LinearSVM SVM;

	SVM.train(decriptors, labels, Mat(), Mat(), params_);

	SVM.save(filename.c_str());

	vector<float> suport_vector;

	SVM.getSupportVector(suport_vector);

	return suport_vector;
}

//Cargar Modelo SVM
vector<float> Classifiers::HogVectorSVMLoad(string filename){
	
	LinearSVM SVM;

	SVM.load(filename.c_str());

	vector<float> suport_vector;

	SVM.getSupportVector(suport_vector);

	return peopleDetector;

}