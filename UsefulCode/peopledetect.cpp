#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include <boost/version.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/erase.hpp>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#define ENOUGH 1000

using namespace cv;
using namespace std;
using namespace boost::algorithm;
using namespace boost::assign;

int printversion();
std::vector<string> antsread(string filename);
std::vector<int> gtinfo(std::vector<string> ant);
int writescore(std::vector<int> gtitems, char* filename, double** img, int percent);
string removeExtension(string filename);

int main(int argc, char** argv)
{

  printversion();
  Mat img;
  FILE* f = 0;
  char _filename[1024];
  std::vector<string> ants;
  std::vector<string> ant;
    /* Validar cantidad de argumentos de la entrada */
  if( argc !=5) {
    printf("Usage: peopledetect (<image_filename> | <image_list>.txt)  (<anotation_filename> | <anotation_list.txt>) (<percentage 0-100>) (<show images y/n>)\n");
    return 0;
  }

  int percent = atoi(argv[3]);

  if(percent<0||percent>100){
    printf("El valor porcentual debe estar entre 0 y 100\n");
    return 0;
  }

/* Abrir archivos de entrada */
  img = imread(argv[1]);
  ants = antsread(string(argv[2]));
  int ant_c = 0;
  if( img.data )
  {
    strcpy(_filename, argv[1]);
  }
  else
  {
    f = fopen(argv[1], "rt");
    if(!f)
    {
      fprintf( stderr, "ERROR: the specified file could not be loaded\n");
      return -1;
    }
  }

  HOGDescriptor hog;

  hog.winSize = Size(328,344);
  hog.blockSize  = Size(8,8);
  hog.blockStride = Size(8,8);
  hog.cellSize = Size(8,8);
  
  CvSVM SVM;

  SVM.load("hog_svm_3.xml"); 

  const float* suport_vector = SVM.get_support_vector(0);

  vector<float> peopleDetector {suport_vector,suport_vector+15867};

  hog.setSVMDetector(peopleDetector);

  namedWindow("people detector", 1);


  for(;;)
  {   
    char* filename = _filename;
    std::vector<Rect> found, found_filtered;
    std::vector<double> peso; //Valor del peso entregado por el clasificador
    if(f)
    {
      if(!fgets(filename, (int)sizeof(_filename)-2, f))break;                       
      if(filename[0] == '#')continue;            
      int l = (int)strlen(filename);
      while(l > 0 && isspace(filename[l-1]))--l;            
      filename[l] = '\0';
      img = imread(filename);
      ant = antsread(ants.at(ant_c));
      ant_c++;
    }
    printf("%s:\n", filename);
    if(!img.data)
      continue;

    fflush(stdout);
    std::vector<int> ant_info = gtinfo(ant);

    double** imagen = new double *[ant_info.at(0)];
    for (int i = 0; i < ant_info.at(0); i++)
      imagen[i] = new double [ant_info.at(1)];

    for (int i = 0; i < ant_info.at(0); i++){
      for (int j = 0; j < ant_info.at(1); j++)
        imagen[i][j] = 0;
    }

    double t = (double)getTickCount();
    hog.detectMultiScale(img, found, peso, 0, Size(1,1), Size(32,32), 1.1, 0);

    t = (double)getTickCount() - t;
    printf("tdetection time = %gms\n", t*1000./cv::getTickFrequency());

    if(found.size()!=peso.size()){
      cout<<"!"<<endl;
      continue;
    }
    for (int i = 0; i < found.size(); i++)
    { 

      Rect aux = found[i];
      int x = (aux.tl().x+aux.br().x)/2;
      int y = (aux.tl().y+aux.br().y)/2;
        //cout << ant_info.at(0) << "x"<<ant_info.at(1)<<endl; 
        //cout << x << "," << y << endl;

      if((x>=0)&&(x<ant_info.at(0))&&(y>=0)&&(y<ant_info.at(1))){
            //std::cout <<"("<<aux.tl().x<<","<<aux.tl().y<<")-("<<aux.br().x<<","<<aux.br().y<<")-("<<x<<","<<y<<")="<<peso[i]<<endl;
        if(imagen[x][y]<peso[i]){
          imagen[x][y]=1-peso[i];
        }
      }
    }
    cout << endl;

    size_t i, j;
    int count = ant_info.at(3);

     /*for( i = 0; i < found.size(); i++ ){
      Rect r = found[i];
      for( j = 0; j < found.size(); j++ )
        if( j != i && (r & found[j]) == r)
          break;
        if( j == found.size() )
          found_filtered.push_back(r); 
      }*/

        //std::cout << "(" << ant_info.at(4) << "," << ant_info.at(5) << ") = " << imagen[ant_info.at(4)][ant_info.at(5)] << std::endl;
   //   int verif = writescore(ant_info,filename, imagen, percent);
        //std::cout << "(" << ant_info.at(4) << "," << ant_info.at(5) << ") = " << imagen[ant_info.at(4)][ant_info.at(5)] << std::endl;
        delete imagen;
        if(argv[4][0]=='y'){
          cout << "Imagen" << endl;
          for( i = 0; i < found.size(); i++ )
          {
            Rect r = found[i];
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.75);
            r.y += cvRound(r.height*0.075);
            r.height = cvRound(r.height*0.7);
            rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 1);
            //Point ce = Point((r.tl().x+r.br().x)/2,(r.tl().y+r.br().y)/2);
            //line( img, ce,ce, Scalar(255, 0, 0), 2,8 );
            
          } 
          //for (i = 0; i < count; i++)
          
         // {
            //cout << ant_info.at(4+2*i) << "-" << ant_info.at(5+2*i);
            //Point ct = Point(ant_info.at(4+2*i),ant_info.at(5+2*i));
            //line( img, ct,ct, Scalar( 0, 0, 255 ), 4,8 );
         // }       

          imshow("people detector", img);
          int c = waitKey(0) & 255;
          if( c == 'q' || c == 'Q' || !f)
            break;
        }
      }

      if(f)
        fclose(f);
      return 0;
    }
/*Imprime la versión de las librerías no standar utilizadas*/
    int printversion(){
      std::cout << "Boost Version "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minior version
          << BOOST_VERSION % 100                // patch level
          << std::endl;

          std::cout << "OpenCV Version "<< CV_VERSION << std::endl; 

        }

/*Eliminar la extensión from StackOverflow*/
        string removeExtension(string filename) {
          size_t lastdot = filename.find_last_of(".");
          if (lastdot == string::npos) return filename;
          return filename.substr(0, lastdot); 
        }   
/*Lee el archivo con anotaciones*/
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
/*obtiene información de la anotaciones*/
        std::vector<int> gtinfo(std::vector<string> ant){
          std::vector<int> info;
          for (int i = 0; i < ant.size(); i++)
          {
           std::vector<string> sp_line; 
           erase_all(ant.at(i)," ");
         //cout << ant.at(i)  << endl;             
           boost::split(sp_line,ant.at(i),boost::is_any_of(":"));
           if(sp_line.at(0)=="Imagesize(XxYxC)"){
             std::vector<string> img_size;
             boost::split(img_size,sp_line.at(1),boost::is_any_of("x"));
             //std::cout << img_size.at(0) << img_size.at(1) << img_size.at(2) << std::endl;
             info += atoi(img_size.at(0).c_str()), atoi(img_size.at(1).c_str()),atoi(img_size.at(2).c_str());  
           }else if(sp_line.at(0)=="Objectswithgroundtruth") {
             std::vector<string> num_obj;
             boost::split(num_obj,sp_line.at(1),boost::is_any_of("{"));
             //std::cout << num_obj.at(0) << std::endl;
             info += atoi(num_obj.at(0).c_str());     
           }else if(sp_line.at(0)[0]=='B') {
             std::vector<string> center;
             boost::split(center,sp_line.at(1),boost::is_any_of("(,)-"));
             int x = atoi(center.at(1).c_str())+atoi(center.at(5).c_str());
             int y = atoi(center.at(2).c_str())+atoi(center.at(6).c_str());
             //std::cout << x/2 <<","<<y/2<< std::endl;
             info += x/2,y/2;
           }

         }
         return info;
       }

       int writescore(std::vector<int> gtitems, char* filename, double** img, int percent){


        int p = percent/2;
        int xbound = (gtitems.at(0)*p)/100;
        int ybound = (gtitems.at(1)*p)/100; 
        std::vector<string> sp_name;
        string f = boost::lexical_cast<string>(filename);
        boost::split(sp_name,f,boost::is_any_of("/"));
        string name = removeExtension(sp_name.at(sp_name.size()-1));

        for(int i=0;i<gtitems.at(3);i++){
          ofstream myfile;
          string file = boost::lexical_cast<string>("out/")+name+boost::lexical_cast<string>("_")+boost::lexical_cast<string>(i+1)+boost::lexical_cast<string>(".mat");
          std::cout << file << std::endl;
          myfile.open (file.c_str());       

          myfile << "# name: MAT\n# type: matrix\n# rows: " << 2*xbound << "\n# columns: " << 2*ybound << "\n";

          for (int x = gtitems.at(4+2*i)-xbound; x < gtitems.at(4+2*i)+xbound; x++){
            for (int y = gtitems.at(5+2*i)-ybound; y < gtitems.at(5+2*i)+ybound; y++){                    
              myfile << " " << setprecision(10) << fixed << img[x][y];
            }
            myfile <<endl;
          }  
          myfile.close();
        }
        return 0;
      }