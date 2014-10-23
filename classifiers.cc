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
	CvSVM SVM;
	return HogVectorSVMTrain(decriptors, labels, SVM.get_params(), filename);
}

//Entrenar y guardar modelo
vector<float> Classifiers::HogVectorSVMTrain(Mat decriptors, Mat labels, CvSVMParams params_, string filename)
{
	CvSVM SVM;

	SVM.train(decriptors, labels, Mat(), Mat(), params_);

	SVM.save(filename.c_str());

	const float* suport_vector = SVM.get_support_vector(0);

	vector<float>  peopleDetector {suport_vector,suport_vector+decriptors.cols};

	return peopleDetector;
}

//Cargar Modelo SVM
vector<float> Classifiers::HogVectorSVMLoad(string filename){
	
	CvSVM SVM;

	SVM.load(filename.c_str());

	const float* suport_vector = SVM.get_support_vector(0);

	int suport_vector_size = sizeof(suport_vector_size)/sizeof(float);

	vector<float>  peopleDetector {suport_vector,suport_vector+suport_vector_size};

	return peopleDetector;

}