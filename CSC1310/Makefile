AutomatedMakefile = am
CC = g++ -std=c++11

CSC1310_PATH = $(GAME_PATH)/CSC1310
RANDOM_PATH = $(GAME_PATH)/random

SRC_DIR=./src
BUILD_DIR=./build
HEADER_DIR=./include

INC_DIRS = -I$(CSC1310_PATH)/include -I$(RANDOM_PATH)
LIB_DIRS = -L$(RANDOM_PATH)
LIBS = -lrandom

COMPILE = $(CC) $(INC_DIRS) -Wno-deprecated-declarations -c
LINK = $(CC) -o

CSC1310_FILES = build/Tokens.o build/Integer.o build/Double.o build/Keyboard.o build/Matrix.o build/Permutation.o build/Poly.o build/ReadFile.o build/WriteFile.o build/String.o build/HighPerformanceCounter.o

all: CSC1310_LIB

CSC1310_LIB: 					$(CSC1310_FILES)

$(BUILD_DIR)/String.o:				$(SRC_DIR)/String.cpp $(HEADER_DIR)/String_.h
						$(COMPILE) $< -o $@

$(BUILD_DIR)/%.o:				$(SRC_DIR)/%.cpp $(HEADER_DIR)/%.h
						$(COMPILE) $< -o $@

