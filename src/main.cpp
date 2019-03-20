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
#include "speedup.h"
#include "bank.h"
#include "dragon.h"
#include "bullet.h"
#include <iostream>
#define INF 999999999
#define pb push_back
#define sz(a) (int)(a).size() 
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

Dragon dragon;
Boomerang boom;
Magnet magnet;
Propulsion gas[20];
Ball lives[10];
Bank bank;
Speedup speedup;
Firebeam firebeams[10];
Fireline firelines[3];
Ball ball;
Ring rings[2];
Platform platform;
Score sc;

Bullet bullets[20];
vector <Score> scr;
vector <Coin> coins;
vector <Waterball> waterballs;
bounding_box_t b;
color_t COLOR_BALL = {255, 255, 255}, COLOR_PLATFORM = {0, 153, 153}, COLOR_COIN = {255, 255, 102}, COLOR_FIRE = {255, 128, 0}, COLOR_WATER = {0, 128, 255}, COLOR_PROPULSION = {255, 255, 255}, COLOR_MAGNET = {238, 5, 52}, COLOR_RING = {220, 239, 157}, COLOR_BOOM = {243, 46 ,46}, COLOR_COIN1 = {20, 200, 20};

int NO_OF_FIRELINES = 3, NO_OF_COINS = 5, NO_OF_WBALLS = 0, delay = 40, NO_OF_GAS = 0, NO_OF_FIREBEAMS = 10, NO_OF_MAGNETS = 1, NO_OF_RINGS = 2, NO_OF_BOOM = 5, score = 0, lives_remaining = 10, NO_OF_BULLETS = 20;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, camera_rotation_angle = 0, cx, cy, r, screen_speed = 0.03, spd_inc = 0.3;
bool onRing = 0, gravity = 1, has_speedup = 0;
int ind, ticks_boom = 0, ticks_magnet = 0, ii=0, bullet_time = 50;

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
    ball.speed_x_act = screen_speed;

    platform.draw(VP);
    
    for (int i=0; i<NO_OF_COINS; ++i) {
        coins[i].speed_x = screen_speed;
        if (coins[i].position.x != INF)
            coins[i].draw(VP);
    }

    for (int i=0; i<NO_OF_FIRELINES; ++i) {
        firelines[i].speed_x = screen_speed;
        if (firelines[i].position.x != INF)
            firelines[i].draw(VP);
    }
    
    for (int i=0; i<NO_OF_WBALLS; ++i) {
        if (waterballs[i].position.x != INF)
            waterballs[i].draw(VP);
    }
    
    for (int i=0; i<20; ++i) {
        if (gas[i].position.y != INF)
            gas[i].draw(VP);
    }
    
    if (magnet.present)
        magnet.draw(VP);
    
    for (int i=0; i<NO_OF_FIREBEAMS; ++i) {
        firebeams[i].speed_x = screen_speed;
        if (firebeams[i].position.x != INF)
            firebeams[i].draw(VP);
    }

    for (int i=0; i<NO_OF_RINGS; ++i) {
        rings[i].speed_x = screen_speed;
        rings[i].draw(VP);
    }

    if (boom.present)
        boom.draw(VP);

    for (int i=0; i<sz(scr); ++i) {
        scr[i].draw(VP);
    }

    if (speedup.present) {
        speedup.speed_x = screen_speed;
        speedup.draw(VP);
    }

    if (bank.present) {
        bank.speed_x = screen_speed;
        bank.draw(VP);
    }

    if (dragon.present) dragon.draw(VP);

    for (int i=0; i<NO_OF_BULLETS; ++i) {
        if (bullets[i].position.x != INF)
            bullets[i].draw(VP);
    }

    for (int i=0; i<lives_remaining; ++i) {
        lives[i].draw(VP);
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

    if (speedup.present) speedup.tick(dir);

    if (bank.present) bank.tick(dir);

    // camera_rotation_angle += 1;
}

void tick_input(GLFWwindow *window) {

    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_W);
    int waterballoons = glfwGetKey(window, GLFW_KEY_SPACE);
    int q = glfwGetKey(window, GLFW_KEY_Q);

    if (q) {
        cout << "----------------Game Over---------------\n";
        cout << "Final Score: " << score + lives_remaining << endl;
        quit(window);
    }

    if (!onRing && gravity)
        ball.tick(DIR_DOWN);
        
    if (left) {
        if (ball.position.x <= -3.78)
            tick_elements(0);
        else ball.tick(DIR_LEFT);
    }

    if (right) {
        if (ball.position.x >= 3.78)
        {
            ball.position.x -= 100*screen_speed;
            for (int i=0; i<100; ++i)
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
        gas[NO_OF_GAS].position.x = x;
        gas[NO_OF_GAS].position.y = y;
        gas[NO_OF_GAS].ctime = 0;
                    
        NO_OF_GAS = (NO_OF_GAS + 1) % 20;
        ball.tick(DIR_UP);
    }
    
    if (waterballoons) {
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

    if (has_speedup)
        tick_elements(1);
    
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball = Ball(0, -1.5, COLOR_BALL);

    platform = Platform(0, -2, COLOR_PLATFORM);
    
    for (int i=0, x, y, t; i<NO_OF_COINS; ++i) {
        y = -1 + rand() % 4;
        color_t c;
        t = rand() % 6;
        if (t >= 3) c = COLOR_COIN, t=0;
        else c = COLOR_COIN1, t=1;
        x = 3 + rand() % 10;
        coins.pb(Coin(x, y, c, t));
    }
    
    for (int i=0, x, y; i<NO_OF_FIRELINES; ++i) {
        float len = 1 + rand() % 2;
        float rotation = 50 + rand() % 80;
        x = 5 + rand() % 15;
        y = -1 + rand() % 4;
        firelines[i] = (Fireline(x, y, rotation, len, COLOR_FIRE));
    }
    
    magnet = Magnet(COLOR_MAGNET);
    
    for (int i=0, x, y; i<NO_OF_FIREBEAMS; i+=2) {
        float len = 1 + rand() % 2;
        x = 30 + rand() % 70;
        y = -1;
        firebeams[i] = (Firebeam(x, y, len, COLOR_FIRE, 0));
        firebeams[i+1] = (Firebeam(x, y + 1, len, COLOR_FIRE, 1));
    }

    for (int i=0; i<NO_OF_RINGS; ++i) {
        rings[i] = (Ring(5 + rand() % 10, -1 + rand() % 3, COLOR_RING));
    }

    for (int i=0; i<20; ++i) {
        gas[i] = (Propulsion(0, INF, COLOR_PROPULSION));
    }

    boom = Boomerang(COLOR_BOOM);

    sc = Score(0, 0, 0, COLOR_BLACK);

    speedup = Speedup(5 + rand() % 15, 1);

    bank = Bank(speedup.position.x+20, 1);

    dragon = Dragon(3, 0);

    for (int i=0; i<lives_remaining; ++i) {
        lives[i] = (Ball(-2.5+i/2.0, -3.5, COLOR_BLACK));
    }

    for (int i=0; i<NO_OF_BULLETS; ++i) {
        bullets[i] = (Bullet(INF, dragon.position.y));
    }
    NO_OF_BULLETS = 0;

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

            for (int i=0; i<20; ++i) {
                if (gas[i].position.y != INF)
                    gas[i].tick();
            }

            for (int i=0; i<NO_OF_FIREBEAMS; i++) {
                firebeams[i].position.y += firebeams[i].speed_y;
                if ((i & 1) && (firebeams[i].position.y > 3.5 || firebeams[i].position.y < -0.1))
                    firebeams[i].speed_y *= -1;
                if (!(i & 1) && (firebeams[i].position.y > 2.5 || firebeams[i].position.y < -1.2))
                    firebeams[i].speed_y *= -1;
            }

            for (int i=0; i<NO_OF_BULLETS; ++i) {
                if (bullets[i].position.x != INF)
                    bullets[i].tick();
            }

            if (speedup.present)
            {
                speedup.position.y += speedup.speed_y;
                if (speedup.position.y >= 3 || speedup.position.y <= -1.5)
                    speedup.speed_y *= -1;
            }

            if (has_speedup)
            {
                speedup.rtime -= 1;
                if (speedup.rtime <= 0)
                {
                    has_speedup = 0;
                    screen_speed -= spd_inc;
                }
            }

            if (bank.present)
            {
                bank.position.y += bank.speed_y;
                if (bank.position.y >= 3 || bank.position.y <= -1.5)
                    bank.speed_y *= -1;
            }

            if (!boom.present && NO_OF_BOOM > 0 && ticks_boom >= 500) {
                ticks_boom = 0;
                // NO_OF_BOOM--;
                boom.present = true;
                boom.position.y = 2.5;
                boom.position.x = boom.cx + ((boom.position.y - boom.cy)*(boom.position.y - boom.cy));
            }

            if ((rand() % 1007 <= -93) && !magnet.present && NO_OF_MAGNETS > 0 && ticks_magnet >= 1000) {
                ticks_magnet = 0;
                // NO_OF_MAGNETS--;
                magnet.present = true;
                magnet.position.x = -3 + rand() % 6;
                magnet.position.y = -1.5 + rand() % 5;
                magnet.ctime = 0;
                magnet.direction = rand() % 2;
                if (magnet.direction) magnet.rotation = 180.0f;
                else magnet.rotation = 0.0f;
            }

            if (dragon.present)
            {
                dragon.position.y += dragon.speed_y;
                if (dragon.position.y >= 3 || dragon.position.y <= -1.5)
                    dragon.speed_y *= -1;
                if (bullet_time <= 0) {
                    bullet_time = 50;
                    bullets[NO_OF_BULLETS].position.x = dragon.position.x;
                    bullets[NO_OF_BULLETS].position.y = dragon.position.y;
                    NO_OF_BULLETS++;
                    NO_OF_BULLETS %= 20;
                }
            }

            if (dragon.t >= 2000)
            {
                dragon.present = true;
            }

            if (dragon.t >= 3000)
            {
                dragon.present = false;
                dragon.t = 0;
            }

            if (lives_remaining == 0)
                break;

            display_score();
            
            tick_input(window);

            ++ticks_magnet;
            ++ticks_boom;
            ++dragon.t;
            --bullet_time;
            
            if (magnet.present) {
                // gravity = 0;
                if (ball.position.x - magnet.position.x >= 0.1) {
                    ball.position.x -= 0.05;
                }
                else if (ball.position.x - magnet.position.x <= 0.1) {
                    ball.position.x += 0.05;
                }
                if (ball.position.y - magnet.position.y >= 0.1) {
                    ball.position.y -= 0.5;
                }
                else if (ball.position.y - magnet.position.y <= -0.1) {
                    ball.position.y += 0.5;
                }
                magnet.tick();
            }
            else gravity = 1;

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
        bool f = 0;
        if (coins[i].position.x < -15) f = 1;
        else if ((2 * abs(ball.b.x - coins[i].b.x) < (ball.b.width + coins[i].b.width)) 
            && (2 * abs(ball.b.y - coins[i].b.y) < (ball.b.height + coins[i].b.height))) {
            f = 1;
            coins[i].position.x = INF;
            if (!coins[i].type)
                ++score;
            else score += 3;
        }
        if (f && i < 5)
        {
            coins[i].b.x = coins[i].position.x = 5 + rand() % 10;
            coins[i].b.y = coins[i].position.y = -1 + rand() % 5;
        }
    }

    // ball and fire
    for (int i=0; i<NO_OF_FIRELINES && !onRing && !has_speedup; ++i) {
        if (firelines[i].position.x == INF || firelines[i].position.x < -15)
        {
            firelines[i].rotation = 30 + rand() % 100;
            firelines[i].position.x = 5 + rand() % 15;
            firelines[i].position.y = -1 + rand() % 4;
            continue;
        }
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
            ball.b.y = ball.position.y = 5;
        }
    }

    for (int i=0; i<NO_OF_FIREBEAMS && !onRing; ++i) {
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
            ball.b.y = ball.position.y = 5;
        }
    }

    // water balloons and fire
    for (int i=0; i<NO_OF_WBALLS; ++i) {
        if (waterballs[i].position.x == INF) continue;
        for (int j=0; j<NO_OF_FIRELINES; ++j) {
            if (firelines[j].position.x == INF || firelines[i].position.x < -15)
            {
                firelines[i].rotation = 30 + rand() % 100;
                firelines[i].position.x = 5 + rand() % 15;
                firelines[i].position.y = -1 + rand() % 4;
                continue;
            }
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
    for (int i=0; i<NO_OF_RINGS && !has_speedup; ++i) {
        if (rings[i].position.x < -15 - rings[i].radius) {
            rings[i].position.x = 5 + rand() % 30;
            rings[i].position.y = -1 + rand() % 4;
            continue;
        }
        bool a, b;
        cx = rings[i].position.x, cy = rings[i].position.y, r = rings[i].radius + rings[i].thickness / 2.0;
        a = (abs(dist(ball.position.x, ball.position.y, rings[i].position.x, rings[i].position.y) - rings[i].radius - rings[i].thickness) <= 0.1);
        b = ((ball.position.y >= rings[i].position.y) && (ball.position.y <= rings[i].position.y + rings[i].radius + rings[i].thickness / 2.0));
        if (a && b) {
            ball.position.y = cy + sqrt(abs(r*r - (ball.position.x-cx)*(ball.position.x-cx)));
            onRing = 1;
            ind = i;
            cx = rings[i].position.x, cy = rings[i].position.y, r = rings[i].radius + rings[i].thickness / 2.0;
        }
    }

    // chech if ball has left the ring
    if (onRing && (ball.position.x <= rings[ind].position.x - rings[ind].radius - rings[ind].thickness || ball.position.x >= rings[ind].position.x + rings[ind].radius + rings[ind].thickness))
        onRing = 0;

    // ball with boomerang
    if (!has_speedup && !onRing && boom.present && (2 * abs(ball.b.x - boom.b.x) < (ball.b.width + boom.b.width)) 
        && (2 * abs(ball.b.y - boom.b.y) < (ball.b.height + boom.b.height))) {
        --lives_remaining;
        ball.position.x = -3;
        ball.position.y = 5;
    }

    // ball with speedup
    speedup.b.x = speedup.position.x;
    speedup.b.y = speedup.position.y;
    speedup.b.height = speedup.b.width = 2*(speedup.radius1+speedup.thickness);
    if (speedup.present && (2 * abs(ball.b.x - speedup.b.x) < (ball.b.width + speedup.b.width)) 
        && (2 * abs(ball.b.y - speedup.b.y) < (ball.b.height + speedup.b.height))) {
        has_speedup = 1;
        screen_speed += spd_inc;
        speedup.present = false;
    }

    // ball with coin bank
    bank.b.x = bank.position.x + bank.radius;
    bank.b.y = bank.position.y - bank.radius;
    if (bank.present && (2 * abs(ball.b.x - bank.b.x) < (ball.b.width + bank.b.width)) 
        && (2 * abs(ball.b.y - bank.b.y) < (ball.b.height + bank.b.height))) {
        bank.present = false;
        cy = ball.position.y;
        for (int i=0, c=1; i<5; ++i, cy+=0.4) {
            cx = ball.position.x + 2;
            for (int j=0; j<(5-c)/2; ++j, cx+=0.4) {
                coins.pb(Coin(cx, cy, COLOR_COIN, 0));
            }
            for (int j=0; j<c; ++j, cx+=0.4) {
                coins.pb(Coin(cx, cy, COLOR_COIN1, 1));
            }
            for (int j=0; j<(5-c)/2; ++j, cx+=0.4) {
                coins.pb(Coin(cx, cy, COLOR_COIN, 0));
            }
            if (i >= 2) c -= 2;
            else c += 2;
        }
        NO_OF_COINS += 25;
    }

    // ball with dragon bullets
    for (int i=0; i<NO_OF_BULLETS && !onRing && !has_speedup; ++i) {
        if (bullets[i].position.x == INF) continue;
        if ((2 * abs(ball.b.x - bullets[i].b.x) < (ball.b.width + bullets[i].b.width)) 
            && (2 * abs(ball.b.y - bullets[i].b.y) < (ball.b.height + bullets[i].b.height))) {
            bullets[i].position.x = INF;
            --lives_remaining;
            ball.position.x = -3;
            ball.position.y = 5;
        }
    }

}

float dist(float a, float b, float c, float d) {
	return sqrt((a-c)*(a-c) + (b-d)*(b-d));
}

void display_score () {
    scr.clear();
    for (int i=0, dgt, p=10; i<4; p*=10, ++i) {
        dgt = (10 * (score % p)) / p;
        if (dgt == 0 || dgt == 4 || dgt == 5 || dgt == 6 || dgt == 8 || dgt == 9) {
            sc.position = glm::vec3(-1+(3-i)/2.0, -3 + 0.3, 0);
            sc.rotation = 0;
            scr.pb(sc);
        }
        if (dgt == 0 || dgt == 2 || dgt == 6 || dgt == 8) {
            sc.position = glm::vec3(-1+(3-i)/2.0, -3,0);
            sc.rotation = 0;
            scr.pb(sc);
        }
        if (dgt == 0 || dgt == 2 || dgt == 3 || dgt == 5 || dgt == 6 || dgt == 7 || dgt == 8 || dgt == 9) {
            sc.position = glm::vec3(-1+(3-i)/2.0+0.1, -3 + 0.6,0);
            sc.rotation = 270;
            scr.pb(sc);
        }
        if (dgt == 2 || dgt == 3 || dgt == 4 || dgt == 5 || dgt == 6 || dgt == 8 || dgt == 9) {
            sc.position = glm::vec3(-1+(3-i)/2.0+0.1, -3 + 0.3,0);
            sc.rotation = 270;
            scr.pb(sc);
        }
        if (dgt == 0 || dgt == 2 || dgt == 3 || dgt == 5 || dgt == 6 || dgt == 8 || dgt == 9) {
            sc.position = glm::vec3(-1+(3-i)/2.0+0.1, -3,0);
            sc.rotation = 270;
            scr.pb(sc);
        }
        if (dgt == 0 || dgt == 1 || dgt == 2 || dgt == 3 || dgt == 4 || dgt == 7 || dgt == 8 || dgt == 9) {
            sc.position = glm::vec3(-1+(3-i)/2.0+0.3, -3 + 0.3,0);
            sc.rotation = 0;
            scr.pb(sc);
        }
        if (dgt == 0 || dgt == 1 || dgt == 3 || dgt == 4 || dgt == 5 || dgt == 6 || dgt == 7 || dgt == 8 || dgt == 9) {
            sc.position = glm::vec3(-1+(3-i)/2.0+0.3, -3,0);
            sc.rotation = 0;
            scr.pb(sc);
        }
    }
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
