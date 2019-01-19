#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H

class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, float rot, float length, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double length, radius;
private:
    VAO *object;
};

#endif // FIRELINE_H
