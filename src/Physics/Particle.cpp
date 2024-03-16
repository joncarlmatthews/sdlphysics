#include <iostream>
#include "Particle.h"

Particle::Particle(float x, float y, float mass){
    std::cout << "Particle constructor called" << std::endl;
    this->position = Vec2(x, y);
    this->mass = mass;
}

Particle::~Particle(){
    std::cout << "Particle destructor called" << std::endl;
}