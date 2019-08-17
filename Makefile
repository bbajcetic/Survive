#OBJS specifies files to compile
OBJS = Survive.cpp

#CC specifies compiler
CC = g++

#OBJ_NAME specifies object file name
OBJ_NAME = Survive

#specifies compilation flags
COMPILER_FLAGS = -w

#specifies the libraries to link against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#target
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
