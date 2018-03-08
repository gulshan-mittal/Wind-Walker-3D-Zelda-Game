#include "treasure.h"
#include "main.h"

Treasure::Treasure(float x, float y, float z, float num, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->treasure_draw = 1;
    int pos = 0,i=0,k;
    GLfloat g_vertex_buffer_data[9*6];
    float pi = 3.14159;
    float angle = 0, theta=(2*pi)/6;
    i = 0;
    while(i<6)
    {
        *(g_vertex_buffer_data+pos)= 0.0f;
        pos = pos +1;
        *(g_vertex_buffer_data+pos)= 0.0f;
        pos = pos +1;        
        *(g_vertex_buffer_data+pos)= 0.0f;
        pos = pos +1;        
        for(k=0;k<2;k++)
        {
            *(g_vertex_buffer_data+pos)= 8*cos(angle);
            pos = pos +1;        
            *(g_vertex_buffer_data+pos)= 8*sin(angle);
            pos = pos +1;
            *(g_vertex_buffer_data+pos)= 0.0f;
            pos = pos +1;
            angle = angle + theta;
        }
        angle = angle - theta;
        i++;
    }
    this->object = create3DObject(GL_TRIANGLES, 3*6, g_vertex_buffer_data, color, GL_FILL);
}

void Treasure::draw(glm::mat4 VP) 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position); 
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Treasure::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}


bounding_box_t Treasure::bounding_box() 
{
    bounding_box_t bbox = { this->position.x, this->position.y, this->position.z, 0.1, 8, 7 };
    return bbox;
}
