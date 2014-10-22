#include "classifiers.h"

//Constructor vacio
Classifiers::Classifiers(void)
{
	this->SVM = CvSVM();
	this->params = CvSVMParams();
}

//Construxtor General
Classifiers::Classifiers(CvSVM SVM_, CvSVMParams params_)
{
	this->SVM = CvSVM(SVM_);
	this->params = CvSVMParams(params_);
}

//Cosntructor copia
Classifiers::Classifiers(const Classifiers& Classifiers_)
{
	this->SVM = CvSVM(Classifiers_.SVM);
	this->params = CvSVMParams(Classifiers_.params);
}

//Entrenar y guardar modelo con parametros por defecto
vector<float> Classifiers::HogVectorSVM(Mat decriptors, Mat labels, string filename)
{
	return HogVectorSVM(Mat, Mat, SVM.get_params(), filename);
}

//Entrenar y guardar modelo
vector<float> Classifiers::HogVectorSVM(Mat decriptors, Mat labels, CvSVMParams params_, string filename)
{
	SVM.train(decriptors, labels, Mat(), Mat(), params:_);

	SVM.save(filename);

	const float* suport_vector = SVM.get_support_vector(0);

	vector<float>  peopleDetector {suport_vector,suport_vector+decriptors.cols};

	return peopleDetector;
}

//Cargar Modelo SVM
vector<float> Classifiers::HogVectorSVMLoad(string filename){
	
	SVM.load(filename);

	const float* suport_vector = SVM.get_support_vector(0);

	int suport_vector_size = end(suport_vector) - begin(suport_vector);

	vector<float>  peopleDetector {suport_vector,suport_vector+suport_vector_size};

	return peopleDetector;

}