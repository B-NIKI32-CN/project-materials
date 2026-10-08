#include <iostream>

#include "Headers/particle_box.h"

Particle_box::Particle_box(unsigned int max_quantity): maxQuantityParticles(max_quantity)
{
    nowQuantityParticles = 0;
    // std::cout << nowQuantityParticles << std::endl;
    xCoordsParticles   = new double[maxQuantityParticles];
    yCoordsParticles   = new double[maxQuantityParticles];
    xVelocityParticles = new double[maxQuantityParticles];
    yVelocityParticles = new double[maxQuantityParticles];
    xForseParticles    = new double[maxQuantityParticles];
    yForseParticles    = new double[maxQuantityParticles];

}

Particle_box::~Particle_box()
{
    delete[] xCoordsParticles;
    delete[] yCoordsParticles;
    delete[] xVelocityParticles;
    delete[] yVelocityParticles;
    delete[] xForseParticles;
    delete[] yForseParticles;
}