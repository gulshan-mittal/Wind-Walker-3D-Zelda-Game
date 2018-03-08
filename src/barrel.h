#include "main.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, float z, color_t color);
    glm::vec3 position;
    float speed_x;
    float rotation;
    float utility;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();

private:
    VAO *object;
};

#endif
