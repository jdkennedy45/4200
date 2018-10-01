AutomatedMakefile = am
CC = g++ -std=c++11

CSC1310_PATH = $(SOCKET_PATH)/CSC1310
ZIP_PATH = $(COMPILER_PATH)/zlib-1.2.11
ZIPP_PATH = $(SOCKET_PATH)/zip

SRC_DIR=./src
BUILD_DIR=./build
HEADER_DIR=./include

INC_DIRS = -I$(ZIP_PATH) -I$(ZIPP_PATH)/include -I$(CSC1310_PATH)/include -I$(SOCKET_PATH)/sockets/include -I$(COMPILER_PATH)/poco-1.7.6/Net/include -I$(COMPILER_PATH)/poco-1.7.6/Foundation/include -I$(COMPILER_PATH)/poco-1.7.6/Util/include
LIB_DIRS = -L$(ZIP_PATH)/lib -L$(ZIPP_PATH)/lib -L$(CSC1310_PATH) -L$(COMPILER_PATH)/poco-1.7.6/lib/MinGW/i686
LIBS = -lzlib -lzipp -lCSC1310 -lPocoNet -lPocoFoundation -lWS2_32

COMPILE = $(CC) $(INC_DIRS) -Wno-deprecated-declarations -c
LINK=$(CC) $(LIB_DIRS) -o 

SOCKET_FILES =

all: SocketServer SocketClient

SocketServer: 			$(BUILD_DIR)/SocketServer.o $(SOCKET_FILES)
				$(LINK) SocketServer.exe build/SocketServer.o $(SOCKET_FILES) $(LIBS)

SocketClient: 			$(BUILD_DIR)/SocketClient.o $(SOCKET_FILES)
				$(LINK) SocketClient.exe build/SocketClient.o $(SOCKET_FILES) $(LIBS)

$(BUILD_DIR)/SocketClient.o:	$(SRC_DIR)/SocketClient.cpp $(HEADER_DIR)/SocketClient.h
				$(COMPILE) $< -o $@

$(BUILD_DIR)/SocketServer.o:	$(SRC_DIR)/SocketServer.cpp $(HEADER_DIR)/SocketServer.h
				$(COMPILE) $< -o $@


