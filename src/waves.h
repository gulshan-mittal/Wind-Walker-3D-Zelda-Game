#include "main.h"

#ifndef WAVES_H
#define WAVES_H


class Waves {
public:
    Waves() {}
    Waves(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float speed_x, speed_y, accel_x, accel_y;
    void tick();
    void set_position(float x, float y, float z);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif 
