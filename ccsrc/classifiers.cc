#include "classifiers.h"

//Constructor vacio
Classifiers::Classifiers(void)
{
	this->svm_params = LinearSVMDefaultParams();
}

//Construxtor General
Classifiers::Classifiers(CvSVMParams params_)
{
	this->svm_params = params_;
}

//Construxtor General
Classifiers::Classifiers(CvBoostParams params_)
{
	this->boost_params = params_;
}

//Cosntructor copia
Classifiers::Classifiers(const Classifiers& Classifiers_)
{
	this->svm_params = Classifiers_.svm_params;
}

//SVM Linear parametros por defecto
CvSVMParams Classifiers::LinearSVMDefaultParams()
{
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC;    
	params.kernel_type = CvSVM::LINEAR;    
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 10000, FLT_EPSILON);  
	params.C = 0.002;
	return params;
}

//Entrenar y guardar modelo con parametros por defecto
void Classifiers::SVMTrain(Mat descriptors, Mat labels, string filename)
{
	return SVMTrain(descriptors, labels, LinearSVMDefaultParams(), filename);
}

//Entrenar y guardar modelo
void Classifiers::SVMTrain(Mat descriptors, Mat labels, CvSVMParams params_, string filename)
{
	CvSVM SVM;
	SVM.train(descriptors, labels, Mat(), Mat(), params_);
	SVM.save(filename.c_str());
}

//SVM Linear parametros por defecto
CvBoostParams Classifiers::AdaboostDefaultParams()
{
	CvBoostParams params;
	params.boost_type = CvBoost::REAL;
    params.weak_count = 100;
    params.weight_trim_rate = 0.95;
    params.cv_folds = 0;
    params.max_depth = 1;
	return params;
}

//Entrenar y guardar modelo con parametros por defecto
void Classifiers::AdaboostTrain(Mat descriptors, Mat labels, string filename)
{
	return AdaboostTrain(descriptors, labels, AdaboostDefaultParams(), filename);
}

//Entrenar y guardar modelo
void Classifiers::AdaboostTrain(Mat descriptors, Mat labels, CvBoostParams params_, string filename)
{
	CvBoost boost;
	boost.train(descriptors,CV_ROW_SAMPLE, labels, Mat(), Mat(),Mat(), Mat(), params_);
	boost.save(filename.c_str());
}
