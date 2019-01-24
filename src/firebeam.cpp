#include "main.h"
#include "firebeam.h"
#define N_TRNG 360
#define INF 999999999
#include <cmath>

Firebeam::Firebeam(float x, float y, float len, color_t color, bool t) {

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_x = 0.03;
    speed_y = 0.05f;
    radius = 0.1f;
    length = len;

    GLfloat vertex_buffer_data[2*9*N_TRNG + 18], vertex_buffer_color[2*9*N_TRNG + 18];

    for (int i=0; i<9*N_TRNG; i+=9) {

        vertex_buffer_data[i] = 0.0f;
        vertex_buffer_data[i+1] = 0.0f;
        vertex_buffer_data[i+2] = 0.0f;

        vertex_buffer_data[i+3] = radius*cos((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data[i+4] = radius*sin((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data[i+5] = 0.0f;

        vertex_buffer_data[i+6] = radius*cos((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data[i+7] = radius*sin((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data[i+8] = 0.0f;

    }

    for (int i=0; i<9*N_TRNG; i+=9) {

        vertex_buffer_data[9*N_TRNG + i] = length;
        vertex_buffer_data[9*N_TRNG + i+1] = 0.0f;
        vertex_buffer_data[9*N_TRNG + i+2] = 0.0f;

        vertex_buffer_data[9*N_TRNG + i+3] = length + radius*cos((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data[9*N_TRNG + i+4] = radius*sin((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data[9*N_TRNG + i+5] = 0.0f;

        vertex_buffer_data[9*N_TRNG + i+6] = length + radius*cos((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data[9*N_TRNG + i+7] = radius*sin((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data[9*N_TRNG + i+8] = 0.0f;

    }

    for (int i=2; i<18; i+=3) {
        vertex_buffer_data[18*N_TRNG+i] = 0.0f;
    }

    vertex_buffer_data[18*N_TRNG] = 0.0f;
    vertex_buffer_data[18*N_TRNG+1] = radius/2.0;
    vertex_buffer_data[18*N_TRNG+3] = 0.0f;
    vertex_buffer_data[18*N_TRNG+4] = -radius/2.0;
    vertex_buffer_data[18*N_TRNG+6] = length;
    vertex_buffer_data[18*N_TRNG+7] = radius/2.0;

    vertex_buffer_data[18*N_TRNG+9] = 0.0f;
    vertex_buffer_data[18*N_TRNG+10] = -radius/2.0;
    vertex_buffer_data[18*N_TRNG+12] = length;
    vertex_buffer_data[18*N_TRNG+13] = radius/2.0;
    vertex_buffer_data[18*N_TRNG+15] = length;
    vertex_buffer_data[18*N_TRNG+16] = -radius/2.0;

    // for (int i=0; i<9*N_TRNG; i+=9) {

    //     vertex_buffer_color[i] = 120.0f;
    //     vertex_buffer_color[i+1] = 120.0f;
    //     vertex_buffer_color[i+2] = 120.0f;

    //     vertex_buffer_color[i+3] = 120.0f;
    //     vertex_buffer_color[i+4] = 120.0f;
    //     vertex_buffer_color[i+5] = 120.0f;

    //     vertex_buffer_color[i+6] = 120.0f;
    //     vertex_buffer_color[i+7] = 120.0f;
    //     vertex_buffer_color[i+8] = 120.0f;

    // }

    // for (int i=0; i<9*N_TRNG; i+=9) {

    //     vertex_buffer_color[9*N_TRNG + i] = 120.0f;
    //     vertex_buffer_color[9*N_TRNG + i+1] = 120.0f;
    //     vertex_buffer_color[9*N_TRNG + i+2] = 120.0f;

    //     vertex_buffer_color[9*N_TRNG + i+3] = 120.0f;
    //     vertex_buffer_color[9*N_TRNG + i+4] = 120.0f;
    //     vertex_buffer_color[9*N_TRNG + i+5] = 120.0f;

    //     vertex_buffer_color[9*N_TRNG + i+6] = 120.0f;
    //     vertex_buffer_color[9*N_TRNG + i+7] = 120.0f;
    //     vertex_buffer_color[9*N_TRNG + i+8] = 120.0f;

    // }

    // for (int i=2; i<18; i+=3) {
    //     vertex_buffer_color[18*N_TRNG+i] = 0.0f;
    // }

    // vertex_buffer_color[18*N_TRNG] = 255.0f;
    // vertex_buffer_color[18*N_TRNG+1] = 128.0f;
    // vertex_buffer_color[18*N_TRNG+3] = 255.0f;
    // vertex_buffer_color[18*N_TRNG+4] = 128.0f;
    // vertex_buffer_color[18*N_TRNG+6] = 255.0f;
    // vertex_buffer_color[18*N_TRNG+7] = 128.0f;

    // vertex_buffer_color[18*N_TRNG+9] = 255.0f;
    // vertex_buffer_color[18*N_TRNG+10] = 128.0f;
    // vertex_buffer_color[18*N_TRNG+12] = 255.0f;
    // vertex_buffer_color[18*N_TRNG+13] = 128.0f;
    // vertex_buffer_color[18*N_TRNG+15] = 255.0f;
    // vertex_buffer_color[18*N_TRNG+16] = 128.0f;

    this->object = create3DObject(GL_TRIANGLES, 2*N_TRNG*3 + 6, vertex_buffer_data, color, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
}

void Firebeam::tick(bool dir) {
    if (dir)
        this->position.x -= speed_x;
    else this->position.x += speed_x;
}
