CXX = g++
CXXFLAGS = -Wall -std=c++20 -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/calc-cli

INSTALL_DIR = $(HOME)/.local/bin
INSTALL_NAME = calc-cli

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

install: $(TARGET)
	@mkdir -p $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)/$(INSTALL_NAME)
	@echo "Installed on $(INSTALL_DIR)/$(INSTALL_NAME)"

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean install
