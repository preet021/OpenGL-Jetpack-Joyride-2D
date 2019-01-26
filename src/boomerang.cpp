#include "main.h"
#include "boomerang.h"

Boomerang::Boomerang(color_t color) {
	
    this->rotation = 0;
    this->speed_y = -0.04f;
    this->present = false;
    this->cx = -3.0f;
    this->cy = 0.0f;
    this->b.x = this->position.x;
    this->b.y = this->position.y + 0.25;
    this->b.width = this->b.height = 0.5f;

	GLfloat vertex_buffer_data[] = {
		-0.25f, 0.0f, 0.0f,
        0.25f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
	};

	this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
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

void Boomerang::tick() {
    // equation of motion: (y - cy)^2 = 4*(x - cx)
    this->rotation += 5;
    this->position.y += this->speed_y;
    this->position.x = this->cx + ((this->position.y - this->cy)*(this->position.y - this->cy));
    if (this->position.x > 5 || this->position.y < -2 || this->position.y > 4)
        this->present = false;
    this->b.x = this->position.x;
    this->b.y = this->position.y + 0.25;
}
