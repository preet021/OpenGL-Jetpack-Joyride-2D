#include "main.h"
#include "waterball.h"
#define N_TRNG 360
#define INF 999999999

Waterball::Waterball(float x, float y, color_t color) {

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    radius = 0.1f;
    b.x = x;
    b.y = y;
    b.width = 2*radius;
    b.height = 2*radius;
    speed_x = 0.05;
    speed_y = 0.1;
    acceleration = -1.0/200;

    GLfloat vertex_buffer_data[N_TRNG*9];

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

    this->object = create3DObject(GL_TRIANGLES, N_TRNG*3, vertex_buffer_data, color, GL_FILL);
}

void Waterball::draw(glm::mat4 VP) {
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

void Waterball::tick() {
    this->position.x += speed_x;
    this->position.y += speed_y;
    speed_y += acceleration;
    this->b.x = this->position.x;
    this->b.y = this->position.y;
}
