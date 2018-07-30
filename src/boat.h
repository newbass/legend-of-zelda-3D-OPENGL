#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    int mode;
    int wind;
    int jump;
    int point;
    float health;
    int fire;
    int boss;
    int shoot;
    int hunt;
    float heliheight;
    float heliangle;
    int windangle;
    float windspeed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(int k, int m, int is);
    void rotate(int flag);
    void move_forward(int flag);
    double speed;
    double speedy;
    double speedw;
private:
    VAO *object;
};

#endif // BOAT_H
