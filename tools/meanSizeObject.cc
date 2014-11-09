#include <stdio.h>
#include <string>
#include <fstream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../ccsrc/annotation.h"

#define BORDER 300

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

	ifstream img_list(argv[1]);
	ifstream annotation_list(argv[2]);

	string img_filename;
	string annotation_filename;

	//namedWindow("People Detector", 1);
	int count_img = 0;
	int count_objects = 0;
	int img_rows_sum = 0;
	int img_cols_sum = 0;
	int object_rows_sum = 0;
	int object_cols_sum = 0;
	while(getline(img_list, img_filename) && getline(annotation_list, annotation_filename) ) {
		count_img++;
		Annotation annotation;
		annotation.ReadAnnotation(annotation_filename);
		Mat img = imread(img_filename);
		img_rows_sum += img.rows;
		img_cols_sum += img.cols;
		for(Rect roi : annotation.get_object()) {		
			count_objects++;
			object_rows_sum += roi.height;
			object_cols_sum += roi.width;
		}		
	}

	cout << "Mean Image Size: " << img_cols_sum/count_img  << "," << img_rows_sum/count_img << endl;
	cout << "Mean Object Size: " << object_cols_sum/count_objects << "," << object_rows_sum/count_objects  << endl;

	return 0;	
}