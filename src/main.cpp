#include "main.h"
#include "timer.h"
#include "boat.h"
#include "aurora.h"
#include "ocean.h"
#include "waves.h"
#include "rock.h"
#include "canon.h"
#include "wind.h"
#include "treasure.h"
#include "barrel.h"
#include "enemy.h"
#include "direction.h"
#include "health.h"
#include "dragon.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
glm::mat4 VP;


/**************************
* Customizable functions *
**************************/
#define BITS 8
pid_t pid = -1;
Boat boat;
Canon canon;
Rock rock[200];
Waves wave[200];
Wind wind[300];
Aurora aurora;
Treasure treasure[71];
Treasure power_up;
int ocean_num = 5, camera_view = 1, voice = 1,enemy_num= 5,rock_num = 100, waves_num = 150, wind_num = 150 , barrel_num = 70,treasure_num = 70;
Ocean ocean[20];
Barrel barrel[71];
Direction direction;
Enemy enemy[8];
Health health;
Dragon dragon;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
double camera_rotation_angle = 0, camera_zoom = 0;
double camera_coord[4];
double camera_lookup[4];
// bool camera_ortho;
const float pi = 3.14159;
int duration = 240, start_time = 1000;
int wind_effect[2];
float windshift_x, windshift_z, wind_accelx,wind_accelz;
float heart_lives = 4.0;
int rock_halt = 0;
int jump_flag = 0;
float curr_rock_rel_rad = 0.0f,curr_rock_rel_ds = 0.0f;
float curr_rock_rel_x = 0.0f,curr_rock_rel_z = 0.0f;
int score = 0, lives = 6;
int dragon_kill = 0, rain_st = 3000, rain_dur = 800, rain_flag = 0;
int booster_flag = 0;
int booster_time = 0 ,weather_change = 0, weapon_change = 0;
color_t color_arr[5] = {COLOR_YELLOW, COLOR_GREEN, COLOR_PINK, COLOR_DARKBROWN, COLOR_RED};

int prev_xpos = 0, prev_ypos = 0;
// camera_view_t camera_view;


Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (camera_coord[0],camera_coord[1], camera_coord[2]);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (camera_lookup[0] ,camera_lookup[1], camera_lookup[2]);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 3, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)); // Fixed camera for 2D (ortho) in XY plane
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);


    for(int j=0;j<ocean_num;j++)
    {
        ocean[j].draw(VP);
    }
    boat.draw(VP);
    if(canon.release && weapon_change == 0)
    {
        canon.draw(VP);
    }

    if(weapon_change == 1)
    {
        aurora.draw(VP);
    }

    for(int j=0;j<rock_num;j++)
    {
        rock[j].draw(VP);
    }

    for(int j=0;j<waves_num;j++)
    {
        wave[j].draw(VP);
    }
    
    int count = 0;
    while(count< barrel_num)
    {
        if(barrel[count].utility == 1)
        {
            barrel[count].draw(VP);
        }
        count++;    
    }

    count = 0;
    while(count< barrel_num)
    {
        if(treasure[count].treasure_draw == 1)
        {
            treasure[count].draw(VP);
        }
        count++;    
    }

    for(int j=0;j< enemy_num ;j++)
    {
        if(enemy[j].val == 1)
        {
            enemy[j].draw(VP);
        }
    }
    if(dragon.val == 1)
    {
        dragon.draw(VP);
    }

    for(int j=0;j<1;j++)
    {
        if(wind_effect[j] || weather_change)
        {
            for(int k=0;k<wind_num;k++)
            {
                wind[k].draw(VP);
            }
        }
    }


    if(power_up.treasure_draw == 1)
    {
        power_up.draw(VP);
    }

    direction.draw(ortho_projection());
    health.draw(ortho_projection());
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int forward = glfwGetKey(window, GLFW_KEY_UP);
    int backward = glfwGetKey(window, GLFW_KEY_DOWN);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int attack = glfwGetKey(window, GLFW_KEY_F);
    int canon_rot_up = glfwGetKey(window, GLFW_KEY_W);
    int canon_rot_down = glfwGetKey(window, GLFW_KEY_S);

    if (left) 
    {
        boat.movement_boat('l', 0.0f); 
           
    }
    if(right)
    {
        boat.movement_boat('r', 0.0f);
        
    }
    if(forward)
    {
        float tp_angle = (boat.rotation - 90)*(pi/180);
        boat.movement_boat('f', tp_angle);
          
    }
    if(backward)
    {
        float tp_angle = (boat.rotation - 90)*(pi/180);
        boat.movement_boat('b', tp_angle);
    }
    if(jump)
    {
        if(boat.position.y <= 48.13)
        {
            boat.movement_boat('j', 0.0f);
        }
    }

    if(attack)
    {
        if(weapon_change == 0)
        {
            if(canon.release == 0)
            {
                
                canon.release = 1;
                for(int j=0;j<2;j++)
                {
                    canon.params[j] = 10;
                }
                canon.params[2] = -0.5;
                canon.params[4] = (boat.rotation - 90)*(pi/180.0);
                
            }
        }
        else if(weapon_change == 1)
        {
            if(aurora.flag_shoot == 0)
            {
                aurora.flag_shoot = 1;
                aurora.shoot();
            }
        }
    }

    if(canon_rot_up && weapon_change == 1)
    {
        aurora.rotation_y += 1;
    }
    if(canon_rot_down && weapon_change == 1)
    {
        aurora.rotation_y -= 1;
    }
}

void tick_elements() {

    boat.tick();
    direction.tick(boat.rotation);    
    for(int j=0;j<waves_num;j++)
    {
        wave[j].tick();
        if(wind_effect[0] == 1 && duration % 4 == 0)
        {
            float coord_x = rand()%3060 - 987; 
            float coord_z = rand()%3263 - 600;
            wave[j].set_position(coord_x+boat.position.x, 40.12,coord_z+boat.position.z);
        }
    }
    if(wind_effect[0] || weather_change)
    {
        for(int j=0;j<wind_num;j++)
        {
            wind[j].tick();
        }
    }
    else if(start_time <= 2 && wind_effect[0])
    {
       for(int j=0;j<wind_num;j++)
        {
            float coord_x = rand()%3060 - 987.0f; 
            float coord_z = rand()%3263 - 600.0f;
            float coord_y  = rand()%100 + 650.0f;
            wind[j].set_position(coord_x + boat.position.x, coord_y, coord_z + boat.position.z);
        } 
    }
    for(int j=0;j<treasure_num;j++)
    {
        if(barrel[j].utility == 1)
        {
            if(detect_collision(boat.bounding_box(),treasure[j].bounding_box()))
            {
                barrel[j].utility = 0;
                treasure[j].treasure_draw = 0;
                score += 20+rand()%20;
            }
        }
    }

    for(int j=0;j<treasure_num;j++)
    {   
        if(treasure[j].treasure_draw)
        {
            treasure[j].rotation += 1.25;
        }
    }

    if(booster_flag == 1)
    {
        booster_time = booster_time - 1;
        boat.speed_x += boat.accel_x;
        if(booster_time <= 0)
        {
            booster_flag = 0;
            power_up.treasure_draw = 0;
            boat.speed_x = 2.5;
            booster_time = 0;
        }
    }
    int dragon_score = (dragon_kill+1)%5;
    if(dragon_score == 0)
    {
        if(dragon.val != 1)
        {
            dragon_reinitialize();
        }
    }
    if(weapon_change == 0)
    {
        if(canon.release == 0)
        {
            canon.set_position(boat.position.x, boat.position.y, boat.position.z);
        }
        else if(canon.release = 1)
        {
            canon.tick(boat.position.x, boat.position.y,boat.position.z);
        } 
    }
    else if(weapon_change == 1)
    {
        aurora.set_position(boat.position.x - (3.0f*sin(boat.rotation -90)*(M_PI/180)),boat.position.y +0.70f,boat.position.z  - (3.00f*cos(boat.rotation -90)*(M_PI/180)));
        aurora.rotation_xz = boat.rotation;
        aurora.tick();
    }

    float temp_x = boat.position.x, temp_z = boat.position.z;

    for(int j=0;j<enemy_num;j++)
    {
        if(detect_collision(boat.bounding_box(), enemy[j].bounding_box()))
        {
            health.life_reduce();
            if(health.life <= 0)
            {
                health.life = 2.2;
                lives = lives - 1;
            }
            bounce_back(enemy[j].bounding_box(),temp_x,temp_z);
            enemy_initiate(j);

        }
    }

    for(int j=0;j<enemy_num;j++)
    {
        if(canon.release == 1)
        {
            if(detect_collision(canon.bounding_box(), enemy[j].bounding_box()))
            {
                canon_initiate();
                enemy_initiate(j);
                dragon_kill += 1;
                score += rand()%50 + 50;
            }
        }

        if(aurora.flag_shoot == 1)
        {
            if(detect_collision(aurora.canball.bounding_box(), enemy[j].bounding_box()))
            {
                aurora.flag_shoot = 0;
                enemy_initiate(j);
                dragon_kill += 1;
                score += rand()%50 + 50;
            }
        }
    }

    for(int j=0;j<rock_num;j++)
    {   
        if(canon.release == 1)
        {
            if(detect_collision(canon.bounding_box(), rock[j].bounding_box()))
            {
                canon_initiate();
                score += rand()%50;
                float coord_x = rand()%2000 - 700;
                float coord_z = rand()%2000 - 1000;
                rock[j].position.x = coord_x;
                rock[j].position.z = coord_z;
                rock[j].position.y = 45.12;
            }
        }

        if(aurora.flag_shoot == 1)
        {
            if(detect_collision(aurora.canball.bounding_box(), rock[j].bounding_box()))
            {
                aurora.flag_shoot = 0;
                score += rand()%50;
                float coord_x = rand()%2000 - 700;
                float coord_z = rand()%2000 - 1000;
                rock[j].position.x = coord_x;
                rock[j].position.z = coord_z;
                rock[j].position.y = 45.12;
            }
        }
    }

    if(power_up.treasure_draw == 1)
    {
        if(detect_collision(boat.bounding_box(), power_up.bounding_box()))
        {
            boat.speed_x = 2.6;
            power_up.treasure_draw = 0;
            booster_flag = 1;
            booster_time = 720;
            lives += 1;
        }
    }

    temp_x = boat.position.x, temp_z = boat.position.z;
    if(dragon.val == 1)
    {
        if(detect_collision(dragon.bounding_box(),boat.bounding_box()))
        {
            lives -= 1;
            dragon_reinitialize();
            bounce_back(dragon.bounding_box(), temp_x, temp_z);
        }
        if(detect_collision(dragon.bounding_box(),canon.bounding_box()))
        {
            canon_initiate();
            dragon.life = dragon.life -1;
            if(dragon.life <= 0)
            {
                dragon.val = 0;
                dragon.life = 3;
                dragon_kill += 1;
                score += rand()%50 + 80;
                power_up.position.x = dragon.position.x;
                power_up.position.y = dragon.position.y;
                power_up.position.z = dragon.position.z;
                power_up.treasure_draw = 1;
            }
            else if(dragon.life > 0)
            {
                dragon_reinitialize();
            }
        }
        else if(detect_collision(dragon.bounding_box(),aurora.canball.bounding_box()))
        {
            aurora.flag_shoot = 0;
            dragon.life = dragon.life -1;
            if(dragon.life <= 0)
            {
                dragon.val = 0;
                dragon.life = 3;
                dragon_kill += 1;
                score += rand()%50 + 80;
                power_up.position.x = dragon.position.x;
                power_up.position.y = dragon.position.y;
                power_up.position.z = dragon.position.z;
                power_up.treasure_draw = 1;
            }
            else if(dragon.life > 0)
            {
                dragon_reinitialize();
            }
        }
    }

    for(int j=0;j<1;j++)
    {
        if(wind_effect[j] == 1)
        {
            duration = duration -1;
            wind_accelx += 0.00005;
            wind_accelz += 0.00005;
            boat.position.x += wind_accelx*windshift_x*150;
            boat.position.z += wind_accelz*windshift_z*150; 
            if(duration <=0 )
            {
                duration = 240;
                wind_effect[j] = 0;
                break;
            }
        }
        else
        {
            start_time = start_time -1;
            if(start_time <=0 )
            {
                start_time = 1000;
                windshift_x = -200 + static_cast<float>(rand())/(static_cast <float> (RAND_MAX/(400)));
                windshift_z = -200 + static_cast<float>(rand())/(static_cast <float> (RAND_MAX/(400)));
                float unit_vec = sqrt(windshift_x*windshift_x + windshift_z*windshift_z);
                windshift_x = windshift_x/unit_vec;
                windshift_z = windshift_z/unit_vec;
                wind_effect[j] = 1;
                wind_accelx = 0.005;
                wind_accelz = 0.005;
                
            }
        }
    }

    temp_x = boat.position.x, temp_z = boat.position.z;
    for(int j=0;j<rock_num;j++)
    {
        rock_halt = 0;
        if(detect_collision(rock[j].bounding_box(),boat.bounding_box()))
        {
            rock_halt = 1;
            health.life_reduce();
            if(health.life <= 0)
            {
                health.life = 2.2;
                lives = lives - 1;
            }
            bounce_back(rock[j].bounding_box(),temp_x,temp_z);
        }

    }

    for(int j=0;j<enemy_num;j++)
    {
        int flag = enemy[j].val;
        if(flag == 1)
        {
            enemy[j].tick();
        }
    }

    if(power_up.treasure_draw == 1)
    {
        power_up.rotation += 1.8;
    }

    if(dragon.val == 1)
    {
        dragon.tick();
    }

    for(int j=0;j<enemy_num;j++)
    {
        controller_enemy(j);
    }

    if(dragon.val != 0)
    {
        controller_dragon();
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // ball1 = Ball(0, 0, COLOR_RED);
    for (int j=0;j< ocean_num;j++)
    {
        float idx = ((float)j)*0.02;
        ocean[j] = Ocean(0,40+idx,0,COLOR_BACKGROUND , INT32_MAX);
        
    } 
    
    boat = Boat(0, 48.12, 0, COLOR_GREEN);
    boat.rotation = 90;

    canon = Canon(0,46.15,3,COLOR_POND);

    for(int j=0;j<waves_num;j++)
    {
        float coord_x = rand()%2000 - 1000;
        float coord_z = rand()%2000 - 600;
        wave[j] = Waves(coord_x,40.12,coord_z, COLOR_WHITE);
    }

    for(int j=0;j<rock_num;j++)
    {
        float coord_x = rand()%2000 - 700;
        float coord_z = rand()%2000 - 1000;
        rock[j] = Rock(coord_x,45.12,coord_z, COLOR_GREY);
    }

    for(int j=0;j<barrel_num;j++)
    {
        float coord_randx = -987 + static_cast<float>(rand())/(static_cast <float> (RAND_MAX/(2593)));
        float coord_randz = -897 + static_cast<float>(rand())/(static_cast <float> (RAND_MAX/(2487)));
        coord_randx += rand()%1500;
        coord_randz += rand()%1700;
        barrel[j] = Barrel(coord_randx,45.12,coord_randz,COLOR_TAN);
    }
   for(int j=0;j<treasure_num;j++)
   {
       if(barrel[j].utility == 0)
       {
           float coord_x = barrel[j].position.x , coord_z = barrel[j].position.z;
           treasure[j] = Treasure(coord_x, barrel[j].position.y + 38, coord_z,5, COLOR_SILVER);
           barrel[j].utility = 1;
       }       
   }
   float tp_enemy[3];
   tp_enemy[2]= 48.12;
   for(int j=0;j<enemy_num;j++)
   {
        *(tp_enemy+0) = rand() % 600 - 300;
        *(tp_enemy+1) = rand() % 600 - 300;
        if (tp_enemy[0] > 0 && tp_enemy[0] < 50) 
            tp_enemy[0] += 50;
        else if (tp_enemy[0] <= 0 && tp_enemy[0] > -50) 
            tp_enemy[0] -= 50;
        // Initial z of boat is 40
        if (tp_enemy[1] > 50 && tp_enemy[1] < 100) 
            tp_enemy[1] += 50;
        else if (tp_enemy[1] <= 50 && tp_enemy[1] > 0) 
            tp_enemy[1] -= 50;
        int clr = rand() % 5;
        enemy[j] = Enemy(tp_enemy[0], tp_enemy[2], tp_enemy[1], color_arr[clr]);
   }

   dragon = Dragon(0,48.12, -68, COLOR_PINK);
   power_up = Treasure(0,84, -48,5, COLOR_CRIMSON);
   power_up.treasure_draw = 0;

   for(int j=0;j<wind_num;j++)
   {
       float coord_x = rand()%1683 - 859;
       float coord_y = rand()%100 + 200.0f;
       float coord_z = rand()%1937 - 973;
       wind[j] = Wind(coord_x, coord_y,coord_z, COLOR_WHITE);
   }
    // wind[0] = Wind(0,50,-3,COLOR_BLACK);
   
    direction = Direction(-8.50f, -8.50f, 0,COLOR_YELLOW);
    health = Health(-7.2f,9.0f,0.0f);
    aurora = Aurora(0,boat.position.y + 5,-20);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BLACK.r / 256.0, COLOR_BLACK.g / 256.0, COLOR_BLACK.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 650;
    int height = 650;

    window = initGLFW(width, height);

    initGL (window, width, height);
    camera_coord[0] = 0 ,camera_coord[1] = 90, camera_coord[2] =100;
    camera_lookup[0] = 0, camera_lookup[1] = 90, camera_lookup[2] = 0;
    /* Draw in loop */

    pid = fork();
    if(pid == 0)
    {
        while(true)
        {
            audio_init();
            audio_play();
            audio_close();
        }
        _exit(0);
    }

    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            camera_mode();

            char str1[30];
            sprintf(str1,"%d", score);
            char final_str[120] = "Score : ";
            strcat(final_str, str1);
            
            char str2[10];
            sprintf(str2,"%d", lives);
            strcat(final_str,"      Lives : ");
            strcat(final_str, str2);
            
            char str3[10];
            sprintf(str3,"%d", booster_time/60);
            strcat(final_str,"      Booster Time Left : ");
            strcat(final_str, str3);

            glfwSetWindowTitle(window, final_str);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void reset_screen()
{
    float top,bottom,left,right;
    top = screen_center_y + 10 / screen_zoom;
    bottom = screen_center_y - 10 / screen_zoom;
    left   = screen_center_x - 10 / screen_zoom;
    right  = screen_center_x + 10 / screen_zoom;
}


bool detect_collision(bounding_box_t a, bounding_box_t b) 
{
    return (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.x - b.x) * 2 < (a.width + b.width)) && 
           (abs(a.z - b.z) * 2 < (a.length + b.length));
}

int rock_collision_decider(const bounding_box_t & temp_rock)
{
    float ds = (temp_rock.x - boat.position.x)*(temp_rock.x - boat.position.x) + (temp_rock.z - boat.position.z)*(temp_rock.z - boat.position.z);
    float radii = (temp_rock.width + 13.0f)*(temp_rock.width + 13.0f);
    if(ds < radii)
    {
        return 1;
    }
    return 0;
}
void bounce_back(const bounding_box_t & temp_rock, float coord_x, float coord_z)
{
    float x1 = coord_x - temp_rock.x;
    float z1 = coord_z - temp_rock.z;
    float unit_vec1 = sqrt(x1*x1 + z1*z1);
    x1 = x1/unit_vec1;
    z1 = z1/unit_vec1;
    boat.position.x += x1*32.0;
    boat.position.z += z1*32.0;
}
void camera_transform()
{
    camera_view = (camera_view+1)%5;
}

void camera_mode()
{
    double theta = (boat.rotation-90.0)*(pi/180.0);
    if (camera_view == 1)  // Follow cam view 
    {
        camera_coord[0] = boat.position.x + 120*sin(theta);
        camera_coord[1] =100;
        camera_coord[2] = boat.position.z + 120*cos(theta);

        camera_lookup[0] = boat.position.x + sin(theta+pi);
        camera_lookup[1] = 100;
        camera_lookup[2] = boat.position.z + cos(theta+pi);
    }
    else if (camera_view == 0) // Boat cam view 
    {
        // printf("gulshan\n");
        camera_coord[0] = boat.position.x + 10*sin(theta);
        camera_coord[1] = boat.position.y + 30;
        camera_coord[2] = boat.position.z + 10*cos(theta);

        camera_lookup[0] = boat.position.x + 1*sin(theta+pi);
        camera_lookup[1] = boat.position.y + 30;
        camera_lookup[2] = boat.position.z + 1*cos(theta+pi);
    }

    else if(camera_view == 3) // top view
    {
        camera_coord[0] = boat.position.x ;
        camera_coord[1] = 200;
        camera_coord[2] = boat.position.z;

        camera_lookup[0] = boat.position.x + 2;
        camera_lookup[1] = boat.position.y;
        camera_lookup[2] = boat.position.z ;
    }

    else if(camera_view == 4) // tower view
    {
        camera_coord[0] = boat.position.x +450;
        camera_coord[1] = 450;
        camera_coord[2] = boat.position.z;

        camera_lookup[0] = boat.position.x;
        camera_lookup[1] = boat.position.y;
        camera_lookup[2] = boat.position.z ;
    }

    else if(camera_view == 2) // Helicam View
    {
        camera_coord[1] = 170;
    }

}

void camera_helicopter(float x_pos, float y_pos)
{
    if(camera_view == 2)
    {
        camera_lookup[0] = boat.position.x +(x_pos - 300);
        if(y_pos < 301)
        {
            camera_lookup[1] = boat.position.y +(300 - y_pos)/2;
        }
    }
}

void camera_zooming(int type)
{
    if(camera_view == 2)
    {
        float tp[4];
        tp[0] = - camera_coord[0] + camera_lookup[0];
        tp[1] = - camera_coord[1] + camera_lookup[1];
        tp[2] = - camera_coord[2] + camera_lookup[2];
        if(type == 1)
        {
            if(camera_coord[2] - 6 > camera_lookup[2])
            {
                camera_coord[2] -= 6;
            }
        }
        else if( type == -1)
        {
            camera_coord[2] += 6;
        }
        camera_coord[0] = tp[0]*(camera_coord[2] - camera_lookup[2])/tp[2]+camera_lookup[2];
        camera_coord[1] = tp[1]*(camera_coord[2] - camera_lookup[2])/tp[2]+camera_lookup[1];
    }
}

void signal_handler()
{
    kill(pid,SIGKILL);
}

void enemy_initiate(int idx) 
{
    int add_sub1 = rand() % 2;
    int add_sub2 = rand() % 2;    
    float enemy_coord[4];
    enemy_coord[0] = boat.position.x;
    enemy_coord[1] = 48.13;
    enemy_coord[2] = boat.position.z;
    
    if (add_sub1 == 1) 
        enemy_coord[0] -= rand() % 600 - 300;
    else if (add_sub1 == 0) 
        enemy_coord[0] += rand() % 600 - 300;

    if (add_sub2 == 1) 
       enemy_coord[2] -= rand() % 600 - 300;
    else if (add_sub2 == 0) 
       enemy_coord[2] += rand() % 300 - 300;

    float xdis = enemy_coord[0] - boat.position.x;
    float zdis = enemy_coord[2] - boat.position.z;

    if (xdis > -50 && xdis < 0) 
        enemy_coord[0] -= 50;
    else if (xdis < 50 && xdis > 0) 
        enemy_coord[0] += 50;

    if (zdis >= -49.9 && zdis <= -0.1) 
       enemy_coord[2] -= 50;
    else if (zdis <= 49.98 && zdis >= 0.01) 
       enemy_coord[2] += 50;    
    
    enemy[idx].set_position(enemy_coord[0],enemy_coord[1],enemy_coord[2]);

    enemy[idx].val =1;
    if (add_sub1 == 1) 
    {
        float tp_rot =  90 + rand() % 360;
        enemy[idx].rotation = tp_rot;
    }
    else 
    {
        float tp_rot =  90 - rand() % 360;
        enemy[idx].rotation = tp_rot;
    }
}

void dragon_reinitialize() 
{
    int add_sub1 = rand() % 2;
    int add_sub2 = rand() % 2;    
    float dragon_cord[4];
    dragon_cord[0] = boat.position.x;
    dragon_cord[1] = 48.13;
    dragon_cord[2] = boat.position.z;
    
    if (add_sub1 == 1) 
        dragon_cord[0] -= rand() % 600 - 300;
    else if (add_sub1 == 0) 
        dragon_cord[0] += rand() % 600 - 300;

    if (add_sub2 == 1) 
       dragon_cord[2] -= rand() % 600 - 300;
    else if (add_sub2 == 0) 
       dragon_cord[2] += rand() % 300 - 300;

    float xdis = dragon_cord[0] - boat.position.x;
    float zdis = dragon_cord[2] - boat.position.z;

    if (xdis > -50 && xdis < 0) 
        dragon_cord[0] -= 50;
    else if (xdis < 50 && xdis > 0) 
        dragon_cord[0] += 50;

    if (zdis >= -49.9 && zdis <= -0.1) 
       dragon_cord[2] -= 50;
    else if (zdis <= 49.98 && zdis >= 0.01) 
       dragon_cord[2] += 50;    
    
    dragon.set_position(dragon_cord[0],dragon_cord[1],dragon_cord[2]);

    dragon.val = 1;
    if (add_sub1 != 0) 
    {
        float tp_rot =  90 + rand() % 360;
        dragon.rotation = tp_rot;
    }
    else 
    {
        float tp_rot =  90 - rand() % 360;
        dragon.rotation = tp_rot;
    }
}

void canon_initiate()
{
    canon.release =0;
    canon.params[0]= 0;
    canon.params[4] = 0;
    canon.position.x = boat.position.x;
    canon.position.y = boat.position.y - 1.0f;
    canon.position.z = boat.position.z;
}

void controller_enemy(int idx)
{
    float max_dis = 500.0*500.0;
    float tp_cord[4], unit_vec;
    tp_cord[0] = boat.position.x - enemy[idx].position.x;
    tp_cord[1] = boat.position.y - enemy[idx].position.y;
    tp_cord[2] = boat.position.z - enemy[idx].position.z;
    unit_vec = (tp_cord[0]*tp_cord[0] + tp_cord[1]*tp_cord[1] + tp_cord[2]*tp_cord[2]);
    if(max_dis <= unit_vec)
    {
        enemy_initiate(idx);
    }
}

void controller_dragon()
{
    float max_dis = 500.0*500.0;
    float tp_cord[4], unit_vec;
    tp_cord[0] = boat.position.x - dragon.position.x;
    tp_cord[1] = boat.position.y - dragon.position.y;
    tp_cord[2] = boat.position.z - dragon.position.z;
    unit_vec = (tp_cord[0]*tp_cord[0] + tp_cord[1]*tp_cord[1] + tp_cord[2]*tp_cord[2]);
    if(max_dis <= unit_vec)
    {
        dragon_reinitialize();
    }
}

void change_weather()
{
    weather_change = (weather_change + 1)%2;
}

glm::mat4 ortho_projection()
{
    float top,bottom,left,right;
    top = screen_center_y + 10 / screen_zoom;
    bottom = screen_center_y - 10 / screen_zoom;
    left   = screen_center_x - 10/ screen_zoom;
    right  = screen_center_x + 10 / screen_zoom;
    glm::mat4 projection_static = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    glm::mat4 view_static = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 VPstatic = projection_static * view_static;
    return VPstatic;
}

void change_weapon()
{
    weapon_change = (weapon_change + 1)%2;
}


