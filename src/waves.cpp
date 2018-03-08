#include "waves.h"
#include "main.h"

Waves::Waves(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed_x = 0.2;
    this->speed_y = 0.2;
    this->accel_x = 0.003;
    this->accel_y = 0.028;
    static GLfloat vertex_buffer_data[27];
    int j =0;
    for(int k=0;k<5;k++)
    {
        vertex_buffer_data[j++] = 0.0f;
    }
    vertex_buffer_data[j++] = -6.0f;
    vertex_buffer_data[j++] = -8.0f;
    vertex_buffer_data[j++] = 0.0f;
    vertex_buffer_data[j++] = 7.0f;
    for(int k=0;k<5;k++)
    {
        vertex_buffer_data[j++] = 0.0f;
    }
    vertex_buffer_data[j++] = -6.0f;
    vertex_buffer_data[j++] = 8.0f;
    vertex_buffer_data[j++] = 0.0f;
    vertex_buffer_data[j++] = 7.0f;

    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color, GL_FILL);
}

void Waves::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position); 
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    glm::mat4 myScalingMatrix = glm::scale(glm::vec3(2.0f,0.0f,2.0f));
    Matrices.model *= (translate * rotate *myScalingMatrix);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Waves::tick()
{
    this->speed_y += this->accel_y;
    this->position.y += this->speed_y;
    if(this->position.y >= 40.7)
    {
        this->speed_y = -0.2;
    }
    if(this->position.y <= 40.13)
    {
        this->speed_x = 0.2;
    }
    // this->position.y -= 2*speed_x;
    // this->position.y += speed_x;
}

void Waves::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Waves::bounding_box() {
    double  x = this->position.x;
    double  y = this->position.y;
    double  z = this->position.z;
    bounding_box_t bbox = { x, y, z, 4, 4,4 };
    return bbox;
}
