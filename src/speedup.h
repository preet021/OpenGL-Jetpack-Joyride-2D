#include "main.h"

#ifndef SPEEDUP_H
#define SPEEDUP_H


class Speedup {
public:
    Speedup() {}
    Speedup(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick(bool dir);
    bounding_box_t b;
    int rtime;
    bool present;
    double radius1, radius2, thickness, speed_x, speed_y;
private:
    VAO *object;
};

#endif // SPEEDUP_H
