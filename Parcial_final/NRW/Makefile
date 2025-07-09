# Compilador y banderas
CXX = g++
CXXFLAGS = -Wall -Iinclude -std=c++11

# Archivos fuente y objetos
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, src/%.o, $(SRC))

# Ejecutable
BIN = bin/NRRW

# Regla principal
all: $(BIN)

# Regla para compilar el ejecutable
$(BIN): $(OBJ) | bin
	$(CXX) $(CXXFLAGS) -o $@ $^

# Crear carpeta bin si no existe
bin:
	mkdir -p bin

# Regla para limpiar archivos temporales
clean:
	rm -f src/*.o $(BIN) results/*.csv results/*.png
