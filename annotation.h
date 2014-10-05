//Leer y Escribir Matrices de tamaño variable
#ifndef __ANNOTATION_H__
#define __ANNOTATION_H__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/split.hpp>


using namespace std;
using namespace boost::algorithm;

class Annotation
{
private:
	string image_filename;
	int image_height;
	int image_width;
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
	void SetImageFilename(string);
	void SetImageHeight(int);
	void SetImageWidth(int);
	void SetObjectNumber(int);
	void SetObjectHeadCenter(vector<Point>);
	void SetObjectUpLeft(vector<Point>);
	void SetObjectDownRight(vector<Point>);
	void SetObjectCenter(vector<Point>);
	//Getters
	string GetImageFilename(string){return this->image_filename;}
	int GetImageHeight(int){return this->image_height;}
	int GetImageWidth(int){return this->image_width;}
	int GetObjectNumber(int){return this->object_number;}
	vector<Point> SetObjectHeadCenter(vector<Point>){return this->object_head_center;}
	vector<Point> GetObjectUpLeft(vector<Point>){return this->object_up_left;}
	vector<Point> GetObjectDownRight(vector<Point>){return this->object_down_right;}
	vector<Point> GetObjectCenter(vector<Point>){return this->object_center;}	
	//Lectura
	Annotation ReadAnnotation(char*) const;
	//Sobrecarga de operador asignacion
	Annotation& operator= (const Annotation&);
};

#endif