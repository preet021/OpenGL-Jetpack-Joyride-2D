#include "main.h"
#include "bank.h"
#define N_BLCK 360

Bank::Bank(float x, float y) {
    
    this->position = glm::vec3(x, y, 0);
    this->rotation = -90;
    this->radius = 0.22f;
    this->thickness = 0.1f;
    this->speed_y = 0.1;
    this->present = true;
    this->rtime = 100;
    this->b.width = 2.5*this->radius - 0.05;
    this->b.height = 2*(this->radius+this->thickness+(2.5*radius+0.05)*(0.707));

    color_t red = {255, 0, 0};
    GLfloat vertex_buffer_data[18*N_BLCK+45], vertex_buffer_color[18*N_BLCK+45];

    double theta = 952, phi = M_PI / N_BLCK, ax, bx, cx, dx, ay, by, cy, dy;

    for (int i=0; i<18*N_BLCK; i+=18) {
        ax = (radius + thickness) * cos(theta);
        bx = radius * cos(theta);
        cx = (radius + thickness) * cos(theta + phi);
        dx = radius * cos(theta + phi);

        ay = (radius + thickness) * sin(theta);
        by = radius * sin(theta);
        cy = (radius + thickness) * sin(theta + phi);
        dy = radius * sin(theta + phi);

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
        
        theta -= phi;
    }

    for (int i=0; i<18*N_BLCK; i+=18) {
        vertex_buffer_color[i] = 1.0f;
        vertex_buffer_color[i + 1] = 1.0f;
        vertex_buffer_color[i + 2] = 1.0f;

        vertex_buffer_color[3 + i]  = 1.0f;
        vertex_buffer_color[3 + i + 1] = 1.0f;
        vertex_buffer_color[3 + i + 2] = 1.0f;

        vertex_buffer_color[6 + i] = 1.0f;
        vertex_buffer_color[6 + i + 1] = 1.0f;
        vertex_buffer_color[6 + i + 2] = 1.0f;

        vertex_buffer_color[9 + i] = 1.0f;
        vertex_buffer_color[9 + i + 1] = 1.0f;
        vertex_buffer_color[9 + i + 2] = 1.0f;

        vertex_buffer_color[9 + 3 + i]  = 1.0f;
        vertex_buffer_color[9 + 3 + i + 1] = 1.0f;
        vertex_buffer_color[9 + 3 + i + 2] = 1.0f;

        vertex_buffer_color[9 + 6 + i] = 1.0f;
        vertex_buffer_color[9 + 6 + i + 1] = 1.0f;
        vertex_buffer_color[9 + 6 + i + 2] = 1.0f;
        
    }

    
    thickness += 0.02;
    vertex_buffer_data[18+18+18*N_BLCK] = 0.6+2*radius - 0.8;
    vertex_buffer_data[18+18+18*N_BLCK+1] = +0.0f;
    vertex_buffer_data[18+18+18*N_BLCK+2] = 0.0f;

    vertex_buffer_data[18+18+18*N_BLCK+3] = 0.6+2*radius + thickness - 0.8;
    vertex_buffer_data[18+18+18*N_BLCK+4] = +0.0f;
    vertex_buffer_data[18+18+18*N_BLCK+5] = 0.0f;

    vertex_buffer_data[18+18+18*N_BLCK+6] = 0.6+2*radius - 0.8 + (0.05+2.5*radius)*(0.707);
    vertex_buffer_data[18+18+18*N_BLCK+7] = (2.5*radius+0.05)*(0.707);
    vertex_buffer_data[18+18+18*N_BLCK+8] = 0.0f;

    vertex_buffer_color[18+18+18*N_BLCK] = 1.0f;
    vertex_buffer_color[18+18+18*N_BLCK+1] = 1.0f;
    vertex_buffer_color[18+18+18*N_BLCK+2] = 1.0f;

    vertex_buffer_color[18+18+18*N_BLCK+3] = 1.0f;
    vertex_buffer_color[18+18+18*N_BLCK+4] = 1.0f;
    vertex_buffer_color[18+18+18*N_BLCK+5] = 1.0f;

    vertex_buffer_color[18+18+18*N_BLCK+6] = 1.0f;
    vertex_buffer_color[18+18+18*N_BLCK+7] = 1.0f;
    vertex_buffer_color[18+18+18*N_BLCK+8] = 1.0f;



    vertex_buffer_data[18*N_BLCK] = 2*radius - 0.8;
    vertex_buffer_data[18*N_BLCK+1] = -0.05+0.0f;
    vertex_buffer_data[18*N_BLCK+2] = 0.0f;

    vertex_buffer_data[18*N_BLCK+3] = 2*radius + thickness - 0.8;
    vertex_buffer_data[18*N_BLCK+4] = -0.05+0.0f;
    vertex_buffer_data[18*N_BLCK+5] = 0.0f;

    vertex_buffer_data[18*N_BLCK+6] = 2*radius - 0.8;
    vertex_buffer_data[18*N_BLCK+7] = -0.05+2.5*radius;
    vertex_buffer_data[18*N_BLCK+8] = 0.0f;

    vertex_buffer_data[9+18*N_BLCK] = 2*radius + thickness - 0.8;
    vertex_buffer_data[9+18*N_BLCK+1] = -0.05+2.5*radius;
    vertex_buffer_data[9+18*N_BLCK+2] = 0.0f;

    vertex_buffer_data[9+18*N_BLCK+3] = 2*radius + thickness - 0.8;
    vertex_buffer_data[9+18*N_BLCK+4] = -0.05+0.0f;
    vertex_buffer_data[9+18*N_BLCK+5] = 0.0f;

    vertex_buffer_data[9+18*N_BLCK+6] = 2*radius - 0.8;
    vertex_buffer_data[9+18*N_BLCK+7] = -0.05+2.5*radius;
    vertex_buffer_data[9+18*N_BLCK+8] = 0.0f;


    vertex_buffer_color[18*N_BLCK] = 1.0f;
    vertex_buffer_color[18*N_BLCK+1] = 0.5f;
    vertex_buffer_color[18*N_BLCK+2] = 0.0f;

    vertex_buffer_color[18*N_BLCK+3] = 1.0f;
    vertex_buffer_color[18*N_BLCK+4] = 0.5f;
    vertex_buffer_color[18*N_BLCK+5] = 0.0f;

    vertex_buffer_color[18*N_BLCK+6] = 1.0f;
    vertex_buffer_color[18*N_BLCK+7] = 0.5f;
    vertex_buffer_color[18*N_BLCK+8] = 0.0f;

    vertex_buffer_color[9+18*N_BLCK] = 1.0f;
    vertex_buffer_color[9+18*N_BLCK+1] = 0.5f;
    vertex_buffer_color[9+18*N_BLCK+2] = 0.0f;

    vertex_buffer_color[9+18*N_BLCK+3] = 1.0f;
    vertex_buffer_color[9+18*N_BLCK+4] = 0.5f;
    vertex_buffer_color[9+18*N_BLCK+5] = 0.0f;

    vertex_buffer_color[9+18*N_BLCK+6] = 1.0f;
    vertex_buffer_color[9+18*N_BLCK+7] = 0.5f;
    vertex_buffer_color[9+18*N_BLCK+8] = 0.0f;




    vertex_buffer_data[18+18*N_BLCK] = 0.18+2*radius - 0.8;
    vertex_buffer_data[18+18*N_BLCK+1] = -0.05+0.0f;
    vertex_buffer_data[18+18*N_BLCK+2] = 0.0f;

    vertex_buffer_data[18+18*N_BLCK+3] = 0.18+2*radius + thickness - 0.8;
    vertex_buffer_data[18+18*N_BLCK+4] = -0.05+0.0f;
    vertex_buffer_data[18+18*N_BLCK+5] = 0.0f;

    vertex_buffer_data[18+18*N_BLCK+6] = 0.18+2*radius - 0.8;
    vertex_buffer_data[18+18*N_BLCK+7] = -0.05+2.5*radius;
    vertex_buffer_data[18+18*N_BLCK+8] = 0.0f;

    vertex_buffer_data[18+9+18*N_BLCK] = 0.18+2*radius - 0.8 + thickness;
    vertex_buffer_data[18+9+18*N_BLCK+1] = -0.05+2.5*radius;
    vertex_buffer_data[18+9+18*N_BLCK+2] = 0.0f;

    vertex_buffer_data[18+9+18*N_BLCK+3] = 0.18+2*radius + thickness - 0.8;
    vertex_buffer_data[18+9+18*N_BLCK+4] = -0.05+0.0f;
    vertex_buffer_data[18+9+18*N_BLCK+5] = 0.0f;

    vertex_buffer_data[18+9+18*N_BLCK+6] = 0.18+2*radius - 0.8;
    vertex_buffer_data[18+9+18*N_BLCK+7] = -0.05+2.5*radius;
    vertex_buffer_data[18+9+18*N_BLCK+8] = 0.0f;


    vertex_buffer_color[18+18*N_BLCK] = 0.0f;
    vertex_buffer_color[18+18*N_BLCK+1] = 1.0f;
    vertex_buffer_color[18+18*N_BLCK+2] = 0.0f;

    vertex_buffer_color[18+18*N_BLCK+3] = 0.0f;
    vertex_buffer_color[18+18*N_BLCK+4] = 1.0f;
    vertex_buffer_color[18+18*N_BLCK+5] = 0.0f;

    vertex_buffer_color[18+18*N_BLCK+6] = 0.0f;
    vertex_buffer_color[18+18*N_BLCK+7] = 1.0f;
    vertex_buffer_color[18+18*N_BLCK+8] = 0.0f;

    vertex_buffer_color[18+9+18*N_BLCK] = 0.0f;
    vertex_buffer_color[18+9+18*N_BLCK+1] = 1.0f;
    vertex_buffer_color[18+9+18*N_BLCK+2] = 0.0f;

    vertex_buffer_color[18+9+18*N_BLCK+3] = 0.0f;
    vertex_buffer_color[18+9+18*N_BLCK+4] = 1.0f;
    vertex_buffer_color[18+9+18*N_BLCK+5] = 0.0f;

    vertex_buffer_color[18+9+18*N_BLCK+6] = 0.0f;
    vertex_buffer_color[18+9+18*N_BLCK+7] = 1.0f;
    vertex_buffer_color[18+9+18*N_BLCK+8] = 0.0f;

    this->object = create3DObject(GL_TRIANGLES, 6*N_BLCK+15, vertex_buffer_data, vertex_buffer_color, GL_FILL);
}

void Bank::draw(glm::mat4 VP) {
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

void Bank::tick(bool dir) {
    if (dir)
        this->position.x -= speed_x;
    else
        this->position.x += speed_x;
}
