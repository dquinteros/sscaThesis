#include "descriptors.h"


//Constructores
Descriptors::Descriptors(void)
{
	this->hog = DefaultHOGDescriptor();
}

Descriptors::Descriptors(HOGDescriptor hog_)
{
	this->hog = HOGDescriptor(hog_);
}

Descriptors::Descriptors(const Descriptors& Descriptors_)
{
	this->hog = HOGDescriptor(Descriptors_.hog);
}

//HOG Tamaño por defecto
HOGDescriptor Descriptors::DefaultHOGDescriptor()
{
	HOGDescriptor  hog;
	hog.winSize = Size(64,128);
	hog.blockSize  = Size(16,16);
	hog.blockStride = Size(8,8);
	hog.cellSize = Size(8,8);
	return hog;
}

//Compute HOG Descriptors
Mat Descriptors::ComputeHOG(string pos_filename, string neg_filename )
{
	ifstream file_pos(pos_filename);
	ifstream file_neg(neg_filename);

	int hog_width = hog.winSize.width;
	int hog_height = hog.winSize.height;

	cout << "Analyzing " << hog_width << "x" << hog_height << " images..." << endl; 

	if(!file_pos || !file_neg)
	{		
		fprintf( stderr, "ERROR:Specified files could not be loaded\n");		
	}else{
		
		string file_line;
		Mat img;		
		vector<vector<float>> descriptor_vector;
		vector<float> descriptor_result;

		cout << "	Positive " << hog_width << "x" << hog_height << " images..." << endl; 

		while(getline(file_pos, file_line))
		{
		
			//cout << file_line << endl;
			img = imread(file_line);

			if(!img.data)
				continue;
			Rect roi(16,16,hog_width,hog_height);
			Mat resized_img = img(roi);
			//resize(img,resized_img,cv::Size(64, 128));
			hog.compute(resized_img,descriptor_result);
			descriptor_vector.push_back(descriptor_result);	
		}

		int rows_pos = descriptor_vector.size();
		cout <<"	"<<rows_pos << " images" << endl;
		srand(getTickCount());

		cout << "	Negative " << hog_width << "x" << hog_height << " images..." << endl; 

		while(getline(file_neg, file_line))
		{
			//cout << file_line << endl;
			img = imread(file_line);

			if(!img.data)
				continue;
			

			Mat resized_img;
			resize(img,resized_img,hog.winSize);
			//resize(img,resized_img,cv::Size(64, 128));
			hog.compute(resized_img,descriptor_result);
			descriptor_vector.push_back(descriptor_result);	

		}			
	

	int rows = descriptor_vector.size();
	int cols = descriptor_result.size();

	int rows_neg = rows - rows_pos;
	cout <<"	"<<rows_neg << " images" << endl;
	vector<float> hog_label(rows_pos,1.0); 
	vector<float> hog_label_neg(rows_neg,-1.0); 
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

	this->hog_labels = Mat(hog_label_mat);
	this->hog_descriptors = Mat(hog_mat);		
	return hog_mat;
}

Mat nullMat;
return nullMat;

}