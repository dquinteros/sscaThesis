# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -O4 -std=c++11 -ggdb `pkg-config --cflags opencv`
CVFLAGS = `pkg-config --libs opencv`

# the build target executable:
TARGET = main

all:  $(TARGET)

$(TARGET):  ccsrc/$(TARGET).cc
	$(CC) $(CFLAGS) -o $(TARGET).o ccsrc/*.cc $(CVFLAGS)

hogtest:  tools/hogTest.cc
	$(CC) $(CFLAGS) -o hogTest.o tools/hogTest.cc $(CVFLAGS)

people: peopledetect.cpp
	$(CC) $(CFLAGS) -o peopledetect.o peopledetect.cpp $(CVFLAGS)

clean:
	$(RM) *.o