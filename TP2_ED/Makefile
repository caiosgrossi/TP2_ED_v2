# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Nome do executável
EXEC = tp2.out

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Lista de arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regras
all: $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

run: $(BIN_DIR)/$(EXEC)
	./$(BIN_DIR)/$(EXEC) < tests.txt

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean run
