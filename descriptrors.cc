#include "descriptors.h"


//Constructores
Descriptors::Descriptors(void)
{
	this->hog = HOGDescriptor();
}

Descriptors::Descriptors(HOGDescriptor hog)
{
	this->hog = HOGDescriptor(hog);
}

Descriptors::Descriptors(const Descriptors& Descriptors_)
{
	this->hog = Descriptors_.hog;
}

//Compute HOG Descriptors
vector<float> Descriptors::ComputeHOG(string filename)
{
	ifstream file(filename);
	vector<float> hog_mat = vector<float>();
	if(!file)
	{
		fprintf( stderr, "ERROR: the specified file could not be loaded\n");
		return hog_mat;
	}
	string file_line;
	Mat img;
	while(getline(file, file_line))
	{
		img = imread(file_line);
		if (!img.data)
		{
			continue;
		}
		vector<float> descriptor_result = vector<float>();

		hog.compute(img,descriptor_result,cv::Size(8,8),cv::Size(0,0));
		if(descriptor_result.size()>0)
		{
			for(float d : descriptor_result) 
			{
				hog_mat.push_back(d);
			}
		}
		
	}
	return hog_mat;
}