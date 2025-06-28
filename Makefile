CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -I/usr/include/eigen3
SRC = $(wildcard src/*.cpp)
BIN = bin/gravedad

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	./$(BIN)

clean:
	rm -f $(BIN)
	rm -f results/*.dat
