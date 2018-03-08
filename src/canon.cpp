#include "canon.h"
#include "main.h"

Canon::Canon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->release = 0;
    for(int j=0;j<6;j++)
    {
        this->params[j] = 0;
    }
    float pi = 3.14159;
    double phi = 0;
    double init[3];
    double radius = 7.0f;
    static GLfloat vertex_buffer_data[800000];
    double i = 0.0f;
    double j = 0.0f;
    double k = 0.0f;
    int pts = 0;
    double theta = 0;
    
    for (phi=0; phi  - 180 <= 0; phi++) 
    {
        theta = 1;
        init[0] = radius * sin((double)phi*M_PI/180) * cos((double)theta*M_PI/180);
        init[1] = radius * sin((double)phi*M_PI/180) * sin((double)theta*M_PI/180);
        k = radius * cos((double)phi*M_PI/180);
        i = init[0];
        j = init[1];
        theta++;
        do {
    
            *(vertex_buffer_data +pts) = i;
            pts++;
            *(vertex_buffer_data + pts) = j;
            pts++;
            *(vertex_buffer_data + pts) = k;
            pts++;

            
            *(vertex_buffer_data + pts) = 0.0f;
            pts++;
            *(vertex_buffer_data + pts) = 0.0f;
            pts++;
            *(vertex_buffer_data + pts) = 0.0f;
            pts++;

            i = radius * sin((double)phi*M_PI/180);
            i = i* cos((double)theta*M_PI/180);
            j = radius * sin((double)phi*M_PI/180);
            j = j * sin((double)theta*M_PI/180);
            theta++;

            *(vertex_buffer_data +pts) = i;
            pts++;
            *(vertex_buffer_data + pts) = j;
            pts++;
            *(vertex_buffer_data + pts) = k;
            pts++;

        } while(i != (init[0]) && j != (init[1]));
    }
    int count = pts/3;
    this->object = create3DObject(GL_TRIANGLES, count, vertex_buffer_data, color, GL_FILL);   
}


void Canon::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void Canon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



void Canon::tick(float xx, float yy, float zz) 
{
    this->position.x = this->position.x - this->params[0]*sin(this->params[4]);
    this->position.z = this->position.z - this->params[0]*cos(this->params[4]);
    float max_dis = 400.0*400.0;
    float tp_cord[4], unit_vec;
    tp_cord[0] = xx -this->position.x;
    tp_cord[1] = yy -this->position.y;
    tp_cord[2] = zz -this->position.z;
    unit_vec = (tp_cord[0]*tp_cord[0] + tp_cord[1]*tp_cord[1] + tp_cord[2]*tp_cord[2]);
    if(max_dis <= unit_vec)
    {
        this->release = 0;
        this->params[0] = 0;
        this->params[4] = 0;
    }


    // for cannon ball

    // this->params[1] += this->params[2];
    // this->position.y += this->params[1];
    // if(this->position.y < 39)
    // {
    //     for(int j=0;j<3;j++)
    //     {
    //         this->params[j]= 0;
    //     }
    //     this->release = 0;
    // }
}

bounding_box_t Canon::bounding_box() 
{
    bounding_box_t bbox = { this->position.x, this->position.y, this->position.z, 4, 4, 4 };
    return bbox;
}

void Canon::tick_aurora()
{
    this->position.y += this->speed_y;
    float temp_angle = (this->angle - 90)*(M_PI/180);
    this->position.x -= (this->speed_x*sin(temp_angle));
    this->position.z -= (this->speed_x*cos(temp_angle));
    this->speed_y -= 0.01; 
}
