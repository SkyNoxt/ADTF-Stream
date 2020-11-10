
# Declaration of variables
CXXFLAGS = -c -std=c++17 -Ofast -I . -Wall
LDFLAGS = -shared -Ofast
LIBRARY = libADTFStream

ifdef OS
	CXXFLAGS += -Wno-deprecated-declarations
	STAEX = lib
	DYNEX = dll
	OBJEX = obj
else
	CXXFLAGS += -flto -fPIC -Wno-unused-result
	LDFLAGS += -flto
	STAEX = a
	DYNEX = so
	OBJEX = o
endif

# File names
HEADERS = $(shell find . -name "*.h")
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.$(OBJEX))

STATIC = $(LIBRARY).$(STAEX)
DYNAMIC = $(LIBRARY).$(DYNEX)

# Main target
all: $(STATIC) $(DYNAMIC)

# Targets
$(STATIC): $(OBJECTS)
	$(AR) rc $@ $^

$(DYNAMIC): $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

# Compile source files
%.$(OBJEX): %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Format code
format:
	clang-format -style=file -i $(HEADERS) $(SOURCES)

# Clean generated files
clean:
	$(RM) $(STATIC) $(DYNAMIC) $(OBJECTS)
