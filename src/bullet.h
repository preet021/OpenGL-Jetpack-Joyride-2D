#include "main.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y);
    glm::vec3 position;
    float rotation;
    void tick();
    void draw(glm::mat4 VP);
    double radius, speed_x, speed_y, acceleration;
    bounding_box_t b;
    int type;
private:
    VAO *object;
};

#endif // BULLET_H
