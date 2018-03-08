#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H

class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float speed_x,speed_y,speed_z;
    int val , life, booster_val, booster_time;
    void draw(glm::mat4 VP);
    void tick();
    void rotation_decider(int flag);    
    void set_position(float x, float y, float z);
    bounding_box_t bounding_box();    
private:
    VAO *object[2];         
};

#endif
