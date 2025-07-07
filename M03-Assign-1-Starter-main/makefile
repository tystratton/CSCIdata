CXX=g++
CXXFLAGS=-std=c++11 -Wall
#The name of your excecutable
TARGET=main

#all of the .cpp files with a .o extension
OBJECTS=main.o url.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

#how to build a .o from a .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECTS)

url: url.h url.cpp
	g++ -pedantic-errors -g -c url.cpp -o url
	