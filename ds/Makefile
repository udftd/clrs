CC=g++
CXXFLAGS=-Wall -o
TARGET=test
SOURCES=main.cpp
LIBS=-std=c++14 
LD=-O0 -g 

build: clean all

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CXXFLAGS) $(TARGET) $(SOURCES) $(LIBS) $(LD)

clean:
	$(RM) $(TARGET)
