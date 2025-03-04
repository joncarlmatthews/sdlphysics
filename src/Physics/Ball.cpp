#include <iostream>
#include "../Graphics.h"
#include "Ball.h"

Ball::Ball(float32 x, float32 y, float32 mass, float32 radians){
    std::cout << "Ball constructor called" << std::endl;
    this->position = Vec2(x, y);
    this->mass = mass;
    this->radians = radians;
}

Ball::~Ball(){
    std::cout << "Ball destructor called" << std::endl;
}

void Ball::Draw(){
    Graphics::DrawFillCircle(this->position.x, this->position.y, this->radians, 0xFFFFFFFF);
}