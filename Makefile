CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O3
LDFLAGS = -lm
SDL_FLAGS = `pkg-config --cflags --libs sdl2`

TARGET = bin/main

SOURCES = src/main.c \
					src/core/engine.c \
					src/core/memory.c \
					src/utils/vec.c \
					src/utils/color.c \
					src/utils/mat.c \
					src/utils/vertex.c \
					src/rendering/mesh.c \
					src/rendering/cube.c \
					src/rendering/rendertarget.c \
					src/rendering/colorbuffer.c \
					src/rendering/viewport.c \
					src/rendering/rendercommand.c \
					src/rendering/rendering.c \

HEADERS = $(SOURCES:.c=.h)
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(SDL_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(SDL_FLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug: CFLAGS += -g -O0 -DDEBUG
debug: $(TARGET)

release: CFLAGS += -DNDEBUG
release: $(TARGET)

asan: CFLAGS += -g -O1 -fsanitize=address
asan: LDFLAGS += -fsanitize=address
asan: $(TARGET)

loc:
	@echo "Counting Total Lines of Code (.c and .h files)..."
	@wc -l $(SOURCES) $(HEADERS) | grep "total"

deps:
	sudo apt-get install libsdl2-dev
