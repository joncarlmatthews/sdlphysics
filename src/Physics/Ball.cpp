#include <iostream>
#include "../Graphics.h"
#include "Ball.h"

Ball::Ball(float32 x, float32 y, float32 mass, uint32 radius){
    std::cout << "Ball constructor called" << std::endl;
    this->position = Vec2(x, y);
    this->mass = mass;
    this->radius = radius;
}

Ball::~Ball(){
    std::cout << "Ball destructor called" << std::endl;
}

void Ball::Draw(){
    Graphics::DrawFillCircle(this->position.x, this->position.y, this->radius, 0xFFFFFFFF);
}