#include "dragon.h"
#include "main.h"

Dragon::Dragon(float x, float y, float z, color_t color)
{
    this->booster_val = 0;
    this->rotation = 0;
    int rnd_rot = rand()%2 + 1; 
    this->rotation_decider(rnd_rot);
    this->position = glm::vec3(x, y, z);
    this->booster_time = 900;
    this->speed_x = 2;
    this->val = 0;
    this->speed_y= 0;
    this->speed_z= 0;
    this->life = 3;
    

    float  radius = 10, depth;
    const double PI = 3.1415926535897;
    int N = 360;
    int i = 0, k;
    float  theta = PI * 2 / N;
    float  xi;
    float zi;

    GLfloat vertex_buffer_data[400000];    

    for (depth = 0; depth <= 12; depth += 0.1) 
    {
        for (k = 0; k <= N -1;) 
        {
            *(vertex_buffer_data+i) = 0.0f;
            i++;
            *(vertex_buffer_data+i) = depth;
            i++;
            *(vertex_buffer_data+i) = 0.0f;
            i++;

            xi = radius * cos(k * theta);
            zi = radius * sin(k * theta);

            *(vertex_buffer_data+i) = xi;
            i++;
            *(vertex_buffer_data+i) = depth;
            i++;
            *(vertex_buffer_data+i) = zi;
            i++;

            k++;
            xi = radius * cos(k * theta);
            zi = radius * sin(k * theta);

            *(vertex_buffer_data+i) = xi;
            i++;
            *(vertex_buffer_data+i) = depth;
            i++;
            *(vertex_buffer_data+i) = zi;
            i++;
        }
        radius -= 0.05;
    }

    static const GLfloat vertex_buffer_data2[] = {
        -4.0f,12.0f,-4.0f, 
        -4.0f,12.0f, 4.0f,
        -4.0f, 18.0f, 4.0f,

        4.0f, 18.0f,-4.0f, 
        -4.0f,12.0f,-4.0f,
        -4.0f, 18.0f,-4.0f,
        
        4.0f,12.0f, 4.0f,
        -4.0f,12.0f,-4.0f,
        4.0f,12.0f,-4.0f,

        4.0f, 18.0f,-4.0f,
        4.0f,12.0f,-4.0f,
        -4.0f,12.0f,-4.0f,

        -4.0f,12.0f,-4.0f,
        -4.0f, 18.0f, 4.0f,
        -4.0f, 18.0f,-4.0f,

        4.0f,12.0f, 4.0f,
        -4.0f,12.0f, 4.0f,
        -4.0f,12.0f,-4.0f,

        -4.0f, 18.0f, 4.0f,
        -4.0f,12.0f, 4.0f,
        4.0f,12.0f, 4.0f,

        4.0f, 18.0f, 4.0f,
        4.0f,12.0f,-4.0f,
        4.0f, 18.0f,-4.0f,

        4.0f,12.0f,-4.0f,
        4.0f, 18.0f, 4.0f,
        4.0f,12.0f, 4.0f,

        4.0f, 18.0f, 4.0f,
        4.0f, 18.0f,-4.0f,
        -4.0f, 18.0f,-4.0f,

        4.0f, 18.0f, 4.0f,
        -4.0f, 18.0f,-4.0f,
        -4.0f, 18.0f, 4.0f,

        4.0f, 18.0f, 4.0f,
        -4.0f, 18.0f, 4.0f,
        4.0f,12.0f, 4.0f
    };    

    this->object[0] = create3DObject(GL_TRIANGLES, 360 * 3 * depth * 10, vertex_buffer_data, COLOR_DARKBROWN, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data2, COLOR_DARKGREEN, GL_FILL);    
}

void Dragon::draw(glm::mat4 VP) 
{
    glm::mat4 transform[3];
    Matrices.model = glm::mat4(1.0f);
    transform[0] = glm::translate (this->position);    // glTranslatef
    transform[1] = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    transform[2] = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f,2.0f, 2.0f)); 

    Matrices.model = Matrices.model * (transform[0] * transform[1])*(transform[2]);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]), draw3DObject(this->object[0]) , draw3DObject(this->object[1]);    
}

void Dragon::rotation_decider(int flag)
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

void Dragon::set_position(float x, float y, float z) 
{
    this->position.x = x; this->position.y = y; this->position.z = z;
}

void Dragon::tick()
{
    this->position.x -= this->speed_x*sin((this->rotation - 90) * M_PI / 180);
    this->position.z -= this->speed_x*cos((this->rotation - 90) * M_PI / 180); 
}

bounding_box_t Dragon::bounding_box() 
{
    bounding_box_t bbox = { this->position.x, this->position.y, this->position.z, 38, 38, 30};
    return bbox;
}