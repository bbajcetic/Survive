#ifndef ZOMBIEMANAGER_H
#define ZOMBIEMANAGER_H

#include "Zombie.h"
#include "Constants.h"

class ZombieManager {
    public:
        std::vector<Zombie*> zombies;

        ZombieManager(int wave);
        ~ZombieManager();
        void reset(int wave);
        void destroyZombies();
        void update(int current_time);
        void render();

        void zombieDead() { num_dead++; }
        int getSize() { return zombies.size(); }
        int getNumZombies() { return num_zombies; }
        int getNumSpawned() { return num_spawned; }
        int getNumDead() { return num_dead; }

        void setLastSpawn(int time) { last_spawn = time; }

    private:
        int num_zombies;
        int num_spawned;
        int num_dead;
        int last_spawn;
};

#endif
