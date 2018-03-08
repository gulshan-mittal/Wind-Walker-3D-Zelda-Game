#include "main.h"

#ifndef HEALTH_H
#define HEALTH_H


class Health {

public:
    Health() {}
    Health(float x, float y, float z);
    glm::vec3 position;
    float rotation, speed , life;
    void set_position(float x, float y, float z);
    void draw(glm::mat4 VP);
    void life_show(glm::mat4 VP);
    void tick();
    void life_reduce();
private:
    VAO *life_bar[3];
};
#endif 
