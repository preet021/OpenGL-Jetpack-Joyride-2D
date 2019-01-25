#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick(direction_t dir);
    double width, height, speed_x, speed_y_ascend, speed_y_descend, acceleration, speed_x_act;
    bounding_box_t b;
private:
    VAO *object;
};

#endif // BALL_H
