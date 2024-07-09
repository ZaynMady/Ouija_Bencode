# Variables
OBJ_DIR := build
SRC_DIR := src
TARGET := ouija

# Compiler options
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I"D:/vcpkg/installed/x64-windows/include" -Wall -Wextra -g
LDFLAGS = -L"D:/vcpkg/installed/x64-windows/lib"
LDLIBS = -lssl -lcrypto -static-libgcc -static-libstdc++ -llibssl -llibcrypto

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target rules
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean restart

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

restart:
	rm -rf difference.txt Assets/film.torrent