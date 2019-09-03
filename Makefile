#OBJS specifies files to compile
OBJS = Survive.o Survivor.o ObjTexture.o Map.o Projectile.o Zombie.o ZombieManager.o Collision.o Container.o CustomRender.o Vec2D.o CustomMath.o

#CC specifies compiler
CC = g++

#OBJ_NAME specifies object file name
OBJ_NAME = Survive.out

#specifies compilation flags
COMPILER_FLAGS = -w -g

#specifies the libraries to link against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#target
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

Survive.o: ObjTexture.h Survivor.h Zombie.h ZombieManager.h Map.h Projectile.h Collision.h Container.h CustomRender.h Vec2D.h Constants.h CustomMath.h

ObjTexture.o: ObjTexture.h Constants.h

Survivor.o: Survivor.h Constants.h

Zombie.o: Zombie.h Constants.h

ZombieManager.o: ZombieManager.h Constants.h

Map.o: Map.h Constants.h

Projectile.o: Projectile.h Constants.h

Collision.o: Collision.h Constants.h

Container.o: Container.h Constants.h

CustomRender.o: CustomRender.h Constants.h

Vec2D.o: Vec2D.h Constants.h

CustomMath.o: CustomMath.h Constants.h
