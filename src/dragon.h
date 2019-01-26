#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick(direction_t dir);
    double width, height, radius1, radius2, speed_y;
    bool present;
    int t;
    bounding_box_t b;
private:
    VAO *object[6];
};

#endif // DRAGON_H
