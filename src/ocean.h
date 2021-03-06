#include "main.h"

#ifndef OCEAN_H
#define OCEAN_H


class Ocean {
public:
    Ocean() {}
    Ocean(float x, float y, float z, color_t color , double rad);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed ,rad;
private:
    VAO *object;
};

#endif 
