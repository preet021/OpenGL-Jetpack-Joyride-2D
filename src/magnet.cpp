#include "main.h"
#include "magnet.h"
#define N_TRNG 360
#define INF 999999999
#include <cmath>

Magnet::Magnet(color_t color) {

    this->rotation = 0;
    this->present = false;
    this->thickness = 0.1;
    this->length = 0.3;
    this->width = 0.3;
    this->ctime = 0;

    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        length, 0.0f, 0.0f,
        length, thickness, 0.0f,

        length, thickness, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, thickness, 0.0f,

        0.0f, width - thickness, 0.0f,
        0.0f, width, 0.0f,
        length, width - thickness, 0.0f,

        0.0f, width, 0.0f,
        length, width - thickness, 0.0f,
        length, width, 0.0f,

        length, 0.0f, 0.0f,
        length + thickness, 0.0f, 0.0f,
        length, width, 0.0f,

        length, width, 0.0f,
        length + thickness, 0.0f, 0.0f,
        length + thickness, width, 0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
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

void Magnet::tick () {
    this->ctime += 1;
    if (this->ctime > 1000)
        this->present = 0;
}
