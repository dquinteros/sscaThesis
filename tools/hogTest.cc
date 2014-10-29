#include <stdio.h>
#include <string.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	
	Mat img;
	img = imread("train/neg/bike_022.png");

	vector<float> descriptor_result;
	HOGDescriptor hog;

	hog.winSize = Size(64,128);
	hog.blockSize = Size(16,16);
	hog.blockStride = Size(8,8);
	hog.cellSize = Size(8,8);

	cout << img.rows << "," << img.cols << endl;

	hog.compute(img,descriptor_result);

	int x;
	for(float i : descriptor_result) {
		if(x>4)
			break;
		cout << i << " | " ;
		x++;
	}
	cout << endl;

	return 0;	
}
