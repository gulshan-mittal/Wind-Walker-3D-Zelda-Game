#include "ocean.h"
#include "main.h"
#include "limits.h"

Ocean::Ocean(float x, float y, float z, color_t color, double rad) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rad = rad;
    speed = 1;
    static GLfloat g_vertex_buffer_data[4000];
    int j=0,k=1;
    double pi = 3.14257;
    double xx=INT16_MAX;
    double zz = 0.0;
    for(int i=0;i<360;i++)
    {
        g_vertex_buffer_data[j++] = 0.0f;
        g_vertex_buffer_data[j++] = 0.0f;
        g_vertex_buffer_data[j++] = 0.0f;

        g_vertex_buffer_data[j++] = xx;
        g_vertex_buffer_data[j++] = 0.0f;
        g_vertex_buffer_data[j++] = zz;

        xx= INT16_MAX*cos(-(double)k*pi/180);
        zz= INT16_MAX*sin(-(double)k*pi/180);
        k++;

        g_vertex_buffer_data[j++] = xx;
        g_vertex_buffer_data[j++] = 0.0f;
        g_vertex_buffer_data[j++] = zz;
    }

    this->object = create3DObject(GL_TRIANGLES, 361*3, g_vertex_buffer_data, color, GL_FILL);
}

void Ocean::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ocean::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ocean::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

