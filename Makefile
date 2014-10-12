# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -std=c++11 -ggdb `pkg-config --cflags opencv`
CVFLAGS = `pkg-config --libs opencv`

# the build target executable:
TARGET = main

all:  $(TARGET)

$(TARGET):  $(TARGET).cc
	$(CC) $(CFLAGS) -o $(TARGET) *.cc $(CVFLAGS)


people: peopledetect.cpp
	$(CC) $(CFLAGS) -o peopledetect peopledetect.cpp $(CVFLAGS)

clean:
	$(RM) $(TARGET)