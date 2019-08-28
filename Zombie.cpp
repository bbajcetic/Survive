#include "Zombie.h"

Zombie::Zombie(int x, int y, int angle) {
    //printf("---Entering Zombie constructor\n");
    //objTexture = NULL;
    this->objTexture = new ObjTexture();
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->next_x = x;
    this->next_y = y;
    this->next_angle = angle;
    this->moving = false;
    this->speed = ZOMBIE_STARTING_SPEED;
    this->width = ZOMBIE_WIDTH;
    this->height = ZOMBIE_HEIGHT;
    this->health = ZOMBIE_STARTING_HEALTH;
    this->frame = 0;
    this->last_move = 0;
    //printf("---Leaving Zombie constructor\n");
}
Zombie::~Zombie() {
    //printf("---Entering Zombie destructor\n");
    delete objTexture;
    objTexture = NULL;
    //printf("---Leaving Zombie destructor\n");
}
/* returns true if Zombie is still alive */
bool Zombie::takeDamage(int damage) {
    health -= damage;
    printf("Zombie health = %d\n", health);
    if (health <= 0) {
        return false;
    }
    return true;
}
void Zombie::update(int current_time) {
    //printf("---Entering Zombie::update\n");
    if (current_time - last_move < ZOMBIE_TIME_PER_MOVE) {
        return;
    }
    if (x == next_x && y == next_y) {
        updateNext();
    }
    if (angle != next_angle) {
        turn();
    }
    else if (x != next_x || y != next_y) {
        move();
    }
    last_move = current_time;
    frame = (frame + 1) % (ZOMBIE_NUM_SPRITES*ZOMBIE_FRAMES_PER_ANIMATION);
    //printf("---Leaving Zombie::update\n");
}
void Zombie::turn() {
    int to_angle = next_angle - angle;
    if ( abs(to_angle) < ZOMBIE_SENSITIVITY ) {
        angle = next_angle;
    }
    else if ( abs(to_angle) > 180 ) {
        if (to_angle > 180) {
            angle = angle - ZOMBIE_SENSITIVITY;
            if (angle < 0) {
                angle += 360;
            }
        }
        else if (to_angle < -180) {
            angle = (angle + ZOMBIE_SENSITIVITY);
            if (angle > 360) {
                angle -= 360;
            }
        }
    }
    else {
        angle = (to_angle > 0) ? angle + ZOMBIE_SENSITIVITY : angle - ZOMBIE_SENSITIVITY;
    }
}
void Zombie::updateNext() {
    //updates next_x and next_y and next_angle to the next tile
    int temp = map.getTileIndex(getX(), getY());
    int top = temp - MAP1_TILE_COLS;
    int bottom = temp + MAP1_TILE_COLS;

    int val = map.getPathValue(temp);

    int around[8] = {
        top-1, top, top+1, temp+1, bottom+1, bottom, bottom-1, temp-1
    };
    /* if zombie is on left side tiles, make sure it doesn't wrap around */
    if (map.isLeftEdge(temp)) {
        /* invalidate tiles to the left */
        around[0] = -1; around[6] = -1; around[7] = -1;
    }
    /* if zombie is on right side tiles, make sure it doesn't wrap around */
    else if (map.isRightEdge(temp)) {
        /* invalidate tiles to the right */
        around[2] = -1; around[3] = -1; around[4] = -1;
    }

    int min = std::numeric_limits<int>::max();
    std::vector<int> min_vals;
    for (int i = 0; i < 8; ++i) {
        if (!map.onMap(around[i])) {
            continue;
        }
        int curr_val = map.getPathValue(around[i]);
        /* if wall or unfilled, skip tile */
        if (curr_val < 0) {
            continue;
        }
        /* check corner piece to prevent cutting corners */
        if (i%2 == 0) {
            int side1, side2;
            if (i == 0) { side1 = around[7]; }
            else { side1 = around[i-1]; }
            side2 = around[(i+1)%8];
            if (map.getPathValue(side1) < 0 || map.getPathValue(side2) < 0) {
                around[i] = -1;
                continue;
            }
        }
        /* go to decreasing tile */
        else if (curr_val <= min) {
            min = curr_val;
        }
    }
    for (int i = 0; i < 8; ++i) {
        if (!map.onMap(around[i])) {
            continue;
        }
        int curr_val = map.getPathValue(around[i]);
        /* put all min values in vector */
        if (curr_val == min) {
            min_vals.push_back(around[i]);
        }
    }
    //pick random index from min_vals[0] to min_vals[size]-1
    /* choose random square from min_vals to go to */
    int rand_pick = rand() % min_vals.size();
    int next_index = min_vals[rand_pick];
    /* get coordinates of next tile and calculate diff from current tile */
    next_x = map.getXFromIndex(next_index);
    next_y = map.getYFromIndex(next_index);
    int diff_x = next_x - x;
    int diff_y = next_y - y;

    /* calculate next_angle */
    float rad;
    rad = findAngle(float(diff_x), float(diff_y));
    //if (diff_x == 0) {
    //    rad = (diff_y >= 0) ? PI/2.0 : 3*PI/2.0;
    //}
    //else {
    //    rad = atan( float(diff_y)/float(diff_x) );
    //    if (diff_x >= 0 and diff_y < 0) {
    //        rad = rad + 2.0*PI;
    //    }
    //    else if (diff_x < 0) {
    //        rad = rad + PI;
    //    }
    //}
    next_angle = int( rad * float(180) / PI );
}

void Zombie::move() {
    float distance_sq = pow(next_x - x, 2.0) + pow(next_y - y, 2.0);
    float distance = sqrt(distance_sq);
    if (distance < speed) {
        x = next_x;
        y = next_y;
    }
    else {
        float rad = float(angle) * (PI/float(180));
        float move_x = float(speed) * cos(float(rad));
        float move_y = float(speed) * sin(float(rad));
        x = x + move_x;
        y = y + move_y;
    }
}

void Zombie::draw() {
    //printf("---Entering Zombie::draw\n");
    int anim_index = frame/ZOMBIE_FRAMES_PER_ANIMATION;
    objTexture->render(x, y, angle, width, height, anim_index);
    //printf("---Leaving Zombie::draw\n");
}
void Zombie::load(std::string path, int anim_rows, int anim_cols) {
    //printf("---Entering Zombie::load\n");
    //if (objTexture != NULL) {
    //    delete objTexture;
    //}
    //objTexture = new ObjTexture();
    objTexture->load(path, anim_rows, anim_cols);
    //objTexture.load(path, 1, 1);
    //printf("---Leaving Zombie::load\n");
}
