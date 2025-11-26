CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
LDFLAGS = -lm
SDL_FLAGS = `pkg-config --cflags --libs sdl2`

TARGET = software_engine

SOURCES = src/main.c \
					src/core/engine.c \
					src/core/memory.c \
					src/utils/vec.c \
					src/utils/float.c \
					src/utils/trig.c \
					src/rendering/mesh.c \
					src/rendering/renderbuffer.c \
					src/rendering/rendercommand.c \

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

release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)

asan: CFLAGS += -g -O1 -fsanitize=address
asan: LDFLAGS += -fsanitize=address
asan: $(TARGET)

deps:
	sudo apt-get install libsdl2-dev
