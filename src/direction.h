#include "main.h"

#ifndef DIRECTION_H
#define DIRECTION_H


class Direction {
public:
    Direction() {}
    Direction(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z, float rotation);
    float speed_x, speed_z ,omega;
    void tick(float rotation);
    bounding_box_t bounding_box();
    void movement_direction(char type, float angle);
private:
    VAO *object[2];
};

#endif 
