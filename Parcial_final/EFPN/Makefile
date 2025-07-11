CXX = g++
CXXFLAGS = -Wall -I./include -std=c++11
LDFLAGS =

BIN_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
RESULTS_DIR = results
SCRIPTS_DIR = scripts
DOCS_DIR = documents

TARGET = $(BIN_DIR)/montecarlo_sim

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/SistemaDosNiveles.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean run plot docs clean_results

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR) $(RESULTS_DIR) # Ensure RESULTS_DIR is created before linking
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(RESULTS_DIR): # Explicit target for results directory
	mkdir -p $(RESULTS_DIR)
	# Optionally, set permissions to ensure writability, e.g., chmod 775 $(RESULTS_DIR)
	# This might be needed if default permissions are too restrictive.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET) $(RESULTS_DIR) # Ensure results directory exists before running
	./$(TARGET)

plot:
	python3 $(SCRIPTS_DIR)/plot_results.py

docs:
	# Add Doxygen and LaTeX commands here
	# doxygen Doxyfile
	# pdflatex $(DOCS_DIR)/montecarlo.tex

clean:
	rm -f $(OBJS)
	rm -f $(BIN_DIR)/*

clean_results: # New target to clean only results files
	rm -f $(RESULTS_DIR)/*.dat
	rm -f $(RESULTS_DIR)/*.png

