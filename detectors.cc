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
	vector<double> peso;

	double t = (double)getTickCount();
	hog.detectMultiScale(img, found, peso, 0, Size(1,1), Size(32,32), 1.05, 0);
	t = (double)getTickCount() - t;

	cout << "tdetection time = "<< t*1000./cv::getTickFrequency() << "ms" << endl;

	int i = 0;

	for(Rect r :  found )
	{		
		Point ce = Point((r.tl().x+r.br().x)/2,(r.tl().y+r.br().y)/2);
		line( img, ce,ce, Scalar(255*peso[i], 0, 0),1,8);
		//r.x += cvRound(r.width*0.1);
        //r.width = cvRound(r.width*0.75);
        //r.y += cvRound(r.height*0.075);
        //r.height = cvRound(r.height*0.7);
		rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 1);
		i++;
	} 
	
	for (Point p : annotation.get_object_center())
	{
		line( img, p,p, Scalar( 0, 0, 255 ),4,8);
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

vector<NeighbourhoodMatrix> Detectors::HogDetectPrint(string img_filename, string annotation_filename)
{
	Annotation annotation;
	annotation.ReadAnnotation(annotation_filename);
	Mat img = imread(img_filename);
	vector<NeighbourhoodMatrix> neighbourhood_vector;
	if(!img.data)
		return neighbourhood_vector;

	vector<Rect> found;
	vector<double> peso;

	double t = (double)getTickCount();
	hog.detectMultiScale(img, found, peso, 0, Size(1,1), Size(32,32), 1.05, 0);
	t = (double)getTickCount() - t;

	cout << "tdetection time = "<< t*1000./cv::getTickFrequency() << "ms" << endl;

	int rows = img.rows*0.15;
	int cols = img.cols*0.15;

	vector<vector<double>> neighbourhood_matrix(rows*2,vector<double>(cols*2,0.0));

	if(peso.size() == found.size()){

		for (Point center : annotation.get_object_center()){		

			Point up_left = Point(center.x-cols, center.y-rows);
			Point down_right = Point(center.x+cols,center.y+rows);

			Rect ROI(up_left,down_right);
			//cout << ROI.height << "," << ROI.width << "=" << neighbourhood_matrix.size() << "," << neighbourhood_matrix.front().size() << endl;

			int i = 0;
			for(Rect r :  found)
			{
				Point ce = Point((r.tl().x+r.br().x)/2,(r.tl().y+r.br().y)/2);
				if(ROI.contains(ce))
				{
					int corrected_x = ce.x - ROI.tl().x;
					int corrected_y = ce.y - ROI.tl().y;

					if(neighbourhood_matrix[corrected_y][corrected_x]<peso[i]){ 					
						neighbourhood_matrix[corrected_y][corrected_x] = peso[i];
					}
				}
				i++;
			}

			NeighbourhoodMatrix aux(neighbourhood_matrix);
			neighbourhood_vector.push_back(aux);
			neighbourhood_matrix.resize(rows*2,vector<double>(cols*2,0.0));
		}
	}

	return neighbourhood_vector;
}

vector<NeighbourhoodMatrix> Detectors::HogDetectPrint(string img_filename, string annotation_filename, HOGDescriptor hog_)
{
	this->hog = HOGDescriptor(hog_);
	return HogDetectPrint(img_filename, annotation_filename);
}

vector<NeighbourhoodMatrix> Detectors::HogDetectPrint(string img_filename, string annotation_filename, vector<float> peopleDetector)
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

void Detectors::HogDetectBuclePrint(string img_filename_list, string annotation_filename_list)
{
	ifstream img_filename(img_filename_list);
	ifstream annotation_filename(annotation_filename_list);
	string img_filename_line;
	string annotation_filename_line;
	vector<NeighbourhoodMatrix> neighbourhood_vector;
	while(getline(img_filename, img_filename_line) && getline(annotation_filename, annotation_filename_line) ) {

		neighbourhood_vector = HogDetectPrint(img_filename_line, annotation_filename_line);
		img_filename_line.erase(img_filename_line.find_last_of("."), string::npos);
		img_filename_line.erase(0,img_filename_line.find_last_of("/")+1);
		int i = 1;
		for(NeighbourhoodMatrix neighbourhood_matrix : neighbourhood_vector) {
			string file = boost::lexical_cast<string>("out/")+img_filename_line+boost::lexical_cast<string>("_")+boost::lexical_cast<string>(i)+boost::lexical_cast<string>(".mat");
			cout << file << endl;
			neighbourhood_matrix.WriteNeigbourhoodMatrix(file);
			i++;
		};
		
	}
}
