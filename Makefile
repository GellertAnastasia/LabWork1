PROJECT = labwork

LIBPROJECT = $(PROJECT).a

TESTPROJECT = test-$(PROJECT)

CXX = g++

A = ar

AFLAGS = rsv

CCXFLAGS = -I. -std=c++17 -Wall -g -fPIC

LDXXFLAGS = $(CCXFLAGS) -L. -l:$(LIBPROJECT)

DEPS=$(wildcard *.h)

SOURCES = main.cpp rotate.cpp filter.cpp

OBJ = $(SOURCES:.cpp=.o)


.PHONY: default

default: all;

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(LIBPROJECT): $(OBJ) 
	$(A) $(AFLAGS) $@ $^

$(PROJECT): main.o $(LIBPROJECT)
	$(CXX) -o $@ main.o $(LDXXFLAGS)

all: $(PROJECT)

.PHONY: clean

clean:
	rm -f *.o
	rm -f $(PROJECT) 
	rm -f $(LIBPROJECT)
