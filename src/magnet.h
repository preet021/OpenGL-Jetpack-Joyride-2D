#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet {
public:
    Magnet() {}

    Magnet(color_t color);
    glm::vec3 position;
    float rotation;
    int direction, ctime;
    void tick();
    void draw(glm::mat4 VP);
    double thickness, length, width;
    bool present;
private:
    VAO *object;
};

#endif // MAGNET_H
