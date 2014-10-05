#include "annotation.h"

//Constructor vacio
Annotation::Annotation(void)
{
	this->image_filename = string();
	this->image_height = 0;
	this->image_width = 0;
	this->object_number = 0;
	this->object_head_center = vector<Point>();
	this->object_up_left = vector<Point>();
	this->object_down_right = vector<Point>();
	this->object_center = vector<Point>();
}
//Constructor general
Annotation::Annotation(string image_filename_,int image_height_,int image_width_,int object_number_,vector<Point> object_head_center_,vector<Point> object_up_left_,vector<Point> object_down_right_,vector<Point> object_center_)
{
	this->image_filename = image_filename_;
	this->image_height = image_height_;
	this->image_width = image_width_;
	this->object_number = object_number_;
	this->object_head_center = vector<Point>(object_head_center_);
	this->object_up_left = vector<Point>(object_up_left_);
	this->object_down_right = vector<Point>(object_down_right_);
	this->object_center = vector<Point>(object_center_);
}
//Constructor copia
Annotation::Annotation(const Annotation& annotation_)
{
	this->image_filename = annotation_.image_filename;
	this->image_height = annotation_.image_height;
	this->image_width = annotation_.image_width;
	this->object_number = annotation_.object_number;
	this->object_head_center = vector<Point>(annotation_.object_head_center);
	this->object_up_left = vector<Point>(annotation_.object_up_left);
	this->object_down_right = vector<Point>(annotation_.object_down_right);
	this->object_center = vector<Point>(annotation_.object_center);
}
//Set image_filename
void Annotation::SetImageFilename(string image_filename_)
{
	this->image_filename = image_filename_;
}
//Set image_height
void Annotation::SetImageHeight(int image_height_)
{
	this->image_height = image_height_;
}
//Set image_width
void Annotation::SetImageWidth(int image_width_)
{
	this->image_width = image_width_;
}
//Set object_number
void Annotation::SetObjectNumber(int object_number_)
{
	this->object_number = object_number_;
}
//Set object_head_center
void Annotation::SetObjectHeadCenter(vector<Point> object_head_center_)
{
	this->object_head_center = object_head_center_;
}
//Set object_up_left
void Annotation::SetObjectUpLeft(vector<Point> object_up_left_)
{
	this->object_up_left = object_up_left_;
}
//Set object_down_right
void Annotation::SetObjectDownRight(vector<Point> object_down_right_)
{
	this->object_down_right = object_down_right_;
}
//Set object_center
void Annotation::SetObjectCenter(vector<Point> object_center_)
{
	this->object_center = object_center_;
}
//Letura
Annotation Annotation::ReadAnnotation(char* filename) {
	
	Annotation read_annotation;
	ifstream file(filename);

	if(!file)
	{
		fprintf( stderr, "ERROR: the specified file could not be loaded\n");
		return read_annotation;
	}

	string file_line;

	if(getline(file,file_line))
	{
		erase_all(file_line," ");

	}

	while(getline(file,file_line)) {
		  if (file_line[0]=='#'|| file_line[0]=='\0') continue;

	}
}