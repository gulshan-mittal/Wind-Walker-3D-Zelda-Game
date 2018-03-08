#include "direction.h"
#include "main.h"

Direction::Direction(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->speed_x = 2.5;
    this->speed_z = 1.5;
    this->omega =0;

    float  in_radius = 0.80f, out_radius = 1.0f;
    float prev_y1;
    float prev_y2 , prev_x1;
    float prev_x2;
    static GLfloat vertex_buffer_data[7000];
    float  curr_x1 = in_radius, curr_x2 = 0.0f, curr_y1 = out_radius, curr_y2 = 0.0f;
    int pts = 0;
    int k = 1;

    for(int len = 0; len < 360;len++)
    {
        prev_x1 = in_radius * cos((float)k*M_PI/180);
        prev_x2 = in_radius * sin((float)k*M_PI/180);
        prev_y1 = out_radius * cos((float)k*M_PI/180);
        prev_y2 = out_radius * sin((float)k*M_PI/180);
        k++;

        
        *(vertex_buffer_data+pts) = curr_x1;
        pts++;
        *(vertex_buffer_data+pts) = curr_x2;
        pts++;
        *(vertex_buffer_data+pts) = 0.0f;
        pts++;

        
        *(vertex_buffer_data+pts) = curr_y1;
        pts++;
        *(vertex_buffer_data+pts) = curr_y2;
        pts++;
        *(vertex_buffer_data+pts) = 0.0f;
        pts++;

        
        *(vertex_buffer_data+pts) = prev_y1;
        pts++;
        *(vertex_buffer_data+pts) = prev_y2;
        pts++;
        *(vertex_buffer_data+pts) = 0.0f;
        pts++;


        *(vertex_buffer_data+pts) = curr_x1;
        pts++;
        *(vertex_buffer_data+pts) = curr_x2;
        pts++;
        *(vertex_buffer_data+pts) = 0.0f;
        pts++;

        *(vertex_buffer_data+pts) = prev_x1;
        pts++;
        *(vertex_buffer_data+pts) = prev_x2;
        pts++;
        *(vertex_buffer_data+pts) = 0.0f;
        pts++;

        *(vertex_buffer_data+pts) = prev_y1;
        pts++;
        *(vertex_buffer_data+pts) = prev_y2;
        pts++;
        *(vertex_buffer_data+pts) = 0.0f;
        pts++;

        curr_x1 = prev_x1;
        curr_x2 = prev_x2;
        curr_y1= prev_y1;
        curr_y2 = prev_y2;

    }

    this->object[0] = create3DObject(GL_TRIANGLES, pts/3, vertex_buffer_data, color, GL_FILL);

    static GLfloat vertex_buffer_data_needle[19];
    int len = 0;

    vertex_buffer_data_needle[len++] = 0.05f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = 0.25f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = -0.05f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = 0.00f;

    vertex_buffer_data_needle[len++] = 0.05f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = -0.25f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = -0.05f;
    vertex_buffer_data_needle[len++] = 0.00f;
    vertex_buffer_data_needle[len++] = 0.00f;


    this->object[1] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_needle, color, GL_FILL);
}

void Direction::draw(glm::mat4 VP) 
{
    glm::mat4 transform[3];
    Matrices.model = glm::mat4(1.0f);
    *(transform+0) = glm::translate(this->position);
    *(transform+1) = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1)) ;
    *(transform+2) = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 1.0f));
    // glm::mat4 rotate  =  transform[1]* glm::translate(glm::vec3(0, 0, 0));

    Matrices.model = Matrices.model*(transform[0]); 
    glm::mat4 MVPring = VP * Matrices.model ;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVPring[0][0]) , draw3DObject(this->object[0]);

    // Draw the needle of the compass
    Matrices.model = glm::mat4(1.0f) , Matrices.model *= (transform[0]*transform[1]*transform[2]) ;
    glm::mat4 MVPneedle = VP * Matrices.model ; 
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVPneedle[0][0]) , draw3DObject(this->object[1]);
}

void Direction::set_position(float x, float y, float z, float roation) 
{
    this->position = glm::vec3(x-50, y, z);
    this->rotation += rotation;
}

void Direction::tick(float rot) 
{
    this->rotation = rot;
}
