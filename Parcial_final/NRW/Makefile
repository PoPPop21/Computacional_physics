
---
# Makefile para el proyecto NRW
```makefile
# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = bin/nrrw
DOXYFILE = Doxyfile

# Default
all: $(BIN)

# Compilar ejecutable
$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@

# Objetos
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar
clean:
	rm -f src/*.o $(BIN)

# Documentación
doc:
	doxygen $(DOXYFILE)

# Empaquetar
package:
	tar -czvf proyecto_nrrw.tar.gz src/ include/ bin/ results/ scripts/ documents/ Makefile README.md

.PHONY: all clean doc package
