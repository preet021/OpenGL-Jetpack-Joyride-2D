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
#include "boomerang.h"
#include "score.h"
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
void display_score();

Ball ball;
Platform platform;
Boomerang boom;
Magnet magnet;
vector <Score> scr;
vector <Firebeam> firebeams;
vector <Coin> coins;
vector <Fireline> firelines;
vector <Waterball> waterballs;
vector <Propulsion> gas;
vector<Ring> rings;
bounding_box_t b;
color_t COLOR_BALL = {255, 255, 255}, COLOR_PLATFORM = {0, 153, 153}, COLOR_COIN = {255, 255, 102}, COLOR_FIRE = {255, 128, 0}, COLOR_WATER = {0, 128, 255}, COLOR_PROPULSION = {255, 255, 255}, COLOR_MAGNET = {238, 5, 52}, COLOR_RING = {220, 239, 157}, COLOR_BOOM = {243, 46 ,46}, COLOR_COIN1 = {20, 200, 20};

int NO_OF_FIRELINES = 5, NO_OF_COINS = 10, NO_OF_WBALLS = 0, delay = 40, NO_OF_GAS = 0, NO_OF_FIREBEAMS = 4, NO_OF_MAGNETS = 2, NO_OF_RINGS = 2, NO_OF_BOOM = 3, score = 0, lives_remaining = 5;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, camera_rotation_angle = 0, cx, cy, r;
bool onRing = 0;
int ii = 0, ind;

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
    
    if (magnet.present)
        magnet.draw(VP);
    
    for (int i=0; i<NO_OF_FIREBEAMS; ++i) {
        if (firebeams[i].position.x != INF)
            firebeams[i].draw(VP);
    }

    for (int i=0; i<NO_OF_RINGS; ++i) {
        rings[i].draw(VP);
    }

    if (boom.present)
        boom.draw(VP);

    for (int i=0; i<(int)scr.size(); ++i) {
        scr[i].draw(VP);
    }

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

    for (int i=0; i<NO_OF_RINGS; ++i) {
        rings[i].tick(dir);
    }

    // camera_rotation_angle += 1;
}

void tick_input(GLFWwindow *window) {

    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_W);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);

    if (!onRing)
        ball.tick(DIR_DOWN);
        
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
    
    if (onRing)
        ball.position.y = rings[ind].position.y + sqrt(abs(rings[ind].radius*rings[ind].radius - (ball.position.x-rings[ind].position.x)*(ball.position.x-rings[ind].position.x)));
    
    if (boom.present)
        boom.tick();
    
    if (magnet.present) {
        if (magnet.direction) {
            if (ball.position.x > magnet.position.x) {
                ball.position.x -= 0.02f;
                if (ball.position.x < magnet.position.x)
                    ball.position.x = magnet.position.x;
                if (ball.position.y > magnet.position.y) {
                    ball.position.y = (ball.position.y - 0.06 >= magnet.position.y) ? (ball.position.y - 0.06) : (magnet.position.y);
                } else {
                    ball.position.y = (ball.position.y + 0.06 <= magnet.position.y) ? (ball.position.y + 0.06) : (magnet.position.y);
                }
            }
        } else {
            if (ball.position.x < magnet.position.x) {
                ball.position.x += 0.02f;
                if (ball.position.x > magnet.position.x)
                    ball.position.x = magnet.position.x;
                if (ball.position.y > magnet.position.y) {
                    ball.position.y = (ball.position.y - 0.06 >= magnet.position.y) ? (ball.position.y - 0.06) : (magnet.position.y);
                } else {
                    ball.position.y = (ball.position.y + 0.06 <= magnet.position.y) ? (ball.position.y + 0.06) : (magnet.position.y);
                }
            }
        }
        magnet.tick();
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball = Ball(0, -1.5, COLOR_BALL);

    platform = Platform(0, -2, COLOR_PLATFORM);
    
    for (int i=0, x, y, t; i<NO_OF_COINS; ++i) {
        x = 5 + rand() % 50;
        y = -1 + rand() % 5;
        color_t c;
        t = rand() % 2;
        if (!t) c = COLOR_COIN;
        else c = COLOR_COIN1;
        coins.pb(Coin(x, y, c, t));
    }
    
    for (int i=0, x, y; i<NO_OF_FIRELINES; ++i) {
        float len = 1.5 + rand() % 2;
        float rotation = rand() % 180;
        x = 5 + rand()%50;
        y = -1 + rand() % 5;
        firelines.pb(Fireline(x, y, rotation, len, COLOR_FIRE));
    }
    
    magnet = Magnet(COLOR_MAGNET);
    
    for (int i=0, x, y; i<NO_OF_FIREBEAMS; i+=2) {
        float len = 1.5 + rand() % 2;
        x = 5 + rand() % 50;
        y = -1;
        firebeams.pb(Firebeam(x, y, len, COLOR_FIRE, 0));
        firebeams.pb(Firebeam(x, y + 1, len, COLOR_FIRE, 1));
    }

    for (int i=0; i<NO_OF_RINGS; ++i) {
        rings.pb(Ring(5 + rand() % 50, -1 + rand() % 3, COLOR_RING));
    }

    boom = Boomerang(COLOR_BOOM);

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

            if ((rand() % 1007 == 53) && !boom.present && NO_OF_BOOM > 0) {
                NO_OF_BOOM--;
                boom.present = true;
                boom.position.y = 2.5;
                boom.position.x = boom.cx + ((boom.position.y - boom.cy)*(boom.position.y - boom.cy));
            }

            if ((rand() % 2007 == 97) && !magnet.present && NO_OF_MAGNETS > 0) {
                NO_OF_MAGNETS--;
                magnet.present = true;
                magnet.position.x = -3 + rand() % 6;
                magnet.position.y = -1.5 + rand() % 5;
                magnet.ctime = 0;
                magnet.direction = rand() % 2;
            }

            if (lives_remaining == 0)
                break;

            display_score();
            
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    cout << "----------------Game Over---------------\n";
    cout << "Final Score: " << score + lives_remaining << endl;

    quit(window);
}

void detect_collisions() {

    // ball and coins
    for (int i=0; i<NO_OF_COINS; ++i) {
        if (coins[i].position.x == INF) continue;
        if ((2 * abs(ball.b.x - coins[i].b.x) < (ball.b.width + coins[i].b.width)) 
            && (2 * abs(ball.b.y - coins[i].b.y) < (ball.b.height + coins[i].b.height))) {
            if (!coins[i].type) ++score;
            else score += 3;
            coins[i].position.x = INF;
        }
    }

    // ball and fire
    for (int i=0; i<NO_OF_FIRELINES; ++i) {
        if (firelines[i].position.x == INF) continue;
        float delta = firelines[i].length*cos(firelines[i].rotation*M_PI/180.0);
        float x1, x2, y1, y2;
        x1 = firelines[i].position.x;
        y1 = firelines[i].position.y;
        x2 = firelines[i].position.x + delta;
        y2 = firelines[i].position.y + firelines[i].length*sin(firelines[i].rotation*M_PI/180.0);
        bool z = (abs(dist(x1, y1, ball.b.x, ball.b.y) + dist(x2, y2, ball.b.x, ball.b.y) - firelines[i].length) <= 0.1);
        if (z) {
            lives_remaining--;
            firelines[i].position.x = INF;
            ball.b.x = ball.position.x = -3.0;
            ball.b.y = ball.position.y = 0;
        }
    }

    for (int i=0; i<NO_OF_FIREBEAMS; ++i) {
        if (firebeams[i].position.x == INF) continue;
        float delta = firebeams[i].length*cos(firebeams[i].rotation*M_PI/180.0);
        float x1, x2, y1, y2;
        x1 = firebeams[i].position.x;
        y1 = firebeams[i].position.y;
        x2 = firebeams[i].position.x + delta;
        y2 = firebeams[i].position.y + firebeams[i].length*sin(firebeams[i].rotation*M_PI/180.0);
        bool z = (abs(dist(x1, y1, ball.b.x, ball.b.y) + dist(x2, y2, ball.b.x, ball.b.y) - firebeams[i].length) <= 0.1);
        if (z) {
            --lives_remaining;
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

    // check if ball is on any ring
    for (int i=0; i<NO_OF_RINGS; ++i) {
        bool a, b;
        cx = rings[i].position.x, cy = rings[i].position.y, r = rings[i].radius + rings[i].thickness / 2.0;
        a = (abs(dist(ball.position.x, ball.position.y, rings[i].position.x, rings[i].position.y) - rings[i].radius - rings[i].thickness) <= 0.1);
        b = ((ball.position.y >= rings[i].position.y) && (ball.position.y <= rings[i].position.y + rings[i].radius + rings[i].thickness / 2.0));
        if (a && b) {
            ball.position.y = cy + sqrt(abs(r*r - (ball.position.x-cx)*(ball.position.x-cx)));
            onRing = 1; ind=i;
            cx = rings[i].position.x, cy = rings[i].position.y, r = rings[i].radius + rings[i].thickness / 2.0;
        }
    }

    // chech if ball has left the ring
    if (onRing && (ball.position.x <= rings[ind].position.x - rings[ind].radius - rings[ind].thickness || ball.position.x >= rings[ind].position.x + rings[ind].radius + rings[ind].thickness))
        onRing = 0;

    // ball with boomerang
    if (boom.present && (2 * abs(ball.b.x - boom.b.x) < (ball.b.width + boom.b.width)) 
        && (2 * abs(ball.b.y - boom.b.y) < (ball.b.height + boom.b.height))) {
        --lives_remaining;
        ball.position.x = -3;
        ball.position.y = 0;
    }

}

float dist(float a, float b, float c, float d) {
	return sqrt((a-c)*(a-c) + (b-d)*(b-d));
}

void display_score () {
    scr.clear();
    int dgt, i = 0;
    while (i < 4) {
        dgt = score % (10*(i + 1));
        if (dgt == 0 || dgt == 4 || dgt == 5 || dgt == 6 || dgt == 8 || dgt == 9) {
            scr.pb(Score(-3+i/3.0, -3 + 0.3, 0, COLOR_BLACK));
        }
        if (dgt == 0 || dgt == 2 || dgt == 6 || dgt == 8) {
            scr.pb(Score(-3+i/3.0, -3, 0, COLOR_BLACK));
        }
        if (dgt == 0 || dgt == 2 || dgt == 3 || dgt == 5 || dgt == 6 || dgt == 7 || dgt == 8 || dgt == 9) {
            scr.pb(Score(-3+i/3.0, -3 + 0.6, 270, COLOR_BLACK));
        }
        if (dgt == 2 || dgt == 3 || dgt == 4 || dgt == 5 || dgt == 6 || dgt == 8 || dgt == 9) {
            scr.pb(Score(-3+i/3.0, -3 + 0.3, 270, COLOR_BLACK));
        }
        if (dgt == 0 || dgt == 2 || dgt == 3 || dgt == 5 || dgt == 6 || dgt == 8 || dgt == 9) {
            scr.pb(Score(-3+i/3.0, -3, 270, COLOR_BLACK));
        }
        if (dgt == 0 || dgt == 1 || dgt == 2 || dgt == 3 || dgt == 4 || dgt == 7 || dgt == 8 || dgt == 9) {
            scr.pb(Score(-3+0.3*i+i/3.0+0.3, -3 + 0.3, 0, COLOR_BLACK));
        }
        if (dgt == 0 || dgt == 1 || dgt == 3 || dgt == 4 || dgt == 5 || dgt == 6 || dgt == 7 || dgt == 8 || dgt == 9) {
            scr.pb(Score(-3+i/3.0+0.3, -3, 0, COLOR_BLACK));
        }
    }
    ++i;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
