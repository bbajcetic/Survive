#include "Zombie.h"

Zombie::Zombie(int x, int y, int angle) {
    printf("---Entering Zombie constructor\n");
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
    printf("---Leaving Zombie constructor\n");
}
Zombie::~Zombie() {
    printf("---Entering Zombie destructor\n");
    delete objTexture;
    objTexture = NULL;
    printf("---Leaving Zombie destructor\n");
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
    if (temp % MAP1_TILE_COLS == 0) {
        /* invalidate tiles to the left */
        around[0] = -1; around[6] = -1; around[7] = -1;
    }
    /* if zombie is on right side tiles, make sure it doesn't wrap around */
    else if ( (temp+1) % MAP1_TILE_COLS == 0 ) {
        /* invalidate tiles to the right */
        around[2] = -1; around[3] = -1; around[4] = -1;
    }

    std::vector<int> min_vals;
    int min = std::numeric_limits<int>::max();
    for (int i = 0; i < 8; ++i) {
        if (around[i] >= MAP1_TILE_ROWS * MAP1_TILE_COLS) {
            continue;
        }
        if (around[i] < 0) {
            continue;
        }
        int curr_val = map.getPathValue(around[i]);
        if (curr_val < 0) {
            continue;
        }
        else if (curr_val <= min) {
            min = curr_val;
        }
    }
    printf("min = %d\n", min);
    for (int i = 0; i < 8; ++i) {
        if (around[i] >= MAP1_TILE_ROWS * MAP1_TILE_COLS || around[i] < 0) {
            continue;
        }
        int curr_val = map.getPathValue(around[i]);
        if (curr_val == min) {
            min_vals.push_back(around[i]);
        }
    }
    //pick random index from min_vals[0] to min_vals[size]-1
    int rand_pick = 0;
    int next_index = min_vals[rand_pick];
    printf("Next index = %d\n", next_index);
    next_x = map.getXFromIndex(next_index);
    next_y = map.getYFromIndex(next_index);
    int diff_x = next_x - x;
    int diff_y = next_y - y;
    printf("DIFFX = %d, DIFFY = %d\n", diff_x, diff_y);
    printf("NEXTX = %f, NEXTY = %f\n", next_x, next_y);
    float rad;
    if (diff_x == 0) {
        rad = (diff_y >= 0) ? PI/2.0 : 3*PI/2.0;
    }
    else {
        rad = atan( float(diff_y)/float(diff_x) );
        if (diff_x >= 0 and diff_y < 0) {
            rad = rad + 2.0*PI;
        }
        else if (diff_x < 0) {
            rad = rad + PI;
        }
    }
    next_angle = int( rad * float(180) / PI );
    printf("Next angle float = %f\n", next_angle);
}

void Zombie::turn() {
    int to_angle = next_angle - angle;
    if ( abs(to_angle) < ZOMBIE_SENSITIVITY ) {
        angle = next_angle;
    }
    else {
        angle = (to_angle > 0) ? angle + ZOMBIE_SENSITIVITY : angle - ZOMBIE_SENSITIVITY;
    }
    printf("NEWANGLE = %d\n", angle);
    //else if (to_angle > 0) {
    //    angle = angle + ZOMBIE_SENSITIVITY;
    //}
    //else if (to_angle < 0) {
    //    angle = angle - ZOMBIE_SENSITIVITY;
    //}
}
void Zombie::update() {
    printf("---Entering Zombie::update\n");
    if (x == next_x && y == next_y) {
        updateNext();
    }
    if (angle != next_angle) {
        turn();
    }
    else if (x != next_x || y != next_y) {
        move();
    }
}

void Zombie::move() {
    float distance_sq = pow(abs(next_x - x), 2.0) + pow(abs(next_y - y), 2.0);
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
        //x = ( (next_x - x) >= 0 )? x + move_x : x - move_x;
        //y = ( (next_y - y) >= 0 )? y + move_y : y - move_y;
        //if ( (next_x - x) > 0 ) {
        //    x = x + move_x;
        //} else {
        //    x = x - move_x;
        //}
        //if ( (next_y - y) > 0) {
        //    y = y + move_y;
        //} else {
        //    y = y - move_y;
        //}
    }
}

void Zombie::draw(int anim_index) {
    printf("---Entering Zombie::draw\n");
    objTexture->render(x, y, angle, width, height, anim_index);
    //objTexture.render(x, y, angle, width, height, 0);
    printf("---Leaving Zombie::draw\n");
}
void Zombie::load(std::string path, int anim_rows, int anim_cols) {
    printf("---Entering Zombie::load\n");
    //if (objTexture != NULL) {
    //    delete objTexture;
    //}
    //objTexture = new ObjTexture();
    objTexture->load(path, anim_rows, anim_cols);
    //objTexture.load(path, 1, 1);
    printf("---Leaving Zombie::load\n");
}
