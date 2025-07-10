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

.PHONY: all clean run plot docs

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
	mkdir -p $(RESULTS_DIR)
	mkdir -p $(DOCS_DIR)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
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
	rm -rf $(RESULTS_DIR)/*
	rm -rf html latex # Doxygen generated docs