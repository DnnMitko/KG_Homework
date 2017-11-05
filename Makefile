#https://stackoverflow.com/questions/20308661/linking-sdl-image-in-make-file
OBJS = src/main.cpp src/Homework.cpp pugixml/pugixml.cpp

CC = g++

LIBS = -L/usr/include/SDL2/SDL_image -L/usr/include/SDL2/SDL_ttf

# COMPILER_FLAGS = -w 

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = run

all : $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)