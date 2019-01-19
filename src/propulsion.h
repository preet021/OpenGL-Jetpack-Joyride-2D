#include "main.h"

#ifndef PROPULSION_H
#define PROPULSION_H

class Propulsion {
public:
    Propulsion() {}
    Propulsion(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void tick();
    void draw(glm::mat4 VP);
    double radius, speed_y, ctime;
private:
    VAO *object;
};

#endif // PROPULSION_H
