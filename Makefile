CXX = gcc
# CXXFLAGS = 
TARGET = a.out # modify at will
SRCS = ./src/main.c ./src/parse_info.c ./src/compress.c ./src/write_output.c -lm

all: $(TARGET)

# Linking
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET)

clean: 
	rm -f $(TARGET)