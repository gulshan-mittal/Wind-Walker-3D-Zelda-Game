#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    int val;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed_x, speed_y,speed_z;
    bounding_box_t bounding_box();
    void rotation_decider(int flag);

private:
    VAO *object;
};

#endif 
