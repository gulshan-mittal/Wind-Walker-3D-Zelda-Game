#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed_x, speed_y, omega, accel_y, accel_x, lev_angle, gravity, speed_z;
    void movement_boat(char type, float angle);
    void flow_motion();
    bounding_box_t bounding_box();

private:
    VAO *object[15];
};

#endif 
