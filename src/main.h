#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <limits>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ao/ao.h>
#include <mpg123.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projectionP;
    glm::mat4 projectionO;
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;
extern glm::mat4 VP;
extern double camera_rotation_angle, camera_y, camera_zoom, camera_look_x, camera_look_y;
enum camera_view_t {CAMERA_TOWER, CAMERA_BOAT, CAMERA_FOLLOW, CAMERA_TOP, CAMERA_HELICOPTER};
// extern enum camera_view_t camera_view;
extern bool camera_ortho;


// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float z;
    float length;
    float width;
    float height;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();
void camera_zooming(int type);
void camera_helicopter(float x_pos, float y_pos);
void camera_mode();
void camera_transform();
void signal_handler();
int rock_collision_decider(const bounding_box_t & temp_rock);
void bounce_back(const bounding_box_t & temp_rock, float coord_x, float coord_z);
void canon_initiate();
void dragon_reinitialize();
void enemy_initiate(int idx) ;
void controller_dragon();
void controller_enemy(int idx);
void change_weather();
void change_weapon();
glm::mat4 ortho_projection();

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_YG;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_GREY;
extern const color_t COLOR_POND;
extern const color_t COLOR_VIOLET;
extern const color_t COLOR_PINK;
extern const color_t COLOR_TAN;
extern const color_t COLOR_CRIMSON;
extern const color_t COLOR_GOLD;
extern const color_t COLOR_DARKGREEN;
extern const color_t COLOR_DARKBLUE;
extern const color_t COLOR_DARKBROWN;
extern const color_t COLOR_TREE;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_SILVER;
extern const color_t COLOR_TEMP;
extern const color_t COLOR_ORANGE;
extern const color_t COLOR_LIGHTBLACK;
extern const color_t COLOR_OLIVE;


//Audio
void audio_init();
void audio_play();
void audio_close();

#endif
