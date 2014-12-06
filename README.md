sscaThesis
==========

spatial sensitivity comparative analysis for pedestrian detection

Requirements
============

The code was been tested for 

- C++11 (g++ 4.8+)
- OpenCV 2.4.9
- Boost 1.54
- Linux mint 17 / Ubuntu 14.04


Usage
====

To compile use the make command

To get help
```bash
./main.o --help 
```
To run 
```bash
./main.o -p <Positive trainnig lists of files> -n <Negative trainnig lists of files> -t <Negative trainnig lists of files>  -c <Select Clasifier, svm & boost are supported>
```
