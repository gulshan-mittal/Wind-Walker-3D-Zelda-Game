#include "health.h"
#include "main.h"

Health::Health(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.0;
    this->life = 2.2f;
    static GLfloat vertex_buffer_data[110];
    int j =0;

    *(vertex_buffer_data+ (j++)) = -1.0f,*(vertex_buffer_data+ (j++)) = -1.0f,*(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f, *(vertex_buffer_data+ (j++)) = -1.0f, *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = 1.0f, *(vertex_buffer_data+ (j++)) = 1.0f ;

    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;

    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;

    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;

    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;

    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;

    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;

    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;

    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;

    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;

    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = -1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;

    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = -1.0f ,*(vertex_buffer_data+ (j++)) = 1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;
    *(vertex_buffer_data+ (j++)) = 1.0f ,*(vertex_buffer_data+ (j++)) = -1.0f , *(vertex_buffer_data+ (j++)) = 1.0f;


    this->life_bar[0] = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_DARKBROWN, GL_FILL);
    this->life_bar[1] = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_WHITE, GL_FILL);
    this->life_bar[2] = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Health::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 scale_boundary = glm::scale(glm::mat4(1.0f), glm::vec3(2.4f, 0.5f, 1.0f));
    glm::mat4 scale_empty    = glm::scale(glm::mat4(1.0f), glm::vec3(2.2f, 0.3f, 1.0f));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale_boundary);
    glm::mat4 MVPboundary = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVPboundary[0][0]);
    draw3DObject(this->life_bar[0]);

    Matrices.model = glm::mat4(1.0f);
    Matrices.model *= (translate * rotate * scale_empty);
    glm::mat4 MVPempty = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVPempty[0][0]);
    draw3DObject(this->life_bar[1]);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 transform[3];
    if ((this->life) > 0) 
    {
        transform[0] = glm::translate(glm::mat4(1.0f), glm::vec3(this->position.x - (2.2 - this->life), this->position.y, this->position.z)); 
    }
    int a[3];
    a[0]= 1, a[1] = 0, a[2] = 0;
    transform[1]    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(a[0], a[1], a[2]));
    transform[2]    = glm::scale(glm::mat4(1.0f), glm::vec3(this->life, 0.3f, 1.0f));

    Matrices.model = glm::mat4(1.0f);
    Matrices.model = Matrices.model*(transform[0] * transform[1] * transform[2]);
    glm::mat4 MVPlife = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVPlife[0][0]);
    draw3DObject(this->life_bar[2]);
}

void Health::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void Health::life_reduce() 
{
    this->life -= 0.1;
}

void Health::tick() 
{
    this->rotation += speed;
}

