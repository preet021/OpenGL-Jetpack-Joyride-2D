#include "main.h"
#include "ball.h"

Ball::Ball(float x, float y, color_t color) {
	
	this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    acceleration = 1.0/200;
    speed_x = 0.03;
    speed_y_ascend = 0.1;
    speed_y_descend = 0.03;
    height = 0.4f;
    width = 0.4f;
    b.x = x;
    b.y = y;
    b.width = width;
    b.height = height;

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
        speed_y_ascend = 0.1;
        if (this->position.y > -1.8) {
            speed_y_descend += acceleration;
            this->position.y -= speed_y_descend;
            if (this->position.y < -1.8) this->position.y = -1.8;
        }
        else speed_y_descend = 0.03, speed_y_ascend = 0.1;
        this->b.y = this->position.y;
    }
    else if (dir == DIR_RIGHT) {
        if (this->position.x < 4) {
            this->position.x += this->speed_x;
        }
        this->b.x = this->position.x;
    }
    else if (dir == DIR_LEFT) {
        if (this->position.x > -3.6) {
            this->position.x -= this->speed_x;
        }
        this->b.x = this->position.x;
    }
    else if (dir == DIR_UP) {
        speed_y_descend = 0.03;
        if (this->position.y < 3.8) {
            speed_y_ascend += acceleration;
            this->position.y += this->speed_y_ascend;
        }
        this->b.y = this->position.y;
    }
}
