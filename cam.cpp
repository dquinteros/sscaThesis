#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
int main (int argc, const char * argv[])
{
    VideoCapture cap(CV_CAP_ANY);
    if (!cap.isOpened())
        return -1;
 
    Mat img;
    namedWindow("video capture", CV_WINDOW_AUTOSIZE);
    while (true)
    {
        cap >> img;
        imshow("video capture", img);
        if (waitKey(10) >= 0)
            break;
    }
    return 0;
}