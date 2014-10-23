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
Mat Descriptors::ComputeHOG(string filename)
{
	ifstream file(filename);	
	hog.winSize = Size(64,128);
    hog.blockSize  = Size(16,16);
    hog.blockStride = Size(8,8);
    hog.cellSize = Size(8,8);

	if(!file)
	{		
		fprintf( stderr, "ERROR: the specified file could not be loaded\n");		
	}else{
		string file_line;
		Mat img;
		vector<vector<float>> descriptor_vector = vector<vector<float>>();
		vector<float> descriptor_result = vector<float>();
		while(getline(file, file_line))
		{
			
			//cout << "Imagen: " << file_line << endl;
			img = imread(file_line);

			if (!img.data)
			{
				continue;
			}

			//332, 348
			Mat resized_img;
			descriptor_result.size();
			//int x_multiple = img.rows/64;
			//int y_multiple = img.cols/128;
			resize(img,resized_img,cv::Size(64, 128));			
			hog.compute(resized_img,descriptor_result);
			descriptor_vector.push_back(descriptor_result);	
		}

		int rows = descriptor_vector.size();
		int cols = descriptor_result.size();

		//cout << rows << "," << cols << endl;
		
		float** data = new float*[rows];

		for (int i = 0; i < rows; i++)
		{
			data[i] = new float[cols];
		}

		for (int x = 0; x < rows; x++)
		{
			for (int y = 0; y < cols; y++)
			{
				data[x][y] = descriptor_vector[x][y];
			}
		}

		Mat hog_mat = Mat(rows, cols, CV_32FC1, data);
		
		return hog_mat;
	}

	Mat nullMat;
	return nullMat;
	
}