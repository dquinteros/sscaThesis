#include "annotation.h"

//Constructor vacio
Annotation::Annotation(void)
{
	this->image_filename = string();
	this->image_width = 0;
	this->image_height = 0;
	this->object_number = 0;
	this->object_head_center = vector<Point>();
	this->object_up_left = vector<Point>();
	this->object_down_right = vector<Point>();
	this->object_center = vector<Point>();
}
//Constructor general
Annotation::Annotation(string image_filename_,int image_width_,int image_height_,int object_number_,vector<Point> object_head_center_,vector<Point> object_up_left_,vector<Point> object_down_right_,vector<Point> object_center_)
{
	this->image_filename = image_filename_;
	this->image_width = image_width_;
	this->image_height = image_height_;
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
	this->image_width = annotation_.image_width;
	this->image_height = annotation_.image_height;
	this->object_number = annotation_.object_number;
	this->object_head_center = vector<Point>(annotation_.object_head_center);
	this->object_up_left = vector<Point>(annotation_.object_up_left);
	this->object_down_right = vector<Point>(annotation_.object_down_right);
	this->object_center = vector<Point>(annotation_.object_center);
}
//Set image_filename
void Annotation::set_image_filename(string image_filename_)
{
	this->image_filename = image_filename_;
}
//Set image_width
void Annotation::set_image_width(int image_width_)
{
	this->image_width = image_width_;
}
//Set image_height
void Annotation::set_image_height(int image_height_)
{
	this->image_height = image_height_;
}
//Set object_number
void Annotation::set_object_number(int object_number_)
{
	this->object_number = object_number_;
}
//Set object_head_center
void Annotation::set_object_head_center(vector<Point> object_head_center_)
{
	this->object_head_center = object_head_center_;
}
//Set object_up_left
void Annotation::set_object_up_left(vector<Point> object_up_left_)
{
	this->object_up_left = object_up_left_;
}
//Set object_down_right
void Annotation::set_object_down_right(vector<Point> object_down_right_)
{
	this->object_down_right = object_down_right_;
}
//Set object_center
void Annotation::set_object_center(vector<Point> object_center_)
{
	this->object_center = object_center_;
}
//Letura
void Annotation::ReadAnnotation(string filename) {
	
	ifstream file(filename);

	if(!file)
	{
		fprintf( stderr, "ERROR: the specified file could not be loaded\n");
	}
	else
	{

		string file_line;	
		vector<string> splitted_line;
		vector<string> aux_split;

		while(getline(file,file_line)) {

			if (file_line[0]=='#'|| file_line[0]=='\0' || file_line[0]=='O') continue;

			file_line.erase(remove_if(file_line,is_any_of(" \"()")),file_line.end());
			//cout << file_line << endl;
			split(splitted_line,file_line,is_any_of(":"),token_compress_on);

			if ('B'==splitted_line.front()[0])
			{
				split(aux_split,splitted_line.back(),is_any_of("-"),token_compress_on);
				vector<string> up_left;
				vector<string> down_right;
				split(up_left,aux_split.front(),is_any_of(","),token_compress_on);
				split(down_right,aux_split.back(),is_any_of(","),token_compress_on);
				Point up_left_coordinates = Point(stoi(up_left.front()),stoi(up_left.back()));
				Point down_right_coordinates = Point(stoi(down_right.front()),stoi(down_right.back()));
				object_up_left.push_back (up_left_coordinates);
				object_down_right.push_back(down_right_coordinates);
				int center_x = (up_left_coordinates.x+down_right_coordinates.x)/2;
				int center_y = (up_left_coordinates.y+down_right_coordinates.y)/2;
				Point center_coordinates = Point(center_x,center_y);
				aux_split.clear();
			}
			else if ('C'==splitted_line.front()[0])
			{			
				split(aux_split,splitted_line.back(),is_any_of(","),token_compress_on);
				Point head_center = Point(stoi(aux_split.front()),stoi(aux_split.back()));
				object_head_center.push_back(head_center);
			}
			else if ("Objectswithgroundtruth"==splitted_line.front())
			{			
				split(aux_split,splitted_line.back(),is_any_of("{"),token_compress_on);
				object_number = stoi(aux_split.front());
				aux_split.clear();
			}
			else if ("ImagesizeXxYxC"==splitted_line.front())
			{			
				split(aux_split,splitted_line.back(),is_any_of("x"),token_compress_on);
				image_width = stoi(aux_split.at(0));
				image_height = stoi(aux_split.at(1));
				aux_split.clear();
			}
			else if ("Imagefilename"==splitted_line.front())
			{
				image_filename = splitted_line.back();
			}
			splitted_line.clear();
		}		
	}	
}
//Sobrecarga del operador de asignacion
Annotation& Annotation::operator= (const Annotation &annotation_)
{
	image_filename = annotation_.image_filename;
	image_width = annotation_.image_width;
	image_height = annotation_.image_height;	
	object_number = annotation_.object_number;
	object_head_center = vector<Point>(annotation_.object_head_center);
	object_up_left = vector<Point>(annotation_.object_up_left);
	object_down_right = vector<Point>(annotation_.object_down_right);
	object_center = vector<Point>(annotation_.object_center);
}