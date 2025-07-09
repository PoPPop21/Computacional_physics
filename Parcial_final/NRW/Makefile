CXX = g++
CXXFLAGS = -Wall -Iinclude -std=c++11
LDFLAGS = 
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = bin/NRRW

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f src/*.o bin/NRRW results/*.csv results/*.png
