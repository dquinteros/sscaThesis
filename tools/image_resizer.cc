#include <stdio.h>
#include <string>
#include <fstream>
#include <sys/stat.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../ccsrc/annotation.h"

#define BORDER 300

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//string img_list_filename(string(argv[1]));
	//string annotation_list_filename(string(argv[2]));
	int abs_width = atoi(argv[1]);
	int abs_height = atoi(argv[2]);
	ifstream img_list(argv[3]);
	ifstream annotation_list(argv[4]);
	float percentage = atoi(argv[5]);
	string base;
	if(atoi(argv[6])==0){
		base = "INRIAPerson/test_crop_";
	}else if(atoi(argv[6])==1){
		base = "INRIAPerson/train_crop_";
	}else{
		return 0;
	}
	
	string size = to_string(abs_width)+string("x")+to_string(abs_height);
	string sufix = "/pos";
	string ext = ".png";
	string basename = base+size+sufix;
	cout << basename << endl;
	string mkdir = string("mkdir -p ")+basename;
	system(mkdir.c_str());

	string img_filename;
	string annotation_filename;

	//namedWindow("People Detector", 1);

	while(getline(img_list, img_filename) && getline(annotation_list, annotation_filename) ) {
		Annotation annotation;
		annotation.ReadAnnotation(annotation_filename);
		Mat img = imread(img_filename);
		Mat img_extended;
		img_filename.erase(0,img_filename.find_last_of("/"));
		img_filename.erase(img_filename.find_last_of("."), string::npos);
		int i = 0;

		for(Rect roi : annotation.get_object()) {			
			//rectangle(img, roi.tl(), roi.br(), cv::Scalar(0,255,0), 1);
            if(atoi(argv[6])!=1)
            {
            int x = img.cols * (percentage/100);
            int y = img.rows * (percentage/100);

             Rect nroi(BORDER+roi.x-x,BORDER+roi.y-y,roi.width+(2*x),roi.height+(2*y));

             copyMakeBorder(img, img_extended, BORDER, BORDER, BORDER, BORDER, BORDER_REPLICATE);
			//rectangle(img_extended, nroi.tl(), nroi.br(), cv::Scalar(0,0,255), 1);	
             Mat aux = img_extended(nroi);
             Mat crop;
             aux.copyTo(crop);
             float coef_x =  (abs_width*crop.cols)/roi.width;
             float coef_y =  (abs_height*crop.rows)/roi.height;
             resize(crop,crop,cv::Size(coef_x, coef_y));	
             i++;
             imwrite(basename+string("/")+img_filename+to_string(i)+ext,crop);
         }
         else
         {
            copyMakeBorder(img, img_extended, BORDER, BORDER, BORDER, BORDER, BORDER_REPLICATE);

            float coef_x =  (abs_width*img_extended.cols)/roi.width;
            float coef_y =  (abs_height*img_extended.rows)/roi.height;

            resize(img_extended,img_extended,cv::Size(coef_x, coef_y));

            Rect nroi(BORDER+roi.x,BORDER+roi.y,roi.width,roi.height);

            int new_x = (nroi.x * coef_x)/(img.cols+2*BORDER);
            int new_y = (nroi.y * coef_y)/(img.rows+2*BORDER);

            Rect cutter(new_x-16,new_y-16,abs_width+32,abs_height+32);
            Mat crop = img_extended(cutter);

            imwrite(basename+string("/")+img_filename+to_string(i)+ext,crop);
        }

			//int x_new = (crop.cols/2)-(abs_width/2);
			//int y_new = (crop.rows/2)-(abs_height/2);
			//Rect new_people(x_new,y_new,abs_width,abs_height);
			//rectangle(crop, new_people.tl(), new_people.br(), cv::Scalar(0,0,255), 1);
    }

		//imshow("People Detector", crop);
		//int c = waitKey(0) & 255;
		//if( c == 'q' || c == 'Q')
		//	break;		
}

return 0;	
}