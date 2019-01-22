#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H

class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, float length, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double length, radius, speed_y, speed_x;
private:
    VAO *object;
};

#endif // FIREBEAM_H
