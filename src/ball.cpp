#include "main.h"
#include "ball.h"

Ball::Ball(float x, float y, color_t color) {
	
	this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->acceleration = 1.0/200;
    this->speed_x = 0.0f;
    this->speed_y_ascend = 0.1;
    this->speed_y_descend = 0.03;
    this->height = 0.4f;
    this->width = 0.4f;
    this->b.x = x;
    this->b.y = y;
    this->b.width = width;
    this->b.height = height;

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

	this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
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

void Ball::tick(direction_t dir) {
    if (dir == DIR_DOWN) {
        this->speed_y_ascend = 0.1;
        if (this->position.y > -1.8) {
            this->speed_y_descend += this->acceleration;
            this->position.y -= this->speed_y_descend;
            this->position.x += this->speed_x;
        }
        else this->speed_y_descend = 0.03, this->speed_y_ascend = 0.1, this->speed_x = 0;
    }
    else if (dir == DIR_RIGHT) {
        this->speed_x = 0.04;
        this->position.x += this->speed_x;
    }
    else if (dir == DIR_LEFT) {
        this->speed_x = -0.04;
        this->position.x += this->speed_x;
    }
    else if (dir == DIR_UP) {
        this->speed_y_descend = 0.03;
        if (this->position.y < 3.8) {
            this->speed_y_ascend += this->acceleration;
            this->position.y += this->speed_y_ascend;
        }
    }
    if (this->position.y < -1.8) this->position.y = -1.8;
    if (this->position.x < -3.8) this->position.x = -3.8;
    if (this->position.x > 3.8) this->position.x = 3.8;
    if (abs(this->position.y + 1.8) <= 0.001) this->speed_x = 0;
    this->b.x = this->position.x;
    this->b.y = this->position.y;
}
