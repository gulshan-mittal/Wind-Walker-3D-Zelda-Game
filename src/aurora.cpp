#include "aurora.h"
#include "canon.h"
#include "main.h"

Aurora::Aurora(float x, float y, float z) {
    this->flag_shoot = 0;
    this->position = glm::vec3(x, y, z);
    this->rotation_xz = 0;
    this->rotation_y  = 2;
    this->speed = 0.0;

    /* Structure of the cannon */
    float  new_i = 0.0f;
    int k = 1;
    int pts = 0;
    float  in_radius = 2.15f;
    float j = 0.0f;
    float height = 30.0f;
    float  i = in_radius;
    static GLfloat vertex_buffer_data[21000];
    float  new_j = 0.0f;
    for(int len = 0 ;len < 360;len++)
    {
        new_i = in_radius * cos((float)k*M_PI/180);
        new_j = in_radius * sin((float)k*M_PI/180);
        k++;

        
        *(vertex_buffer_data+(pts++)) = 0.0f;
        *(vertex_buffer_data+(pts++)) = i;
        *(vertex_buffer_data+(pts++)) = j;
        

        
        *(vertex_buffer_data+(pts++)) = 0.0f;
        *(vertex_buffer_data+(pts++)) = 0.0f;
        *(vertex_buffer_data+(pts++)) = 0.0f;

        
        *(vertex_buffer_data+(pts++)) = 0.0f;
        *(vertex_buffer_data+(pts++)) = new_i;
        *(vertex_buffer_data+(pts++)) = new_j;
        

        *(vertex_buffer_data+(pts++)) = 0.0f;
        *(vertex_buffer_data+(pts++)) = i;
        *(vertex_buffer_data+(pts++)) = j;
        

        *(vertex_buffer_data+(pts++)) = height;
        *(vertex_buffer_data+(pts++)) = i;
        *(vertex_buffer_data+(pts++)) = j;
        

        *(vertex_buffer_data+(pts++)) = height;
        *(vertex_buffer_data+(pts++)) = new_i;
        *(vertex_buffer_data+(pts++)) = new_j;
        

        *(vertex_buffer_data+(pts++)) = 0.0f;
        *(vertex_buffer_data+(pts++)) = i;
        *(vertex_buffer_data+(pts++)) = j;
        

        *(vertex_buffer_data+(pts++)) = 0.0f;
        *(vertex_buffer_data+(pts++)) = new_i;
        *(vertex_buffer_data+(pts++)) = new_j;
        

        *(vertex_buffer_data+(pts++)) = height;
        *(vertex_buffer_data+(pts++)) = new_i;
        *(vertex_buffer_data+(pts++)) = new_j;
        

        i = new_i, j = new_j;

    } 
    this->object = create3DObject(GL_TRIANGLES, pts/3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void Aurora::draw(glm::mat4 VP) 
{
    
    glm::mat4 transform[4];
    Matrices.model = glm::mat4(1.0f);
    transform[0] = glm::translate(glm::mat4(1.0f), this->position);    // glTranslatef
    transform[1] = glm::rotate((float) (this->rotation_xz * M_PI / 180.0f), glm::vec3(0, 1, 0));
    transform[2]  = glm::rotate((float) (this->rotation_y  * M_PI / 180.0f), glm::vec3(0, 0, 1));
    transform[3] = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    Matrices.model = Matrices.model * (transform[0] * transform[1] * transform[2] * transform[3]);
    
    glm::mat4 MVPboundary = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVPboundary[0][0]); draw3DObject(this->object);
    
    if (this->flag_shoot == 1)
    {
        canball.draw(VP);
    }
}

void Aurora::set_position(float x, float y, float z) 
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;        
}

/* Shoot Cannon balls from the cannon */
void Aurora::shoot() 
{
    float ball_x, ball_y, ball_z;
    ball_x = this->position.x - 30.0 * sin((this->rotation_xz - 90) * (M_PI/180));
    ball_y = this->position.y + 2.0 * sin((this->rotation_y) * (M_PI/180));
    ball_z = this->position.z - 30.0 * cos((this->rotation_xz - 90) * (M_PI/180));
    float speed_xz ;
    speed_xz = 4.20f * cos((this->rotation_y) * (M_PI/180));
    float speed_y;
    speed_y = 2.5*sin((this->rotation_y) * (M_PI/180));
    this->canball = Canon(ball_x, ball_y, ball_z, COLOR_RED);
    this->canball.speed_x = speed_xz;
    this->canball.speed_y = speed_y;
    this->canball.angle = this->rotation_xz;
}

void Aurora::tick() 
{

    if(this->flag_shoot == 1)
    {   
        if(this->canball.position.y <= 42.0f)
        {
            this->flag_shoot = 0;
        }
        this->canball.tick_aurora();
    }

    if (this->rotation_y <= 1)
    {
        this->rotation_y = 2;
    }
    else if (this->rotation_y >= 59)
    {
        this->rotation_y = 60;
    }    
}

