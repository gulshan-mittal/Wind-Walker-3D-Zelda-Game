#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x, float y, float z, color_t color) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed_x = 0.0;
    this->utility = 0;

    
    float  in_radius = 6.8f;
    float  out_radius = 9.0f;
    float height = 12.0f;
    static GLfloat vertex_buffer_data[1][22000];
    float  i = in_radius;
    float j = 0.0f;
    float a = out_radius;
    float b = 0.0f;
    int pts = 0, k = 1;
    float new_a = 0.0f;
    float new_b = 0.0f;
    float new_i = 0.0f;
    float new_j = 0.0f ;
    for(int ln = 0;ln <=360;ln++)
    {  
        new_i = in_radius * cos((float)k*M_PI/180);
        new_j = in_radius * sin((float)k*M_PI/180);
        new_a = out_radius * cos((float)k*M_PI/180);
        new_b = out_radius * sin((float)k*M_PI/180);
        k++;

        vertex_buffer_data[0][pts++] = i;
        vertex_buffer_data[0][pts++] = j;
        vertex_buffer_data[0][pts++] = -height;

        
        vertex_buffer_data[0][pts++] = 0.0f;
        vertex_buffer_data[0][pts++] = 0.0f;
        vertex_buffer_data[0][pts++] = -height;

        
        vertex_buffer_data[0][pts++] = new_i;
        vertex_buffer_data[0][pts++] = new_j;
        vertex_buffer_data[0][pts++] = -height;

        vertex_buffer_data[0][pts++] = i;
        vertex_buffer_data[0][pts++] = j;
        vertex_buffer_data[0][pts++] = -height;

        vertex_buffer_data[0][pts++] = a;
        vertex_buffer_data[0][pts++] = b;
        vertex_buffer_data[0][pts++] = 0.0f;

        vertex_buffer_data[0][pts++] = new_a;
        vertex_buffer_data[0][pts++] = new_b;
        vertex_buffer_data[0][pts++] = 0.0f;

        vertex_buffer_data[0][pts++] = i;
        vertex_buffer_data[0][pts++] = j;
        vertex_buffer_data[0][pts++] = -height;

        vertex_buffer_data[0][pts++] = new_i;
        vertex_buffer_data[0][pts++] = new_j;
        vertex_buffer_data[0][pts++] = -height;

        vertex_buffer_data[0][pts++] = new_a;
        vertex_buffer_data[0][pts++] = new_b;
        vertex_buffer_data[0][pts++] = 0.0f;

        vertex_buffer_data[0][pts++] = a;
        vertex_buffer_data[0][pts++] = b;
        vertex_buffer_data[0][pts++] = 0.0f;

        vertex_buffer_data[0][pts++] = i;
        vertex_buffer_data[0][pts++] = j;
        vertex_buffer_data[0][pts++] = height;

        vertex_buffer_data[0][pts++] = new_i;
        vertex_buffer_data[0][pts++] = new_j;
        vertex_buffer_data[0][pts++] = height;

        vertex_buffer_data[0][pts++] = a;
        vertex_buffer_data[0][pts++] = b;
        vertex_buffer_data[0][pts++] = 0.0f;

        vertex_buffer_data[0][pts++] = new_a;
        vertex_buffer_data[0][pts++] = new_b;
        vertex_buffer_data[0][pts++] = 0.0f;

        vertex_buffer_data[0][pts++] = new_i;
        vertex_buffer_data[0][pts++] = new_j;
        vertex_buffer_data[0][pts++] = height;

        vertex_buffer_data[0][pts++] = i;
        vertex_buffer_data[0][pts++] = j;
        vertex_buffer_data[0][pts++] = height;

        vertex_buffer_data[0][pts++] = 0.0f;
        vertex_buffer_data[0][pts++] = 0.0f;
        vertex_buffer_data[0][pts++] = height;

        vertex_buffer_data[0][pts++] = new_i;
        vertex_buffer_data[0][pts++] = new_j;
        vertex_buffer_data[0][pts++] = height;

        i = new_i, j = new_j, a = new_a, b = new_b;
    }

    
    this->object = create3DObject(GL_TRIANGLES, pts/3, vertex_buffer_data[0], color, GL_FILL);
}

void Barrel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 scale     = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Barrel::set_position(float x, float y, float z) 
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

void Barrel::tick() 
{
    this->rotation = this->rotation + this->speed_x;
}

