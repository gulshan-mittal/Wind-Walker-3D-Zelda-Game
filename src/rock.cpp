#include "rock.h"
#include "main.h"

Rock::Rock(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        8.0f, 0.0f, 8.0f,
        8.0f, 0.0f, -8.0f,
        -8.0f, 0.0f, 8.0f,

        8.0f, 0.0f, -8.0f,
        -8.0f, 0.0f, -8.0f,
        -8.0f, 0.0f, 8.0f,

        8.0f, 0.0f, -8.0f,
        -8.0f, 0.0f, -8.0f,
        0.0f,10.0f, 0.0f,
        
        8.0f, 0.0f, 8.0f,
        8.0f, 0.0f, -8.0f,
        0.0f,10.0f, 0.0f,

        -8.0f, 0.0f, -8.0f,
        -8.0f, 0.0f, 8.0f,
        0.0f,10.0f, 0.0f,

        8.0f, 0.0f, 8.0f,
        -8.0f, 0.0f, 8.0f,
        0.0f,10.0f, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
}

void Rock::draw(glm::mat4 VP) {
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

void Rock::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Rock::bounding_box() {
    double  x = this->position.x;
    double  y = this->position.y;
    double  z = this->position.z;
    bounding_box_t bbox = { x, y, z, 16, 16, 10 };
    return bbox;
}
