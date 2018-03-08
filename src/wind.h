#include "main.h"

#ifndef WIND_H
#define WIND_H


class Wind {
public:
    Wind() {}
    Wind(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    int occur;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    float accel_x,accel_y, speed_x,speed_y;
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif 
