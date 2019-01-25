#include "main.h"

#ifndef BANK_H
#define BANK_H


class Bank {
public:
    Bank() {}
    Bank(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick(bool dir);
    bounding_box_t b;
    int rtime;
    bool present;
    double radius, thickness, speed_x, speed_y;
private:
    VAO *object;
};

#endif // BANK_H
