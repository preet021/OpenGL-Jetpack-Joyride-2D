#include "main.h"
#include "dragon.h"
#define N_TRNG 360
#define N_BLCK 79

Dragon::Dragon(float x, float y) {
    
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90;
    this->height = 0.7f;
    this->width = 0.7f;
    this->b.x = x;
    this->b.y = y;
    this->b.width = width;
    this->b.height = height;
    this->radius1 = 0.1;
    this->radius2 = 0.05;
    this->speed_y = 0.05;
    this->present = false;
    this->t = 0;

    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        -width/2.0, height/2.0, 0.0f,
        -width/2.0, -height/2.0, 0.0f,

        -width/2.0, height/2.0, 0.0f,
        width/2.0, height/2.0, 0.0f,
        0.0f, 0.0f, 0.0f,
        
        0.0f, 0.0f, 0.0f,
        width/2.0, height/2.0, 0.0f,
        width/2.0, -height/2.0, 0.0f,

        width/2.0, -height/2.0, 0.0f,
        -width/2.0, -height/2.0, 0.0f,
        0.0f, 0.0f, 0.0f,
    };

    color_t face = {255, 158, 0}, mouth = {0, 0, 0}, eye = {255, 255, 255}, eball = {0, 255, 0};

    this->object[0] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, face, GL_FILL);

    GLfloat vertex_buffer_data1[] = {
        -0.1f, -0.1f, 0.0f,
        -width/3.0, height/2.0, 0.0f,
        0.0f, height/2.0, 0.0f
    };

    this->object[1] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, mouth, GL_FILL);

    GLfloat vertex_buffer_data2[9*N_TRNG];

    for (int i=0; i<9*N_TRNG; i+=9) {

        vertex_buffer_data2[i] = 0.17f;
        vertex_buffer_data2[i+1] = 0.1f;
        vertex_buffer_data2[i+2] = 0.0f;

        vertex_buffer_data2[i+3] = 0.17+radius1*cos((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data2[i+4] = 0.1+radius1*sin((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data2[i+5] = 0.0f;

        vertex_buffer_data2[i+6] = 0.17+radius1*cos((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data2[i+7] = 0.1+radius1*sin((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data2[i+8] = 0.0f;

    }

    this->object[2] = create3DObject(GL_TRIANGLES, 3*N_TRNG, vertex_buffer_data2, eye, GL_FILL);

    GLfloat vertex_buffer_data3[9*N_TRNG];

    for (int i=0; i<9*N_TRNG; i+=9) {

        vertex_buffer_data3[i] = 0.17f;
        vertex_buffer_data3[i+1] = 0.1f;
        vertex_buffer_data3[i+2] = 0.0f;

        vertex_buffer_data3[i+3] = 0.17+radius2*cos((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data3[i+4] = 0.1+radius2*sin((i/9)*(2*M_PI/N_TRNG));
        vertex_buffer_data3[i+5] = 0.0f;

        vertex_buffer_data3[i+6] = 0.17+radius2*cos((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data3[i+7] = 0.1+radius2*sin((i/9+1)*(2*M_PI/N_TRNG));
        vertex_buffer_data3[i+8] = 0.0f;

    }

    this->object[3] = create3DObject(GL_TRIANGLES, 3*N_TRNG, vertex_buffer_data3, eball, GL_FILL);

    GLfloat vertex_buffer_data4[36] = {
        width/2.0, height/2.0, 0.0f,
        width/2.0, height/2.0-height/4.0, 0.0f,
        width/2.0+0.2, height/2.0-height/8.0, 0.0f,

        width/2.0, -height/4.0+height/2.0, 0.0f,
        width/2.0, -height/4.0+height/2.0-height/4.0, 0.0f,
        width/2.0+0.2, -height/4.0+height/2.0-height/8.0, 0.0f,

        width/2.0, -height/4.0-height/4.0+height/2.0, 0.0f,
        width/2.0, -height/4.0-height/4.0+height/2.0-height/4.0, 0.0f,
        width/2.0+0.2, -height/4.0-height/4.0+height/2.0-height/8.0, 0.0f,

        width/2.0, -height/4.0-height/4.0-height/4.0+height/2.0, 0.0f,
        width/2.0, -height/4.0-height/4.0-height/4.0+height/2.0-height/4.0, 0.0f,
        width/2.0+0.2, -height/4.0-height/4.0-height/4.0+height/2.0-height/8.0, 0.0f
    };

    this->object[4] = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data4, face, GL_FILL);

    float len = 1;

    GLfloat vertex_buffer_data5[18] = {
        -width/8.0, -height/2.0, 0.0f,
        -width/8.0, -height/2.0-len, 0.0f,
        width/8.0, -height/2.0-len, 0.0f,

        -width/8.0, -height/2.0, 0.0f,
        width/8.0, -height/2.0-len, 0.0f,
        width/8.0, -height/2.0, 0.0f
    };

    this->object[5] = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data5, face, GL_FILL);

}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);
    draw3DObject(this->object[5]);
}

void Dragon::tick(direction_t dir) {
    
}
