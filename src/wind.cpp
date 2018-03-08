#include "wind.h"
#include "main.h"

Wind::Wind(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->accel_x = 0.005;
    this->accel_y = 60;
    this->speed_x = 1;
    this->speed_y = 3;
    this->occur = 0;    
    GLfloat g_vertex_buffer_data[4000];
    double pi = 3.14;
    int j=0,k=1;
    float xx=0.1,yy=0.0;
    int num2 = 360, num1= 0;
    float rad = 1.4;
    for(int i=num1;i<num2;i++)
    {
        g_vertex_buffer_data[j++] = 0.0f;
        g_vertex_buffer_data[j++] = 0.0f;
        g_vertex_buffer_data[j++] = 0.0f;

        g_vertex_buffer_data[j++] = xx;
        g_vertex_buffer_data[j++] = 0.0f;
        g_vertex_buffer_data[j++] = yy;

        xx= rad*cos(-(float)k*pi/180);
        yy= rad*sin(-(float)k*pi/180);
        k++;

        g_vertex_buffer_data[j++] = xx;
        g_vertex_buffer_data[j++] = 0.0f;
        g_vertex_buffer_data[j++] = yy;
    }
    g_vertex_buffer_data[j++] = -rad;
    g_vertex_buffer_data[j++] = 0.1f;
    g_vertex_buffer_data[j++] = 0.0f;
    g_vertex_buffer_data[j++] = rad;
    g_vertex_buffer_data[j++] = 0.0f;
    g_vertex_buffer_data[j++] = 0.1f;
    g_vertex_buffer_data[j++] = 0.0f;
    g_vertex_buffer_data[j++] = 2*rad;
    g_vertex_buffer_data[j++] = 0.0f;

    this->object = create3DObject(GL_TRIANGLES, (num2 -num1)*3 + 9, g_vertex_buffer_data, color, GL_FILL);
}

void Wind::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position); 
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Wind::tick()
{
    this->speed_y += this->accel_y;
    this->position.y -= this->speed_y;
    if(this->position.y <= 45)
    {
        float coord_x = rand()%1683 - 859;
        float coord_y = rand()%100 + 200.0f;
        float coord_z = rand()%1937 - 973;
        this->set_position(coord_x,coord_y,coord_z);
        this->speed_y = 2;
    }
}
void Wind::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Wind::bounding_box() {
    double  x = this->position.x;
    double  y = this->position.y;
    double  z = this->position.z;
    bounding_box_t bbox = { x, y, z, 4, 4,4 };
    return bbox;
}
