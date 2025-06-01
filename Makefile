PROJECT = labwork
TESTPROJECT = test-labwork

CXX = g++
CCXFLAGS = -Iinclude -std=c++17 -Werror -Wpedantic -Wall -g -fPIC
LDXXFLAGS = $(CCXFLAGS) -L.
LDGTESTFLAGS = $(LDXXFLAGS) -lgtest -lgmock -lgtest_main -lpthread

SRC_DIR = src/
INC_DIR = include/
TEST_DIR = tests/

SOURCES = $(shell find $(SRC_DIR) -name '*.cpp' ! -name 'main.cpp')
OBJ = $(SOURCES:.cpp=.o)

MAIN_SRC = $(shell find $(SRC_DIR) -name 'main.cpp')
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

TEST_SOURCES = $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJ = $(TEST_SOURCES:.cpp=.o)

.PHONY: default all clean test runtests

default: all

%.o: %.cpp
	$(CXX) $(CCXFLAGS) -c -o $@ $<

$(PROJECT): $(OBJ) $(MAIN_OBJ)
	$(CXX) -o $@ $^ $(LDXXFLAGS)

$(TESTPROJECT): $(OBJ) $(TEST_OBJ)
	$(CXX) -o $@ $^ $(LDGTESTFLAGS)

runtests: $(TESTPROJECT)
	./$(TESTPROJECT)

test: $(TESTPROJECT)

all: $(PROJECT) $(TESTPROJECT)

clean:
	find $(SRC_DIR) -name "*.o" -delete
	find $(TEST_DIR) -name "*.o" -delete
	rm -f $(PROJECT) $(TESTPROJECT)
