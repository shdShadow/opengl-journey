CC = clang++
CFLAGS = -Wall -Wextra -std=c++17
INCLUDE = -I./Libraries/include/
SOURCES = main.cpp glad.c
OUTPUT = main
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
all: $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(OUTPUT) $(LIBS)
clean:
	rm -f $(OUTPUT)
