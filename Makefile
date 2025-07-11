CXX = g++
# CXXFLAGS = 
TARGET = a.out # modify at will
SRCS = main.c parse_info.c compress.c write_output.c

all: $(TARGET)

# Linking
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET)

clean: 
	rm -f $(TARGET)