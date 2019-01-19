#include "main.h"

#ifndef WATERBALL_H
#define WATERBALL_H

class Waterball {
public:
    Waterball() {}
    Waterball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void tick();
    void draw(glm::mat4 VP);
    double radius, speed_x, speed_y, acceleration;
    bounding_box_t b;
private:
    VAO *object;
};

#endif // WATERBALL_H
