#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double speed_y, cx, cy;
    bool present, width, height;
    bounding_box_t b;
private:
    VAO *object;
};

#endif // BOOMERANG_H
