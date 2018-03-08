#include "main.h"

#ifndef CANON_H
#define CANON_H


class Canon {
public:
    Canon() {}
    Canon(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float xx, float yy, float zz);
    float params[6];
    float speed_x, speed_y, accel_v,accel_h, angle;
    int release;
    void tick_aurora();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif 
