
# Declaration of variables
CXXFLAGS = -c -std=c++17 -flto -Ofast -fPIC -I . -Wall -Wno-unused-result
LDFLAGS = -shared -flto -Ofast

# File names
HEADERS = $(shell find . -name "*.h")
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

STATIC = libADTF-Streaming.a
DYNAMIC = libADTF-Streaming.so

# Main target
all: $(STATIC) $(DYNAMIC)

# Targets
$(STATIC): $(OBJECTS)
	$(AR) rc $(STATIC) $(OBJECTS)

$(DYNAMIC): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(DYNAMIC)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Format code
format:
	clang-format -style=file -i $(HEADERS) $(SOURCES)

# Clean generated files
clean:
	$(RM) $(STATIC) $(DYNAMIC) $(OBJECTS)
