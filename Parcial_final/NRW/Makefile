# Compilador y banderas
CXX = g++
CXXFLAGS = -Wall -Iinclude -std=c++11

# Archivos
OBJS = src/NRRW.o
MAIN1 = src/main.o
MAIN2 = src/main_trayectoria.o

# Ejecutables
BIN_DIR = bin
BIN1 = $(BIN_DIR)/NRRW
BIN2 = $(BIN_DIR)/NRRW_tray

# Carpetas
RESULTS_DIR = results
SCRIPTS_DIR = scripts

# Regla por defecto: compila todo
all: $(BIN1) $(BIN2)

# Regla principal
$(BIN1): $(OBJS) $(MAIN1) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Ejecutable de trayectoria
$(BIN2): $(OBJS) $(MAIN2) | $(BIN_DIR) $(RESULTS_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Crear carpeta bin/
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Crear carpeta results/
$(RESULTS_DIR):
	mkdir -p $(RESULTS_DIR)

# Ejecutar caminata y graficar
tray: $(BIN2)
	./$(BIN2)
	python3 $(SCRIPTS_DIR)/plot_trayectoria.py

# Ejecutar todo: compilar y graficar
run: all tray

# Limpiar archivos
clean:
	rm -f src/*.o $(BIN_DIR)/* $(RESULTS_DIR)/*.csv $(RESULTS_DIR)/*.png
