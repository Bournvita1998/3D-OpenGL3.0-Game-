#include "main.h"
#include "timer.h"
#include "cube.h"
#include "pool.h"
#include "rock.h"
#include "aim.h"
#include "sail.h"
#include "monster.h"
#include "Rectangle.h"
#include "person.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

float screen_zoom = 1;
float screen_center_x = 0;
float screen_center_y = 0;
float gravity = 0.5;
float level = 3;
float pi=3.141;
int score = 0;
float camera_x=0;
float camera_y=90;
float camera_z=100;
float target_x=0;
float target_y=90;
float target_z=0;

Rock cannon,blast;
Monster monster[100];
Aim aim;
Rock rocks[100];
Rectangle island;
Sail sail;
Cube boat;
Pool pool;
person Man;

int rockCount = 100;
int monsterCount = 100;
int view = 1;
int time_cnt = 0;
int time_blast = 0;

void change_camera(),speed_camera();

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
    // glm::vec3 eye ( 0, -5, 2 );
    glm::vec3 eye(camera_x, camera_y, camera_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 0, 1);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    pool.draw(VP);
    blast.draw(VP);
    int i=0,l = rockCount;

    while(i<l)
    {
        monster[i].draw(VP);
        i++;
    }
    i=0;
    while(i<l)
    {
        rocks[i].draw(VP);
        i++;
    }  
    island.draw(VP);
    Man.draw(VP);
    aim.draw(VP);
    cannon.draw(VP);
    boat.draw(VP);
    sail.draw(VP);
}

void tick_input(GLFWwindow *window) {


    float sine = boat.speed*sin(boat.rotation*M_PI/180.0f);
    float cosine = boat.speed*cos(boat.rotation*M_PI/180.0f);
    float ang_h_sin = sin(aim.rotation_h*M_PI/180);
    float ang_h_cos = cos(aim.rotation_h*M_PI/180);
    float ang_z_sin = sin(aim.rotation_z*M_PI/180);
    float ang_z_cos = cos(aim.rotation_z*M_PI/180);


    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    if (down) {

        int flag = 0;
        int i = 0;
        int l = rockCount;

        boat.position.x = boat.position.x + sine;
        boat.position.y = boat.position.y - cosine;

        while(i<l)
            if (detect_collision(boat.bounding_box(),rocks[i].bounding_box()) && rocks[i].position.z != -1000) 
            {
                flag = 1;
                break;
            }
            else
                i++;

        if (flag != 0)
        {
            boat.position.x = boat.position.x - sine;
            boat.position.y = boat.position.y + cosine;
        }
        else
        {
            aim.position.y = boat.position.y;        
            aim.position.x = boat.position.x;
            sail.position.y = boat.position.y;        
            sail.position.x = boat.position.x;
            pool.position.y = boat.position.y;

            float ax = cannon.position.x;
            float az = cannon.position.z;
            float bx = boat.position.x;
            float bz = boat.position.z;

            if (az == bz)
            {
                ax = bx;
                cannon.position.y = boat.position.y;        
            }
        }       
    }

    int up = glfwGetKey(window, GLFW_KEY_UP);

    if (up) {

        int flag = 0;
        int i = 0;
        int l = rockCount;

        boat.position.x = boat.position.x - boat.speed*sine;
        boat.position.y = boat.position.y + boat.speed*cosine;

        while(i<l) 
            if (detect_collision(boat.bounding_box(),rocks[i].bounding_box()) && rocks[i].position.z != -1000) 
            {
                flag = 1;
                break;
            }
            else
                i++;

        if (flag != 0) 
        {
            boat.position.x = boat.position.x + sine;
            boat.position.y = boat.position.y - cosine;
        }                
        else {
            aim.position.y = boat.position.y;        
            aim.position.x = boat.position.x;
            sail.position.y = boat.position.y;        
            sail.position.x = boat.position.x;
            pool.position.y = boat.position.y;

            float ax = cannon.position.x;
            float az = cannon.position.z;
            float bx = boat.position.x;
            float bz = boat.position.z;

            if (az == bz)
            {
                ax = bx;
                cannon.position.y = boat.position.y;        
            }
        }
    }

    int right = glfwGetKey(window, GLFW_KEY_RIGHT);

    if (right) {

        int i = 0,l = rockCount,flag = 0;

        while(i<l)
            if (detect_collision(boat.bounding_box(),rocks[i].bounding_box()) && rocks[i].position.z != -1000) 
            {
                flag = 1;
                break;
            }
            else
                i++;

        if (flag == 0) 
        {
            cannon.rotation -= 5;
            aim.rotation_z -= 5;
            boat.rotation -= 5;
        }
    }

    int left  = glfwGetKey(window, GLFW_KEY_LEFT);

    if (left) {

        int i = 0,l = rockCount,flag = 0;

        while(i<l)
            if (detect_collision(boat.bounding_box(),rocks[i].bounding_box()) && rocks[i].position.z != -1000) {
                flag = 1;
                break;
            }
            else
                i++;

        if (flag == 0) {
            cannon.rotation += 5;
            aim.rotation_z += 5;
            boat.rotation += 5;
        }
    }

    int camera = glfwGetKey(window, GLFW_KEY_C);

    if (time_cnt > 30)
        if (camera)
        {
            change_camera();
            time_cnt = 0;
        }

    int fire = glfwGetKey(window, GLFW_KEY_F);

    if (cannon.position.z == boat.position.z && aim.rotation_h > 3 && time_blast == 0)
        if (fire) 
        {
            cannon.launch_speed = 10 * ang_h_sin;
            cannon.launch_speed_x = -10 * ang_h_cos * ang_z_sin;
            cannon.launch_speed_y = 10 * ang_h_cos * ang_z_cos;
        }

    int jump = glfwGetKey(window, GLFW_KEY_SPACE);

    if (boat.position.z == level)
        if (jump) 
        {
            boat.launch_speed = 6;
            cannon.launch_speed =  6;
            aim.launch_speed = 6;
        }
}

void tick_elements() {
    boat.tick();
    // printf("%lf  %lf  %lf",boat.position.x,boat.position.y,boat.position.z);
    // camera_rotation_angle += 1;
    boat.position.z = boat.position.z + boat.launch_speed;
    cannon.position.z = cannon.position.z + cannon.launch_speed;
    cannon.position.x = cannon.position.x + cannon.launch_speed_x;
    cannon.position.y = cannon.position.y + cannon.launch_speed_y;
    aim.position.z = aim.position.z + aim.launch_speed;




    // island = Rectangle(320,320, 100,100,COLOR_BLAST);
    // Man = person(370,370,10, 10,10,10 , COLOR_RED);




    if(boat.position.x > 300 && boat.position.x < 440 && boat.position.y > 300 && boat.position.y < 440 )
    {
            int w = glfwGetKey(window, GLFW_KEY_W);
            int s = glfwGetKey(window, GLFW_KEY_S);
            int a = glfwGetKey(window, GLFW_KEY_A);
            int d = glfwGetKey(window, GLFW_KEY_D);

            if(w){
                if(Man.position.x < 310 && Man.position.x > 430 && Man.position.y < 310 && Man.position.y > 430)
                    Man.position.y += 0;
                else
                    Man.position.y += 1;
            }
            if(s){
                if(Man.position.x < 310 && Man.position.x > 430 && Man.position.y < 310 && Man.position.y > 430)
                    Man.position.y -= 0;
                else
                    Man.position.y -= 1;
            }
            if(a){
                if(Man.position.x < 310 && Man.position.x > 430 && Man.position.y < 310 && Man.position.y > 430)
                    Man.position.x -= 0;
                else
                    Man.position.x -= 1;
            }
            if(d){
                if(Man.position.x < 310 && Man.position.x > 430 && Man.position.y < 310 && Man.position.y > 430)
                    Man.position.x += 0;
                else
                    Man.position.x += 1;
            }
    }







    if (boat.position.z > level || cannon.position.z > level) 
    {
        boat.launch_speed = boat.launch_speed - gravity;
        cannon.launch_speed = cannon.launch_speed - gravity;
        aim.launch_speed = aim.launch_speed - gravity;
    }

    if (boat.position.z <= level) 
    {
        boat.launch_speed = 0;
        boat.position.z = level;
        aim.launch_speed = boat.launch_speed;
        aim.position.z = boat.position.z;
    }

    if (cannon.position.z <= level) {

        cannon.launch_speed = 0;
        cannon.launch_speed_x = cannon.launch_speed;
        cannon.launch_speed_y = cannon.launch_speed;
        
        int flag =0;
        
        if (cannon.position.x != boat.position.x)
            if(cannon.position.y != boat.position.y)
                flag = 1;

        float tempx = cannon.position.x;
        float tempy = cannon.position.y;

        cannon.position.x = boat.position.x;
        cannon.position.y = boat.position.y;

        cannon.position.z = level;

        if(flag == 1)
        {
            time_blast = 1;
            blast.position.x = tempx;
            blast.position.y = tempy;
        }
    }

    float sin_ang = sin(boat.rotation*pi/180);
    float cos_ang = cos(boat.rotation*pi/180);

    switch(view)
    {
        case 0 : camera_z = 50;
                break;
        case 1 : camera_z = 50;
                 camera_x = boat.position.x + 100*sin_ang;
                 camera_y = boat.position.y - 100*cos_ang;

                 target_x = boat.position.x;
                 target_y = boat.position.y;
                 target_z = boat.position.z;
                 break;

        case 2 : target_x = boat.position.x;
                 target_y = boat.position.y;
                 target_z = boat.position.z;
                 camera_x = boat.position.x;
                 camera_x += 1;
                 camera_y = boat.position.y;
                 camera_z = boat.position.z;
                 camera_z += 300;
                 break;

        case 3 : camera_z = 25;
                 camera_x = boat.position.x;
                 camera_y = boat.position.y;
                 
                 target_x = boat.position.x-40*sin_ang;
                 target_y = boat.position.y+40*cos_ang;
                 target_z = boat.position.z+25;
                 break;

        case 4 : camera_z = 50;
                 camera_x = boat.position.x;
                 camera_x += 100;
                 camera_y = boat.position.y;
                 
                 target_x = boat.position.x;
                 target_y = boat.position.y;
                 target_z = boat.position.z;
                 break;
    }

    time_cnt ++;
    sail.position.z = boat.position.z;

    if (time_blast > 60)
    {
        blast.position.x = -1000;
        blast.position.y = -1000;
        blast.size = 25;
        time_blast = 0;
    }
    int i = 0, l = rockCount,nope =0 ;
    while (i<l)
    {
        if(detect_collision(blast.bounding_box(),rocks[i].bounding_box())){
            rocks[i].position.z = -1000;
            nope = 1;
        }
        i++;
    }
    if(nope == 1)
        score += 50;

    i = 0, l = monsterCount;
    nope = 0;
    while (i<l)
    {
        if(detect_collision(blast.bounding_box(),monster[i].bounding_box())){
            monster[i].position.z = -1000;
            nope =1;
        }
        i++;
    }
    if(nope == 1)
        score += 100;

    if (time_blast > 0) 
    {
        time_blast ++;
        blast.size -= 0.35;
    }
    else
        i=0;
        //        continue;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    boat = Cube(0, 0, COLOR_RED);
    pool = Pool(0,0, COLOR_BLUE);
    boat.position.z = boat.position.z + level;
    pool.position.z = pool.position.z - 32767;

    int i=0,l = rockCount;

    while(i<l) 
    {
        rocks[i] = Rock(((((i+1)*rand()+i*584)%10000)/10  )+30 , ((((i+1)*rand()+i*784)%10000)/10  )+30, COLOR_BLACK);
        rocks[i].position.z = rocks[i].position.z + 1;
        rocks[i].size = i%5 * 5;
        i++;
    }

    i=0;
    l = monsterCount;

    while(i<l) 
    {
        monster[i] = Monster(((((i+1)*rand()+i*584)%10000)/10) + 50 , ((((i+1)*rand()+i*784)%10000)/10) + 50, COLOR_RED);
        monster[i].position.z += monster[i].position.z + 1;
        monster[i].size = 10;
        i++;
    }

    island = Rectangle(320,320, 100,100,COLOR_BLAST);
    Man = person(370,370,10, 10,10,10 , COLOR_RED);
    aim = Aim(0, 0, COLOR_RED);
    aim.position.z = aim.position.z + level;
    cannon = Rock(boat.position.x,boat.position.y,COLOR_RED);
    blast = Rock(-1000,-1000,COLOR_BLAST);
    blast.size = 25;
    cannon.position.z = cannon.position.z + level;
    blast.position.z = blast.position.z - blast.size/2;
    sail = Sail(boat.position.x,boat.position.y,COLOR_BACKGROUND);
    sail.position.z = sail.position.z + level;
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
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
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            char outsc[100];
            sprintf(outsc,"Score = %d",score);
            glfwSetWindowTitle(window,outsc);
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void heli_camera(float x, float y){
    if(view == 0) {
        target_x = boat.position.x;
        target_x += (x-300)/2;
        if(y<=300){
            target_y = boat.position.y;
            target_y += (300-y)/2;
        }
    }
}

void change_camera(){ view = (view+1)%5; }

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    float temp1 = sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
    float temp2 = a.width+b.width;
    return (temp1 < temp2);
}

void reset_screen() {
    float var = 15 / screen_zoom;
    float top    = screen_center_y + var;
    float bottom = screen_center_y - var;
    float left   = screen_center_x - var;
    float right  = screen_center_x + var;
    Matrices.projection = glm::perspective(45.0f,1.0f,50.0f, 500.0f);
}

void cannon_pos(float x, float y) {
    
    if (view == 1 || view == 2 || view == 3 || view == 4) 
    {
        aim.rotation_z = boat.rotation;
        aim.rotation_z -= (3*x/5) - 180;
        aim.rotation_h = -(3*y/20) + 90;
    }
}
