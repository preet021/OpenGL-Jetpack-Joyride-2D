#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coin {
public:
    Coin() {}
    Coin(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void tick(bool dir);
    void draw(glm::mat4 VP);
    double radius, speed_x;
    bounding_box_t b;
private:
    VAO *object;
};

#endif // COIN_H
