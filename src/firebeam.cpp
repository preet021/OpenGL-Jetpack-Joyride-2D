#include "main.h"
#include "firebeam.h"
#define N_TRNG 360
#define INF 999999999
#include <cmath>

Firebeam::Firebeam(float x, float y, float len, color_t color) {

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed_x = 0.03;
    speed_y = 0.1f;
    radius = 0.1f;
    length = len;

    GLfloat vertex_buffer_data[2*9*N_TRNG + 18];

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

void Firebeam::tick() {
    this->position.x -= speed_x;
    if (this->position.x < -8) {
        this->position.x = INF;
    }
    this->position.y += speed_y;
    if (this->position.y > 3.8 || this->position.y < -1.8)
        speed_y *= -1;
}
