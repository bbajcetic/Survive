#OBJS specifies files to compile
OBJS = Survive.o Survivor.o ObjTexture.o Map.o

#CC specifies compiler
CC = g++

#OBJ_NAME specifies object file name
OBJ_NAME = Survive.out

#specifies compilation flags
COMPILER_FLAGS = -w

#specifies the libraries to link against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#target
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

Survive.o: ObjTexture.h Survivor.h Constants.h

ObjTexture.o: ObjTexture.h Constants.h

Survivor.o: Survivor.h Constants.h

Map.o: Map.h Constants.h
