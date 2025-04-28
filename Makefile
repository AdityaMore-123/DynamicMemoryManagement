CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++11
SRC = src/main.cpp src/MemoryManager.cpp src/Block.cpp
OUT = build/DynamicMemoryManagement

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	rm -rf build/*
