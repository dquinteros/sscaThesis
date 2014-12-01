#include "detectors.h"

//Constructor vacio
Detectors::Detectors(void)
{
	this->hog = HOGDescriptor();
}

//Constructores
Detectors::Detectors(HOGDescriptor hog_)
{
	this->hog = HOGDescriptor(hog_);
}

//Constructor Copia
Detectors::Detectors(const Detectors& Detectors_)
{
	this->hog = Detectors_.hog;
}

//Load SVM
void Detectors::LoadSVM(string svm_model)
{
	this->SVM.load(svm_model.c_str());
}

//Load Adaboost
void Detectors::LoadAdaboost(string boost_model)
{
	this->boost.load(boost_model.c_str());
}

//Deteccion con HOG + SVM unitaria
Mat Detectors::HOGSVMDetectShow(string filename)
{
	Mat img;
	img = imread(filename);
	if(!img.data)
		return img;
	vector<float> descriptor_result;
	for (int x = 3; x < (img.cols-3-hog.winSize.width); x++)
	{
		for (int y = 3; y < (img.rows-3-hog.winSize.height); y++)
		{
			Rect roi(x,y,hog.winSize.width,hog.winSize.height);
			Mat crop = img(roi);
			hog.compute(crop,descriptor_result);
			Mat crop_hog = Mat(1,descriptor_result.size(),CV_32FC1);
			for (int i = 0; i < descriptor_result.size(); i++)
			{
				crop_hog.at<float>(0,i) = descriptor_result[i];
			}

			float result = SVM.predict(crop_hog,true);			
			
			Point ce = Point((roi.tl().x+roi.br().x)/2,(roi.tl().y+roi.br().y)/2);
			line( img, ce,ce, Scalar(0, 0, 255*result),1,8);
			//rectangle(img, roi.tl(), roi.br(), cv::Scalar(0,255*result,0), 1);
		}
	}
	return img;
}
//Deteccion con HOG + SVM unitaria
Mat Detectors::HOGSVMDetectShow(string filename, string svm_model)
{
	this->SVM.load(svm_model.c_str());
	return HOGSVMDetectShow(filename);
}
//
NeighbourhoodMatrix Detectors::HOGSVMDetectPrint(string filename, Sigmoid sig)
{
	Mat img;
	img = imread(filename);
	NeighbourhoodMatrix null_matrix;
	if(!img.data)	
		return null_matrix;
	int rows = img.rows-6-hog.winSize.height;
	int cols = img.cols-6-hog.winSize.width;
	vector<vector<double>> matrix =  vector<vector<double>>(rows, vector<double>(cols,0.0));
	#pragma omp parallel num_threads(34)
	{	
		vector<float> descriptor_result;	
		#pragma omp for schedule(dynamic,rows/50)
		for (int x = 3; x < (img.cols-3-hog.winSize.width); x++)
		{
			
			for (int y = 3; y < (img.rows-3-hog.winSize.height); y++)
			{
				Rect roi(x,y,hog.winSize.width,hog.winSize.height);
				Mat crop = img(roi);
				hog.compute(crop,descriptor_result);
				Mat crop_hog = Mat(1,descriptor_result.size(),CV_32FC1);
				for (int i = 0; i < descriptor_result.size(); i++)
				{
					crop_hog.at<float>(0,i) = descriptor_result[i];
				}
				float result = sig.EvaluateSigmoid(SVM.predict(crop_hog,true));
				#pragma omp critical				
				matrix[y-3][x-3] = (double)result;
			}
		}
	}
	NeighbourhoodMatrix neighbourhood_matrix(matrix);

	return neighbourhood_matrix;

}
NeighbourhoodMatrix Detectors::HOGSVMDetectPrint(string filename, string svm_model, Sigmoid sig)
{
	this->SVM.load(svm_model.c_str());
	return HOGSVMDetectPrint(filename, sig);
}
//Deteccion con SVM bucle
void Detectors::HOGSVMDetectBucleShow(string img_filename_list)
{
	ifstream img_filename(img_filename_list);
	string img_filename_line;
	Mat img;
	namedWindow("People Detector", 1);
	while(getline(img_filename, img_filename_line)) {

		img = HOGSVMDetectShow(img_filename_line);

		imshow("People Detector", img);

		int c = waitKey(0) & 255;
		if( c == 'q' || c == 'Q')
			break;
	}
}
void Detectors::HOGSVMDetectBuclePrint(string img_filename_list, string folder, Sigmoid sig)
{
	ifstream img_filename(img_filename_list);
	string img_filename_line;
	while(getline(img_filename, img_filename_line)) {
		NeighbourhoodMatrix neighbourhood_matrix(HOGSVMDetectPrint(img_filename_line, sig));
		img_filename_line.erase(img_filename_line.find_last_of("."), string::npos);
		img_filename_line.erase(0,img_filename_line.find_last_of("/")+1);
		string file = folder+img_filename_line+boost::lexical_cast<string>(".mat");
		neighbourhood_matrix.WriteNeigbourhoodMatrix(file);
		cout << file << endl;
	}

}
//Deteccion con HOG + Adaboost unitaria
Mat Detectors::HOGAdaboostDetectShow(string filename)
{
	Mat img;
	img = imread(filename);
	if(!img.data)
		return img;
	vector<float> descriptor_result;
	for (int x = 3; x < (img.cols-3-hog.winSize.width); x++)
	{
		for (int y = 3; y < (img.rows-3-hog.winSize.height); y++)
		{
			Rect roi(x,y,hog.winSize.width,hog.winSize.height);
			Mat crop = img(roi);
			hog.compute(crop,descriptor_result);
			Mat crop_hog = Mat(1,descriptor_result.size(),CV_32FC1);
			for (int i = 0; i < descriptor_result.size(); i++)
			{
				crop_hog.at<float>(0,i) = descriptor_result[i];
			}

			float result = boost.predict(crop_hog,Mat(),Range::all(),false,true);

			Point ce = Point((roi.tl().x+roi.br().x)/2,(roi.tl().y+roi.br().y)/2);
			line( img, ce,ce, Scalar(0, 0, 255*result),1,8);
			//rectangle(img, roi.tl(), roi.br(), cv::Scalar(0,255*result,0), 1);
		}
	}
	return img;
}
//Deteccion con HOG + SVM unitaria
Mat Detectors::HOGAdaboostDetectShow(string filename, string boost_model)
{
	this->boost.load(boost_model.c_str());
	return HOGAdaboostDetectShow(filename);
}
//
NeighbourhoodMatrix Detectors::HOGAdaboostDetectPrint(string filename, Sigmoid sig)
{
	Mat img;
	img = imread(filename);
	NeighbourhoodMatrix null_matrix;
	if(!img.data)	
		return null_matrix;
	int rows = img.rows-6-hog.winSize.height;
	int cols = img.cols-6-hog.winSize.width;
	vector<vector<double>> matrix =  vector<vector<double>>(rows, vector<double>(cols,0.0));
	#pragma omp parallel num_threads(34)
	{	
		vector<float> descriptor_result;	
		#pragma omp for schedule(dynamic,rows/50)
		for (int x = 3; x < (img.cols-3-hog.winSize.width); x++)
		{
			
			for (int y = 3; y < (img.rows-3-hog.winSize.height); y++)
			{
				Rect roi(x,y,hog.winSize.width,hog.winSize.height);
				Mat crop = img(roi);
				hog.compute(crop,descriptor_result);
				Mat crop_hog = Mat(1,descriptor_result.size(),CV_32FC1);
				for (int i = 0; i < descriptor_result.size(); i++)
				{
					crop_hog.at<float>(0,i) = descriptor_result[i];
				}
				float result = sig.EvaluateSigmoid(boost.predict(crop_hog,Mat(),Range::all(),false,true));
				#pragma omp critical				
				matrix[y-3][x-3] = (double)result;
			}
		}
	}
	NeighbourhoodMatrix neighbourhood_matrix(matrix);

	return neighbourhood_matrix;
}
NeighbourhoodMatrix Detectors::HOGAdaboostDetectPrint(string filename, string boost_model, Sigmoid sig)
{
	this->boost.load(boost_model.c_str());
	return HOGAdaboostDetectPrint(filename, sig);
}
//Deteccion con SVM bucle
void Detectors::HOGAdaboostDetectBucleShow(string img_filename_list)
{
	ifstream img_filename(img_filename_list);
	string img_filename_line;
	Mat img;
	namedWindow("People Detector", 1);
	while(getline(img_filename, img_filename_line)) {

		img = HOGAdaboostDetectShow(img_filename_line);

		imshow("People Detector", img);

		int c = waitKey(0) & 255;
		if( c == 'q' || c == 'Q')
			break;
	}
}
void Detectors::HOGAdaboostDetectBuclePrint(string img_filename_list,string folder, Sigmoid sig)
{
	ifstream img_filename(img_filename_list);
	string img_filename_line;
	while(getline(img_filename, img_filename_line)) {
		NeighbourhoodMatrix neighbourhood_matrix(HOGAdaboostDetectPrint(img_filename_line, sig));
		img_filename_line.erase(img_filename_line.find_last_of("."), string::npos);
		img_filename_line.erase(0,img_filename_line.find_last_of("/")+1);
		string file = folder+img_filename_line+boost::lexical_cast<string>(".mat");
		neighbourhood_matrix.WriteNeigbourhoodMatrix(file);
		cout << file << endl;
	}

}
