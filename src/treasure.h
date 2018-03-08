#include "main.h"

#ifndef TREASURE_H
#define TREASURE_H


class Treasure {
public:
    Treasure() {}
    Treasure(float x, float y, float z, float num, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    float omega;
    int treasure_draw ;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif 
