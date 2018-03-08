#include "main.h"
#include "canon.h"

#ifndef AURORA_H
#define AURORA_H


class Aurora {
private:
    VAO *object;

public:
    Canon canball;
    Aurora() {}
    Aurora(float x, float y, float z);
    int flag_shoot;
    glm::vec3 position;
    float rotation_xz, rotation_y;
    double speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void calc_rotation_y(double xpos, double ypos);
    void shoot();
    void tick();
};

#endif 
