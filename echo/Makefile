.PHONY: all clean

CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = echo_client
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
