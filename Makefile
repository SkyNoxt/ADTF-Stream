
# Declaration of variables
CC = g++

CC_FLAGS = -std=c++17 -flto -Ofast -I . -Wall -Wno-unused-result
LD_FLAGS = -flto -Ofast -lpthread

# File names
TARGET = ADTF-Streaming.so
HEADERS = $(shell find . -name "*.h")
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

# Main target linking
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LD_FLAGS) -o $(TARGET)

# Compile source files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# Format code
format:
	clang-format -style=file -i $(HEADERS) $(SOURCES)

# Clean generated files
clean:
	rm -f $(TARGET) $(OBJECTS)
