
# Declaration of variables
CXXFLAGS = -c -std=c++17 -Wall -Werror
LDFLAGS = -shared

LIBRARY = libADTFStream

ifdef OS
	CXXFLAGS += -Wno-deprecated-declarations
	LDFLAGS += -fuse-ld=lld
	STAEX = lib
	DYNEX = dll
	OBJEX = obj
else
	CXXFLAGS += -fPIC -Wno-unused-result
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

# Targets

all: release

debug: CXXFLAGS += -g
debug: $(STATIC) $(DYNAMIC)

release: CXXFLAGS += -Ofast -flto
release: LDFLAGS += -Ofast
release: $(STATIC) $(DYNAMIC)

# Link main targets
$(STATIC): $(OBJECTS)
	$(AR) rcs $@ $^

$(DYNAMIC): $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

# Compile source files
%.$(OBJEX): %.cpp %.h Makefile
	$(CXX) $(CXXFLAGS) $< -o $@

# Format code
format:
	clang-format -style=file -i $(HEADERS) $(SOURCES)

# Clean generated files
clean:
	$(RM) $(STATIC) $(DYNAMIC) $(OBJECTS)
