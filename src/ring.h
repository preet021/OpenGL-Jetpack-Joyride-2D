#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    bool on;
    void draw(glm::mat4 VP);
    void tick(bool dir);
    double thickness, radius, speed_x;
    bounding_box_t b;
private:
    VAO *object;
};

#endif // RING_H
