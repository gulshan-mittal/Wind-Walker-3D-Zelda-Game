#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->val = 1;
    this->speed_x= 1.5;
    this->speed_y= 0;
    this->speed_z= 0;
    int rnd_rot = rand()%2 + 1; 
    this->rotation_decider(rnd_rot);
    int pts = 0;
    static GLfloat vertex_buffer_data[56];

    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = -4.0f, *(vertex_buffer_data+(pts++)) = -4.0f;
    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = -4.0f, *(vertex_buffer_data+(pts++)) = 4.0f;
    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = 4.0f, *(vertex_buffer_data+(pts++)) = 4.0f;

    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = 4.0f, *(vertex_buffer_data+(pts++)) = 4.0f;
    *(vertex_buffer_data+(pts++)) = -4.0f, *(vertex_buffer_data+(pts++)) = -4.0f, *(vertex_buffer_data+(pts++)) = -4.0f;
    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = 4.0f, *(vertex_buffer_data+(pts++)) = -4.0f;


    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = -4.0f, *(vertex_buffer_data+(pts++)) = -4.0f;
    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = -4.0f, *(vertex_buffer_data+(pts++)) = 4.0f;
    *(vertex_buffer_data+(pts++)) = 8.0f, *(vertex_buffer_data+(pts++)) = 0.0f, *(vertex_buffer_data+(pts++)) = 0.0f;


    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = 4.0f, *(vertex_buffer_data+(pts++)) = -4.0f;
    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = 4.0f, *(vertex_buffer_data+(pts++)) = 4.0f;
    *(vertex_buffer_data+(pts++)) = 8.0f, *(vertex_buffer_data+(pts++)) = 0.0f, *(vertex_buffer_data+(pts++)) = 0.0f;

    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = -4.0f, *(vertex_buffer_data+(pts++)) = -4.0f;
    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = 4.0f, *(vertex_buffer_data+(pts++)) = -4.0f;
    *(vertex_buffer_data+(pts++)) = 8.0f, *(vertex_buffer_data+(pts++)) = 0.0f, *(vertex_buffer_data+(pts++)) = 0.0f;

    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = -4.0f, *(vertex_buffer_data+(pts++)) = 4.0f;
    *(vertex_buffer_data+(pts++)) = -6.0f, *(vertex_buffer_data+(pts++)) = 4.0f, *(vertex_buffer_data+(pts++)) = 4.0f;
    *(vertex_buffer_data+(pts++)) = 8.0f, *(vertex_buffer_data+(pts++)) = 0.0f, *(vertex_buffer_data+(pts++)) = 0.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);    
}

void Enemy::draw(glm::mat4 VP) 
{
    glm::mat4 transform[2];
    Matrices.model = glm::mat4(1.0f);
    transform[0] = glm::translate (this->position); 
    transform[1] = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (transform[0] * transform[1]);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy::rotation_decider(int flag)
{
    if(flag == 2)
    {   
        this->rotation += 90 + rand()%360; 
    }
    else if(flag == 1)
    {
        this->rotation += 90 - rand()%360;
    }
}


void Enemy::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void Enemy::tick()
{
    this->position.x -= this->speed_x*sin((this->rotation - 90) * M_PI / 180);
    this->position.z -= this->speed_x*cos((this->rotation - 90) * M_PI / 180);
    // this->speed_x = rand()%2;
    // this->position.x += this->speed_x;
    // if(this->position.x > 200 || this->position.x < -200)
    // {
    //     this->position.x =  50;
    // }
    // this->speed_z = rand()%2;
    // this->position.z += this->speed_z; 
}

bounding_box_t Enemy::bounding_box() 
{
    bounding_box_t bbox = { this->position.x, this->position.y, this->position.z, 7, 4, 4 };
    return bbox;
}
