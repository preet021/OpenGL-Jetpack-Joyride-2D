#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y,float far, color_t color);
    glm::vec3 position;
    float rotation;
    int count;
    void draw(glm::mat4 VP);
    void tick();
    double thickness, length, width, x;
private:
    VAO *object;
};

#endif // MAGNET_H
