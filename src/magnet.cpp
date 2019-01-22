#include "main.h"
#include "magnet.h"
#define N_TRNG 360
#define INF 999999999
#include <cmath>

Magnet::Magnet(float x, float y, float far, color_t color) {

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x = far;
    count = 2;
    thickness = 0.1;
    length = 0.5;
    width = 0.4;

    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        thickness, 0.0f, 0.0f,
        0.0f, width, 0.0f,
        
        thickness, 0.0f, 0.0f,
        0.0f, width, 0.0f,
        thickness, width, 0.0f,
        
        thickness, 0.0f, 0.0f,
        thickness, thickness, 0.0f,
        thickness + length, 0.0f, 0.0f,
        
        thickness, thickness, 0.0f,
        thickness + length, 0.0f, 0.0f,
        thickness + length, thickness, 0.0f,

        thickness, width, 0.0f,
        thickness, width - thickness, 0.0f,
        thickness + length, width, 0.0f,

        thickness + length, width, 0.0f,
        thickness, width - thickness, 0.0f,
        thickness + length, width - thickness, 0.0f
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

void Magnet::tick() {
    this->x -= 0.01;
    if (this->x < -3.8)
    {
        this->x = INF;
        if (count > 0)
        {
            count--;
            this->x = 5 + rand() % 25;
            this->position.y = -2 + rand()%2;
            this->position.x = -3 + rand() % 6;
        }
    }
}
