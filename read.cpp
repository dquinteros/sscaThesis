#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <boost/version.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <vector>

#define ENOUGH 1000

using namespace cv;
using namespace boost::algorithm;
using namespace boost::assign;

std::vector<string> antsread(string filename);
std::vector<int> gtinfo(std::vector<string> ant);
string removeExtension(string filename);

int main(int argc, char** argv)
{
    std::cout << "Boost Version "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minior version
          << BOOST_VERSION % 100                // patch level
          << std::endl;

          std::cout << "OpenCV Version "<< CV_VERSION << std::endl;      

          Mat img;
          std::vector<string> ants;
          std::vector<string> ant;  

    /* Validar cantidad de argumentos de la entrada */
          if( argc == 1 )
          {
            printf("Usage: peopledetect (<image_filename> | <image_list>.txt)  (<anotation_filename> | <anotation_list.txt>)\n");
            return 0;
        }

    /* Abrir archivos de entrada */    
        ants = antsread(argv[1]); 
        ant = antsread(ants.at(0));
        std::vector<int> v = gtinfo(ant);
        return 0;
    }

/*Eliminar la extensión from StackOverflow*/
    string removeExtension(string filename) {
        size_t lastdot = filename.find_last_of(".");
        if (lastdot == string::npos) return filename;
        return filename.substr(0, lastdot); 
    }   

    std::vector<string> antsread(string filename){

        std::cout << filename << std::endl;
        std::vector<string> lines;   
        string line;

        std::ifstream f(filename.c_str());    

        if(!f)
        {
            fprintf( stderr, "ERROR: the specified file could not be loaded\n");
            return lines;
        }

        while (getline(f, line))
        {
            if (line[0]=='#'|| line[0]=='\0') continue;        
            lines+=line;     
        }    
        return lines;
    }

    std::vector<int> gtinfo(std::vector<string> ant){
        std::vector<int> info;
        for (int i = 0; i < ant.size(); i++)
        {
           std::vector<string> sp_line;
           boost::split(sp_line,ant.at(i),boost::is_any_of(":"));
           if(sp_line.at(0)=="Image size (X x Y x C) "){
               std::vector<string> img_size;
               boost::split(img_size,sp_line.at(1),boost::is_any_of("x"));
               trim(img_size.at(0));trim(img_size.at(1));trim(img_size.at(2));
               std::cout << img_size.at(0) << img_size.at(1) << img_size.at(2) << std::endl;
               info += atoi(img_size.at(0).c_str()), atoi(img_size.at(1).c_str()),atoi(img_size.at(2).c_str());  
           }else if(sp_line.at(0)=="Objects with ground truth ") {
               std::vector<string> num_obj;
               boost::split(num_obj,sp_line.at(1),boost::is_any_of("{ "));
               std::cout << num_obj.at(1) << std::endl;
               info += atoi(num_obj.at(1).c_str());     
           }else if(sp_line.at(0)[0]=='C') {
               std::vector<string> center;
               boost::split(center,sp_line.at(1),boost::is_any_of("(,)"));
               trim(center.at(1));trim(center.at(2));
               std::cout << center.at(1) << center.at(2) << std::endl;      
               info += atoi(center.at(1).c_str()),atoi(center.at(2).c_str());
           }
       }
       return info;
   }