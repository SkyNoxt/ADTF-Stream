
# Declaration of variables
CXXFLAGS = -c -std=c++17 -Wall -Werror
LDFLAGS = -shared

LIBRARY = libADTFStream

ifdef OS
	OBJEX = obj
	STAEX = lib
	DYNEX = dll
	LDFLAGS += -fuse-ld=lld -Wl,-def:ADTFStream.def,$\
		-implib:$(LIBRARY).$(DYNEX).$(STAEX)
else
	OBJEX = o
	STAEX = a
	DYNEX = so
	CXXFLAGS += -fPIC
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
	$(RM) $(LIBRARY)* $(OBJECTS)
