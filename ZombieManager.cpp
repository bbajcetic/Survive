#include "ZombieManager.h"

ZombieManager::ZombieManager(int wave) {
    float multiplier = pow( ZOMBIE_MULTIPLIER, float(wave-1) );
    this->num_zombies = int( float(WAVE1_ZOMBIES) * multiplier );
    this->num_spawned = 0;
    this->num_dead = 0;
    this->last_spawn = 0;
}
ZombieManager::~ZombieManager() {
    std::vector<Zombie*>::iterator z_it = zombies.begin();
    while (z_it != zombies.end()) {
        printf("clearing zombie\n");
        delete *z_it;
        z_it = zombies.erase(z_it);
    }
}
void ZombieManager::reset(int wave) {
    destroyZombies();
    float multiplier = pow( ZOMBIE_MULTIPLIER, float(wave-1) );
    this->num_zombies = int( float(WAVE1_ZOMBIES) * multiplier );
    this->num_spawned = 0;
    this->num_dead = 0;
    this->last_spawn = 0;
}
void ZombieManager::destroyZombies() {
    std::vector<Zombie*>::iterator z_it = zombies.begin();
    while (z_it != zombies.end()) {
        printf("clearing zombie\n");
        delete *z_it;
        z_it = zombies.erase(z_it);
    }
}
void ZombieManager::update(int current_time) {
    std::vector<Zombie*>::iterator z_it = zombies.begin();
    while (z_it != zombies.end()) {
        (*z_it)->update(current_time);
        z_it++;
    }
    //check for next spawn
    if ( (current_time - last_spawn) >= ZOMBIE_SPAWN_TIME ) {
        if (num_spawned < num_zombies) {
            /* spawn zombie */
            //randomize location and speed
            int speed = ( rand() % (ZOMBIE_MAX_SPEED+1-ZOMBIE_MIN_SPEED) ) + ZOMBIE_MIN_SPEED;
            int spawn_y = ( rand() % GAME_HEIGHT );
            int spawn_x = -48;
            Zombie* temp = new Zombie(spawn_x, spawn_y, 0, speed);
            temp->load("ZombieRight.png", 1, 4);
            zombies.push_back(temp);
            num_spawned++;
            printf("New zombie spawned\n");
        }
        last_spawn = current_time;
    }
}
void ZombieManager::render() {
    std::vector<Zombie*>::iterator z_it = zombies.begin();
    while (z_it != zombies.end()) {
        (*z_it)->draw();
        z_it++;
    }
}
