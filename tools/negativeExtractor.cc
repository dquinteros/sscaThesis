#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

	int hog_width = atoi(argv[1]);
	int hog_height = atoi(argv[2]);
	string base = "INRIAPerson/train_neg_";
	string size = to_string(hog_width)+string("x")+to_string(hog_height);
	string sufix = "/neg";
	string ext = ".png";
	string basename = base+size+sufix;
	cout << basename << endl;
	string mkdir = string("mkdir -p ")+basename;
	int i = system(mkdir.c_str());

	string file(argv[3]);

	ifstream file_neg(file);
	string file_line;
 
	int count = 1;
	Mat img;
	while(getline(file_neg, file_line))
	{
		img = imread(file_line);
		file_line.erase(0,file_line.find_last_of("/"));
		file_line.erase(file_line.find_last_of("."), string::npos);

		if(!img.data)
			continue;
		if(img.rows+6>hog_height && img.cols+6>hog_width){
			for(int i = 0; i < 30; i++) {
				int x = rand() % (img.cols-3-hog_width) + 3; 
				int y = rand() % (img.rows-3-hog_height) + 3; 
				Rect roi(x, y, hog_width, hog_height);
				Mat resized_img  = img(roi);
				imwrite(basename+string("/")+file_line+string("_")+to_string(count)+ext,resized_img);
				count++;
			}
		}			
	}
	return 0;	
}