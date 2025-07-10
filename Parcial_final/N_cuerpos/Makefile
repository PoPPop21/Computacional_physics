CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -I/usr/include/eigen3
SRC = $(wildcard src/*.cpp)
BIN = bin/electricidad

all: $(BIN)

$(BIN): bin $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

bin:
	mkdir -p bin

run: all
	./$(BIN)

clean:
	rm -f $(BIN)
	rm -f results/*.dat
