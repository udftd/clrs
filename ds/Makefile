CC=g++
CXXFLAGS=-O0 -g -Wall -o 
TARGET=test
SOURCES=main.cpp
LIBS=-std=c++14 

build: clean all

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CXXFLAGS) $(TARGET) $(SOURCES) $(LIBS)

clean:
	$(RM) $(TARGET)
