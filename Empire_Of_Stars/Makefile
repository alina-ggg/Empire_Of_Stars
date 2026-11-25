CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude
SRC_DIR = src
BUILD_DIR = build
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = empire_of_stars

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
.PHONY: all clean test

test: $(filter-out $(BUILD_DIR)/main.o,$(OBJECTS)) tests/test_logic.cpp
	$(CXX) $(CXXFLAGS) $(filter-out $(BUILD_DIR)/main.o,$(OBJECTS)) tests/test_logic.cpp -o $(BUILD_DIR)/test_logic
	./$(BUILD_DIR)/test_logic
