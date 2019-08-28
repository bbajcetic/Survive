#OBJS specifies files to compile
OBJS = Survive.o Survivor.o ObjTexture.o Map.o Projectile.o Zombie.o Collision.o Vec2D.o

#CC specifies compiler
CC = g++

#OBJ_NAME specifies object file name
OBJ_NAME = Survive.out

#specifies compilation flags
COMPILER_FLAGS = -w -g

#specifies the libraries to link against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#target
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

Survive.o: ObjTexture.h Survivor.h Zombie.h Map.h Projectile.h Collision.h Vec2D.h Constants.h

ObjTexture.o: ObjTexture.h Constants.h

Survivor.o: Survivor.h Constants.h

Zombie.o: Zombie.h Constants.h

Map.o: Map.h Constants.h

Projectile.o: Projectile.h Constants.h

Collision.o: Collision.h Constants.h

Vec2D.o: Vec2D.h Constants.h
