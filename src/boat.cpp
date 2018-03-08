#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed_x = 2.5;
    this->speed_z = 1.5;
    this->speed_y = 0;
    this->omega = 0.27;
    this->lev_angle = 0;
    this->accel_y = -0.0001;
    this->gravity = 0;
    this->accel_x = 0.012;  
    static const GLfloat vertex_buffer_data[] = {

         /* My blackpearl*/
        -18.0,-6.0f, 12.0f,
         18.0, 6.0f, 9.0f,
        -18.0, 6.0f, 12.0f,
        -18.0,-6.0f, 12.0f,
         18.0, 6.0f, 9.0f,
         18.0,-6.0f, 9.0f,

         18.0, 6.0f, 9.0f,
         18.0,-6.0f,-9.0f,
         18.0,-6.0f, 9.0f,
         18.0, 6.0f, 9.0f,
         18.0,-6.0f,-9.0f,
         18.0, 6.0f,-9.0f,

         18.0, 6.0f,-9.0f,
        -18.0,-6.0f,-12.0f,
         18.0,-6.0f,-9.0f,
         18.0, 6.0f,-9.0f,
        -18.0,-6.0f,-12.0f,
        -18.0, 6.0f,-12.0f,

        -18.0,-6.0f,-12.0f,
        -18.0, 6.0f, 12.0f,
        -18.0, 6.0f,-12.0f,
        -18.0,-6.0f,-12.0f,
        -18.0, 6.0f, 12.0f,
        -18.0,-6.0f, 12.0f,

        -18.0,-6.0f, 12.0f,
         18.0,-6.0f,-9.0f,
         18.0,-6.0f, 9.0f,
        -18.0,-6.0f, 12.0f,
         18.0,-6.0f,-9.0f,
        -18.0,-6.0f,-12.0f,

         18.0, 6.0f, 9.0f,
         18.0,-6.0f, 9.0f,
        36.0, 9.0f, 0.0f,

         18.0,-6.0f, 9.0f,
         18.0,-6.0f,-9.0f,
        36.0, 9.0f, 0.0f,

         18.0,-6.0f,-9.0f,
         18.0, 6.0f,-9.0f,
        36.0, 9.0f, 0.0f,

         18.0, 6.0f,-9.0f,
         18.0, 6.0f, 9.0f,
        36.0, 9.0f, 0.0f,

        15.0f,-6.0f, 1.5f,   
        18.0f,-6.0f, 1.5f,
        16.5f, 60.0f, 0.0f,

        18.0f,-6.0f, 1.5f,
        18.0f,-6.0f,-1.5f,
        16.5f, 60.0f, 0.0f,

        18.0f,-6.0f,-1.5f,
        15.0f,-6.0f,-1.5f,
        16.5f, 60.0f, 0.0f,

        15.0f,-6.0f,-1.5f,
        15.0f,-6.0f, 1.5f,
        16.5f, 60.0f, 0.0f,

        // Sail coordinates

        16.5f,48.0f, -10.0f,
        16.5f, 27.0f, -20.0f,
        16.5f, 48.0f,-20.0f,

        16.5f,27.0f, -20.0f,
        16.5f, 27.0f, -10.0f,
        16.5f, 48.0f,-10.0f,

        16.5f,48.0f, 0.0f,
        16.5f, 27.0f, 0.0f,
        16.5f, 27.0f,-10.0f,

        16.5f,48.0f, 0.0f,
        16.5f, 27.0f, -10.0f,
        16.5f, 48.0f,-10.0f,

        16.5f,48.0f, 0.0f,
        16.5f, 27.0f, 0.0f,
        16.5f, 27.0f,10.0f,

        16.5f,48.0f, 0.0f,
        16.5f, 27.0f, 10.0f,
        16.5f, 48.0f,10.0f,

        16.5f,48.0f, 10.0f,
        16.5f, 27.0f, 10.0f,
        16.5f, 27.0f,20.0f,

        16.5f,48.0f, 10.0f,
        16.5f, 27.0f, 20.0f,
        16.5f, 48.0f,20.0f,

        // 16.5f,51.0f, 0.0f,
        // 16.5f, 33.0f, 0.0f,
        // 16.5f, 33.0f, 18.0f

        /*Sail coordinates*/
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_VIOLET, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+18, COLOR_GOLD, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+36, COLOR_VIOLET, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+54, COLOR_GOLD, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+72, COLOR_TREE, GL_FILL);
    this->object[5] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data+90, COLOR_CRIMSON, GL_FILL);
    this->object[6] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data+126, COLOR_BLACK, GL_FILL);
    this->object[7] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+162, COLOR_CRIMSON, GL_FILL);
    this->object[8] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+171, COLOR_CRIMSON, GL_FILL);
    this->object[9] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+180, COLOR_WHITE, GL_FILL);
    this->object[10] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+189, COLOR_WHITE, GL_FILL);
    this->object[11] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+198, COLOR_CRIMSON, GL_FILL);
    this->object[12] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+207, COLOR_CRIMSON, GL_FILL);
    this->object[13] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+216, COLOR_WHITE, GL_FILL);
    this->object[14] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+225, COLOR_WHITE, GL_FILL);

}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2   = glm::rotate((float) (this->lev_angle * M_PI / 180.0f), glm::vec3(this->position.x, this->position.y,this->position.z - 2));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    glm::mat4 rotate = rotate1 * rotate2;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);
    draw3DObject(this->object[5]);
    draw3DObject(this->object[6]);
    draw3DObject(this->object[7]);
    draw3DObject(this->object[8]);
    draw3DObject(this->object[9]);
    draw3DObject(this->object[10]);
    draw3DObject(this->object[11]);
    draw3DObject(this->object[12]);
    draw3DObject(this->object[13]);
    draw3DObject(this->object[14]);
    
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {

    this->speed_y  += gravity;
    this->position.y += this->speed_y;
    if (this->position.y < 48.12)
    {
        this->position.y  = 48.12;
        this->speed_y = 0;
        this->gravity = 0 ;
    }
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Boat::movement_boat(char type, float angle)
{
    if (type == 'r')
    {
        this->rotation = this->rotation - this->speed_z*0.55;
    }

    else if (type == 'l')
    {
        this->rotation = this->rotation + this->speed_z*0.55;
    }

    else if (type == 'f')
    {
        this->position.z = this->position.z - this->speed_x*cos(angle);
        this->position.x = this->position.x - this->speed_x*sin(angle);
    }

    else if (type == 'b')
    {
        this->position.z = this->position.z + this->speed_x*cos(angle);
        this->position.x = this->position.x + this->speed_x*sin(angle);
    }

    else if(type == 'j')
    {
        this->speed_y = 1.85;
        this->gravity = -0.052;
    }

    else if (type == 's')
    {
        return;
    }
}

bounding_box_t Boat::bounding_box() {
    double  x = this->position.x;
    double  y = this->position.y;
    double  z = this->position.z;
    bounding_box_t bbox = { x, y, z, 35, 23, 29};
    return bbox;
}
