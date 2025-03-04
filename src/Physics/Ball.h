#ifndef BALL_H
#define BALL_H

#include "../types.h";
#include "../Graphics.h";
#include "Vec2.h";

typedef struct Ball {
    Vec2 position;
    Vec2 acceleration;
    Vec2 velocity;
    float32 mass;
    float32 radians;
    Ball(float32 x, float32 y, float32 mass, float32 radians); // Constructor
    ~Ball(); // Destructor
    void Draw();
} Ball;

#endif