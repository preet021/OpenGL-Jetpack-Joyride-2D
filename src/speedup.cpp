#include "main.h"
#include "speedup.h"
#define N_BLCK 180
#define N_TRNG 360

Speedup::Speedup(float x, float y) {
    
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius1 = 0.25f;
    this->radius2 = 0.22f;
    this->thickness = 0.15f;
    this->speed_y = 0.1;
    this->present = true;
    this->rtime = 100;

    int sz = 9*N_TRNG;
    GLfloat vertex_buffer_data[sz+36*N_BLCK], vertex_buffer_color[sz+36*N_BLCK];

    double theta = 0, phi = M_PI / N_BLCK, ax, bx, cx, dx, ay, by, cy, dy;

    for (int i=0; i<36*N_BLCK; i+=18) {
        ax = (radius1 + thickness) * cos(theta);
        bx = radius1 * cos(theta);
        cx = (radius1 + thickness) * cos(theta + phi);
        dx = radius1 * cos(theta + phi);

        ay = (radius1 + thickness) * sin(theta);
        by = radius1 * sin(theta);
        cy = (radius1 + thickness) * sin(theta + phi);
        dy = radius1 * sin(theta + phi);

        vertex_buffer_data[i] = ax;
        vertex_buffer_data[i + 1] = ay;
        vertex_buffer_data[i + 2] = 0.0f;

        vertex_buffer_data[3 + i]  = bx;
        vertex_buffer_data[3 + i + 1] = by;
        vertex_buffer_data[3 + i + 2] = 0.0f;

        vertex_buffer_data[6 + i] = dx;
        vertex_buffer_data[6 + i + 1] = dy;
        vertex_buffer_data[6 + i + 2] = 0.0f;

        vertex_buffer_data[9 + i] = ax;
        vertex_buffer_data[9 + i + 1] = ay;
        vertex_buffer_data[9 + i + 2] = 0.0f;

        vertex_buffer_data[9 + 3 + i]  = cx;
        vertex_buffer_data[9 + 3 + i + 1] = cy;
        vertex_buffer_data[9 + 3 + i + 2] = 0.0f;

        vertex_buffer_data[9 + 6 + i] = dx;
        vertex_buffer_data[9 + 6 + i + 1] = dy;
        vertex_buffer_data[9 + 6 + i + 2] = 0.0f;
        
        theta += phi;
    }

    for (int i=0; i<36*N_BLCK; i+=18) {

        vertex_buffer_color[i] = 0.3f;
        vertex_buffer_color[i + 1] = 0.4f;
        vertex_buffer_color[i + 2] = 0.0f;

        vertex_buffer_color[3 + i]  =0.3f;
        vertex_buffer_color[3 + i + 1] = 0.4f;
        vertex_buffer_color[3 + i + 2] = 0.0f;

        vertex_buffer_color[6 + i] = 0.3f;
        vertex_buffer_color[6 + i + 1] = 0.4f;
        vertex_buffer_color[6 + i + 2] = 0.0f;

        vertex_buffer_color[9 + i] = 0.3f;
        vertex_buffer_color[9 + i + 1] = 0.4f;
        vertex_buffer_color[9 + i + 2] = 0.0f;

        vertex_buffer_color[9 + 3 + i]  =0.3f;
        vertex_buffer_color[9 + 3 + i + 1] = 0.4f;
        vertex_buffer_color[9 + 3 + i + 2] = 0.0f;

        vertex_buffer_color[9 + 6 + i] = 0.3f;
        vertex_buffer_color[9 + 6 + i + 1] = 0.4f;
        vertex_buffer_color[9 + 6 + i + 2] = 0.0f;
        
    }

    for (int i=0; i<9*N_TRNG; i+=9) {

        vertex_buffer_data[36*N_BLCK+i] = 0.0f;
        vertex_buffer_data[36*N_BLCK+i+1] = 0.0f;
        vertex_buffer_data[36*N_BLCK+i+2] = 0.0f;

        vertex_buffer_data[36*N_BLCK+i+3] = radius2*cos((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data[36*N_BLCK+i+4] = radius2*sin((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data[36*N_BLCK+i+5] = 0.0f;

        vertex_buffer_data[36*N_BLCK+i+6] = radius2*cos((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data[36*N_BLCK+i+7] = radius2*sin((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data[36*N_BLCK+i+8] = 0.0f;

    }

    for (int i=0; i<9*N_TRNG; i+=9) {

        vertex_buffer_color[36*N_BLCK+i] = 0.1f;
        vertex_buffer_color[36*N_BLCK+i+1] = 0.8f;
        vertex_buffer_color[36*N_BLCK+i+2] = 0.1f;

        vertex_buffer_color[36*N_BLCK+i+3] = 0.1f;
        vertex_buffer_color[36*N_BLCK+i+4] = 0.8f;
        vertex_buffer_color[36*N_BLCK+i+5] = 0.1f;

        vertex_buffer_color[36*N_BLCK+i+6] = 0.1f;
        vertex_buffer_color[36*N_BLCK+i+7] = 0.8f;
        vertex_buffer_color[36*N_BLCK+i+8] = 0.1f;

    }

    this->object = create3DObject(GL_TRIANGLES, 12*N_BLCK+3*N_TRNG, vertex_buffer_data, vertex_buffer_color, GL_FILL);
}

void Speedup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Speedup::tick(bool dir) {
    if (dir)
        this->position.x -= speed_x;
    else
        this->position.x += speed_x;
}
