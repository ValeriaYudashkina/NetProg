.PHONY: all clean

CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = echo_client
TARGET_SERVER = echo_server
SRC = main.cpp
SRC_SERVER = tcp_server.cpp

all: $(TARGET) $(TARGET_SERVER)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

$(TARGET_SERVER): $(SRC_SERVER)
	$(CXX) $(CXXFLAGS) -o $(TARGET_SERVER) $(SRC_SERVER)

clean:
	rm -f $(TARGET) $(TARGET_SERVER) *.o
