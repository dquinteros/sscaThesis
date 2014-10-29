#include "descriptors.h"


//Constructores
Descriptors::Descriptors(void)
{
	this->hog = HOGDescriptor();
}

Descriptors::Descriptors(HOGDescriptor hog_)
{
	this->hog = HOGDescriptor(hog_);
}

Descriptors::Descriptors(const Descriptors& Descriptors_)
{
	this->hog = Descriptors_.hog;
}

//Compute HOG Descriptors
Mat Descriptors::ComputeHOG(string pos_filename, string neg_filename )
{
	ifstream file_pos(pos_filename);
	ifstream file_neg(neg_filename);	
	hog.winSize = Size(64,128);
	hog.blockSize  = Size(16,16);
	hog.blockStride = Size(8,8);
	hog.cellSize = Size(8,8);

	if(!file_pos || !file_neg)
	{		
		fprintf( stderr, "ERROR:Specified files could not be loaded\n");		
	}else{
		
		string file_line;
		Mat img;		
		vector<vector<float>> descriptor_vector;
		vector<float> descriptor_result;
		while(getline(file_pos, file_line))
		{
			//cout << file_line << endl;
			img = imread(file_line);

			if(!img.data)
				continue;
			Rect roi(16,16,64,128);
			Mat resized_img = img(roi);
			//resize(img,resized_img,cv::Size(64, 128));
			hog.compute(resized_img,descriptor_result);
			descriptor_vector.push_back(descriptor_result);	
		}

		int rows_pos = descriptor_vector.size();
		srand(getTickCount());
		while(getline(file_neg, file_line))
		{
			//cout << file_line << endl;
			img = imread(file_line);

			if(!img.data)
				continue;

			for(int i = 0; i < 10; i++) {
				int x = rand() % (img.cols-65) + 1; 
				int y = rand() % (img.rows-128) + 1; 
				Rect roi(x, y, 64, 128);
				Mat resized_img  = img(roi);
				//resize(img,resized_img,cv::Size(64, 128));
				hog.compute(resized_img,descriptor_result);
				descriptor_vector.push_back(descriptor_result);	
			}
			
		}

		int rows = descriptor_vector.size();
		int cols = descriptor_result.size();

		int rows_neg = rows - rows_pos;

		vector<float> hog_label(rows_pos,1); 
		vector<float> hog_label_neg(rows_neg,-1); 
		hog_label.insert(hog_label.end(),hog_label_neg.begin(), hog_label_neg.end());

		Mat hog_mat = Mat(rows, cols, CV_32FC1);
		Mat hog_label_mat = Mat(rows,1,CV_32FC1);

		for (int x = 0; x < rows; x++)
		{
			hog_label_mat.at<float>(x,0) = hog_label[x];			
			for (int y = 0; y < cols; y++)
			{
				hog_mat.at<float>(x,y) = descriptor_vector[x][y];
			}
		}

		this->labels = Mat(hog_label_mat);		
		return hog_mat;
	}

	Mat nullMat;
	return nullMat;
	
}