//Leer y Escribir Matrices de tamaño variable
#ifndef __ANNOTATION_H__
#define __ANNOTATION_H__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "opencv2/imgproc/imgproc.hpp"

#include <boost/algorithm/string/classification.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string/split.hpp>


using namespace std;
using namespace cv;
using namespace boost;
using namespace boost::algorithm;

class Annotation
{
private:
	string image_filename;
	int image_width;
	int image_height;	
	int object_number;
	vector<Point> object_head_center;
	vector<Point> object_up_left;
	vector<Point> object_down_right;
	vector<Point> object_center;

public:
	//Constructor
	Annotation(void);
	Annotation(string,int,int,int,vector<Point>,vector<Point>,vector<Point>,vector<Point>);
	Annotation(const Annotation&);
	//Setters
	void set_image_filename(string);
	void set_image_width(int);
	void set_image_height(int);
	void set_object_number(int);
	void set_object_head_center(vector<Point>);
	void set_object_up_left(vector<Point>);
	void set_object_down_right(vector<Point>);
	void set_object_center(vector<Point>);
	//Getters
	string get_image_filename(void){return this->image_filename;}
	int get_image_width(void){return this->image_width;}
	int get_image_height(void){return this->image_height;}	
	int get_object_number(void){return this->object_number;}
	vector<Point> get_object_headcenter(void){return this->object_head_center;}
	vector<Point> get_object_up_left(void){return this->object_up_left;}
	vector<Point> get_object_down_right(void){return this->object_down_right;}
	vector<Point> get_object_center(void){return this->object_center;}	
	//Lectura
	void ReadAnnotation(string);
	//Sobrecarga de operador asignacion
	Annotation& operator= (const Annotation&);
};

#endif