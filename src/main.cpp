#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "fireline.h"
#include "coin.h"
#include "waterball.h"
#include "propulsion.h"
#include "magnet.h"
#include "firebeam.h"
#include "ring.h"
#include <iostream>
#define INF 999999999
#define pb push_back

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
void detect_collisions();
float dist(float a, float b, float c, float d);

Ball ball;
Platform platform;
vector <Magnet> magnets;
vector <Firebeam> firebeams;
vector <Coin> coins;
vector <Fireline> firelines;
vector <Waterball> waterballs;
vector <Propulsion> gas;
Ring ring;
bounding_box_t b;
color_t COLOR_BALL = {255, 255, 255}, COLOR_PLATFORM = {0, 153, 153}, COLOR_COIN = {255, 255, 102}, COLOR_FIRE = {255, 128, 0}, COLOR_WATER = {0, 128, 255}, COLOR_PROPULSION = {255, 255, 255}, COLOR_MAGNET = {238, 5, 52};

int NO_OF_FIRELINES = 10, NO_OF_COINS = 15, NO_OF_WBALLS = 0, delay = 40, NO_OF_GAS = 0, NO_OF_FIREBEAMS = 8, NO_OF_MAGNETS = 2;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

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
    glm::vec3 eye ( 0, 0, 3 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 11, 0);

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
    ball.draw(VP);

    platform.draw(VP);
    
    for (int i=0; i<NO_OF_COINS; ++i) {
        if (coins[i].position.x != INF)
            coins[i].draw(VP);
    }
    
    for (int i=0; i<NO_OF_FIRELINES; ++i) {
        if (firelines[i].position.x != INF)
            firelines[i].draw(VP);
    }
    
    for (int i=0; i<NO_OF_WBALLS; ++i) {
        if (waterballs[i].position.x != INF)
            waterballs[i].draw(VP);
    }
    
    for (int i=0; i<NO_OF_GAS; ++i) {
        if (gas[i].position.y != INF)
            gas[i].draw(VP);
    }
    
    for (int i=0; i<NO_OF_MAGNETS; ++i) {
        if (magnets[i].position.x > -3.8 && magnets[i].position.x < 3.8)
            magnets[i].draw(VP);
    }
    
    for (int i=0; i<NO_OF_FIREBEAMS; ++i) {
        if (firebeams[i].position.x != INF)
            firebeams[i].draw(VP);
    }

    ring.draw(VP);

}

void tick_elements(bool dir) {

    for (int i=0; i<NO_OF_FIREBEAMS; ++i) {
        if (firebeams[i].position.x != INF)
            firebeams[i].tick(dir);
    }
    
    for (int i=0; i<NO_OF_COINS; ++i) {
        if (coins[i].position.x != INF)
            coins[i].tick(dir);
    }

    for (int i=0; i<NO_OF_FIRELINES; ++i) {
        if (firelines[i].position.x != INF)
            firelines[i].tick(dir);
    }

    ring.tick(dir);

    for (int i=0; i<NO_OF_MAGNETS; ++i) {
        magnets[i].tick();
        if (magnets[i].position.x > -3.8 && magnets[i].position.x < 3.8) {
            float diffx, diffy;
            diffx = ball.position.x - magnets[i].position.x;
            diffy = ball.position.y - magnets[i].position.y;
            if (diffx > 0) {
                ball.tick(DIR_LEFT);
            }
            if (diffx < 0) {
                ball.tick(DIR_RIGHT);
            }
            if (diffy > 0) {
                ball.tick(DIR_DOWN);
            }
            if (diffy < 0) {
                ball.tick(DIR_UP);
            }
        }
    }

    // camera_rotation_angle += 1;
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_W);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    
    if (left) {
        if (ball.position.x <= -3.78)
            tick_elements(0);
        else ball.tick(DIR_LEFT);
    }

    if (right) {
        if (ball.position.x >= 3.78)
        {
            ball.position.x = 0;
            for (int i=0; i<60; ++i)
                tick_elements(1);
        }
        else
        {
            ball.tick(DIR_RIGHT);
            if (ball.position.x > 0)
                tick_elements(1);
        }
    }
    
    if (up) {
        float x, y, delta;
        
        y = ball.position.y - ball.b.height/2.0;
        delta = -25.0 + rand() % 50;
        x = ball.position.x + ball.b.width*(delta/100.0);
        gas.pb(Propulsion(x, y, COLOR_PROPULSION));
        
        y = ball.position.y - ball.b.height/2.0;
        delta = -25.0 + rand() % 50;
        x = ball.position.x + ball.b.width*(delta/100.0);
        gas.pb(Propulsion(x, y, COLOR_PROPULSION));
        
        NO_OF_GAS += 2;
        ball.tick(DIR_UP);
    }
    
    if (space) {
        if (delay >= 40) {
            waterballs.pb(Waterball(ball.position.x, ball.position.y, COLOR_WATER));
            NO_OF_WBALLS++;
            delay = 0;
        }
    }
    ++delay;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball = Ball(0, -1.5, COLOR_BALL);

    platform = Platform(0, -2, COLOR_PLATFORM);
    
    for (int i=0, x, y; i<NO_OF_COINS; ++i) {
        x = 5 + rand() % 50;
        y = -1 + rand() % 5;
        coins.pb(Coin(x, y, COLOR_COIN));
    }
    
    for (int i=0, x, y; i<NO_OF_FIRELINES; ++i) {
        float len = 1.5 + rand() % 2;
        float rotation = rand() % 180;
        x = 5 + rand()%50;
        y = -1 + rand() % 5;
        firelines.pb(Fireline(x, y, rotation, len, COLOR_FIRE));
    }
    
    for (int i=0; i<NO_OF_MAGNETS; ++i) {
        magnets.pb(Magnet(rand() % 50, -2 + rand() % 5, COLOR_MAGNET, rand() % 2));
    }
    
    for (int i=0, x, y; i<NO_OF_FIREBEAMS; i+=2) {
        float len = 1.5 + rand() % 2;
        x = 5 + rand() % 50;
        y = -1;
        firebeams.pb(Firebeam(x, y, len, COLOR_FIRE, 0));
        firebeams.pb(Firebeam(x, y + 1, len, COLOR_FIRE, 1));   
    }

    ring = Ring(5 + rand() % 50, -1 + rand() % 5, COLOR_WATER);
    cout << ring.position.x << " " << ring.position.y << endl;

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
    int height = 500;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            reset_screen();

            detect_collisions();

            ball.tick(DIR_DOWN);
            
            for (int i=0; i<NO_OF_WBALLS; ++i) {
                if (waterballs[i].position.x != INF) 
                    waterballs[i].tick();
            }

            for (int i=0; i<NO_OF_GAS; ++i) {
                if (gas[i].position.y != INF)
                    gas[i].tick();
            }

            for (int i=0; i<NO_OF_FIREBEAMS; i++) {
                firebeams[i].position.y += firebeams[i].speed_y;
                if ((i & 1) && (firebeams[i].position.y > 3.5 || firebeams[i].position.y < 0))
                    firebeams[i].speed_y *= -1;
                if (!(i & 1) && (firebeams[i].position.y > 2.5 || firebeams[i].position.y < -1.5))
                    firebeams[i].speed_y *= -1;
            }

            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void detect_collisions() {

    // ball and coins
    for (int i=0; i<NO_OF_COINS; ++i) {
        if ((2 * abs(ball.b.x - coins[i].b.x) < (ball.b.width + coins[i].b.width)) 
            && (2 * abs(ball.b.y - coins[i].b.y) < (ball.b.height + coins[i].b.height))) {
            coins[i].position.x = INF;
        }
    }

    // ball and fire
    for (int i=0; i<NO_OF_FIRELINES; ++i) {
    	float delta = firelines[i].length*cos(firelines[i].rotation*M_PI/180.0);
    	float x1, x2, y1, y2;
    	x1 = firelines[i].position.x;
    	y1 = firelines[i].position.y;
    	x2 = firelines[i].position.x + delta;
    	y2 = firelines[i].position.y + firelines[i].length*sin(firelines[i].rotation*M_PI/180.0);
    	bool z = (abs(dist(x1, y1, ball.b.x, ball.b.y) + dist(x2, y2, ball.b.x, ball.b.y) - firelines[i].length) <= 0.1);
    	if (z) {
    		firelines[i].position.x = INF;
    		ball.b.x = ball.position.x = -3.0;
    		ball.b.y = ball.position.y = 0;
    	}
    }

    for (int i=0; i<NO_OF_FIREBEAMS; ++i) {
        float delta = firebeams[i].length*cos(firebeams[i].rotation*M_PI/180.0);
        float x1, x2, y1, y2;
        x1 = firebeams[i].position.x;
        y1 = firebeams[i].position.y;
        x2 = firebeams[i].position.x + delta;
        y2 = firebeams[i].position.y + firebeams[i].length*sin(firebeams[i].rotation*M_PI/180.0);
        bool z = (abs(dist(x1, y1, ball.b.x, ball.b.y) + dist(x2, y2, ball.b.x, ball.b.y) - firebeams[i].length) <= 0.1);
        if (z) {
            firebeams[i].position.x = INF;
            ball.b.x = ball.position.x = -3.0;
            ball.b.y = ball.position.y = 0;
        }
    }

    // water balloons and fire
    for (int i=0; i<NO_OF_WBALLS; ++i) {
        if (waterballs[i].position.x == INF) continue;
        for (int j=0; j<NO_OF_FIRELINES; ++j) {
            if (firelines[j].position.x == INF) continue;
            float delta = firelines[j].length*cos(firelines[j].rotation*M_PI/180.0);
            float x1, x2, y1, y2;
            x1 = firelines[j].position.x;
            y1 = firelines[j].position.y;
            x2 = firelines[j].position.x + delta;
            y2 = firelines[j].position.y + firelines[j].length*sin(firelines[j].rotation*M_PI/180.0);
            bool z = (abs(dist(x1, y1, waterballs[i].b.x, waterballs[i].b.y) + dist(x2, y2, waterballs[i].b.x, waterballs[i].b.y) - firelines[j].length) <= 0.01);
            if (z) {
                firelines[j].position.x = INF;
                waterballs[i].position.x = INF;
            }
        }

        for (int j=0; j<NO_OF_FIREBEAMS; ++j) {
            if (firebeams[j].position.x == INF) continue;
            float delta = firebeams[j].length*cos(firebeams[j].rotation*M_PI/180.0);
            float x1, x2, y1, y2;
            x1 = firebeams[j].position.x;
            y1 = firebeams[j].position.y;
            x2 = firebeams[j].position.x + delta;
            y2 = firebeams[j].position.y + firebeams[j].length*sin(firebeams[j].rotation*M_PI/180.0);
            bool z = (abs(dist(x1, y1, waterballs[i].b.x, waterballs[i].b.y) + dist(x2, y2, waterballs[i].b.x, waterballs[i].b.y) - firebeams[j].length) <= 0.01);
            if (z) {
                firebeams[j].position.x = INF;
                waterballs[i].position.x = INF;
            }
        }
    }

}

float dist(float a, float b, float c, float d) {
	return sqrt((a-c)*(a-c) + (b-d)*(b-d));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
