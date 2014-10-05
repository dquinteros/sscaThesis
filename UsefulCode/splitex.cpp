#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

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

#define ENOUGH 1000

using namespace cv;
using namespace std;
using namespace boost::algorithm;
using namespace boost::assign;
using namespace boost;



int main(int argc, char** argv)
{
    string str1("-*-hello abc-*-ABC-*-aBc goodbye-*-");

    typedef vector< iterator_range<string::iterator> > find_vector_type;
    
    find_vector_type FindVec; // #1: Search for separators
    ifind_all( FindVec, str1, "abc" ); // FindVec == { [abc],[ABC],[aBc] }

    typedef vector< string > split_vector_type;
    
    split_vector_type SplitVec; // #2: Search for tokens
    split( SplitVec, str1, is_any_of("-*"), token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
    
    for(string s : SplitVec) {
      cout << "->" << s << endl;
    }
}