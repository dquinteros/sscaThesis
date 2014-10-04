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
