#include "detectors.h"

//Constructor vacio
Detectors::Detectors(void)
{
	this->hog = HOGDescriptor();
}

//Constructor General
Detectors::Detectors(HOGDescriptor hog_)
{
	this->hog = HOGDescriptor(hog_);
}

//Constructor Copia
Detectors::Detectors(const Detectors& Detectors_)
{
	this->hog = Detectors_.hog;
}

Mat Detectors::HogDetectShow(string img_filename, string annotation_filename)
{
	Annotation annotation;
	annotation.ReadAnnotation(annotation_filename);
	Mat img = imread(img_filename);
	if(!img.data)
		return img;

	vector<Rect> found;

	double t = (double)getTickCount();
	hog.detectMultiScale(img, found, 0, Size(2,2), Size(32,32), 1.05, 0);
	t = (double)getTickCount() - t;

	cout << "tdetection time = "<< t*1000./cv::getTickFrequency() << "ms" << endl;

	for(Rect r :  found )
	{
		//r.x += cvRound(r.width*0.1);
        //r.width = cvRound(r.width*0.75);
        //r.y += cvRound(r.height*0.075);
        //r.height = cvRound(r.height*0.7);
        //rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 1);
		Point ce = Point((r.tl().x+r.br().x)/2,(r.tl().y+r.br().y)/2);
		line( img, ce,ce, Scalar(255, 0, 0),1,8);

	} 
	
	for (Point p : annotation.get_object_center())
	{
		line( img, p,p, Scalar( 0, 0, 255 ),8,8);
	}

	return img;
}

Mat Detectors::HogDetectShow(string img_filename, string annotation_filename, HOGDescriptor hog_)
{
	this->hog = HOGDescriptor(hog_);
	return HogDetectShow(img_filename, annotation_filename);
}

Mat Detectors::HogDetectShow(string img_filename,string annotation_filename, vector<float> peopleDetector)
{
	this->hog.setSVMDetector(peopleDetector);
	return HogDetectShow(img_filename, annotation_filename);
}

NeighbourhoodMatrix Detectors::HogDetectPrint(string img_filename, string annotation_filename)
{
	Annotation annotation;
	annotation.ReadAnnotation(annotation_filename);
	Mat img = imread(img_filename);
	NeighbourhoodMatrix nhm;
	if(!img.data)
		return nhm;

	vector<Rect> found;
	vector<double> peso;

	double t = (double)getTickCount();
	hog.detectMultiScale(img, found, peso, 0, Size(8,8), Size(32,32), 1.05, 0);
	t = (double)getTickCount() - t;

	cout << "tdetection time = "<< t*1000./cv::getTickFrequency() << "ms" << endl;

	int rows = img.rows * 0.15;
	int cols = img.cols * 0.15;

	float** neighbourhood = new float*[rows];
	for (int i = 0; i < rows; i++)	
		neighbourhood[i] = new float[cols];
	

	for(Rect r :  found)
	{
		//r.x += cvRound(r.width*0.1);
        //r.width = cvRound(r.width*0.75);
        //r.y += cvRound(r.height*0.075);
        //r.height = cvRound(r.height*0.7);
        //rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 1);
		Point ce = Point((r.tl().x+r.br().x)/2,(r.tl().y+r.br().y)/2);
		if(ce.x>ce.y)
		{

		}
		//line( img, ce,ce, Scalar(255, 0, 0),2,8 );

	} 

	vector<vector<double>> neighbourhood_matrix;

	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++)
		{
			neighbourhood_matrix[x][y] = neighbourhood[x][y];
		}
	}

	NeighbourhoodMatrix nh(neighbourhood_matrix);
	return nhm;
}

NeighbourhoodMatrix Detectors::HogDetectPrint(string img_filename, string annotation_filename, HOGDescriptor hog_)
{
	this->hog = HOGDescriptor(hog_);
	return HogDetectPrint(img_filename, annotation_filename);
}

NeighbourhoodMatrix Detectors::HogDetectPrint(string img_filename, string annotation_filename, vector<float> peopleDetector)
{
	this->hog.setSVMDetector(peopleDetector);
	return HogDetectPrint(img_filename, annotation_filename);
}

void Detectors::HogDetectBucleShow(string img_filename_list, string annotation_filename_list)
{
	ifstream img_filename(img_filename_list);
	ifstream annotation_filename(annotation_filename_list);
	string img_filename_line;
	string annotation_filename_line;
	Mat img;
	namedWindow("People Detector", 1);
	while(getline(img_filename, img_filename_line) && getline(annotation_filename, annotation_filename_line) ) {

		img = HogDetectShow(img_filename_line, annotation_filename_line);

		imshow("People Detector", img);

        int c = waitKey(0) & 255;
        if( c == 'q' || c == 'Q')
            break;
	}

}

void Detectors::HogDetectBuclePrint(string img_filename, string annotation_filename)
{

}
