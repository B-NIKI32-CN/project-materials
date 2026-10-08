#pragma once

struct Particle_box
{
    const unsigned int maxQuantityParticles;    
    unsigned int nowQuantityParticles;

    double* xCoordsParticles;
    double* yCoordsParticles;

    double* xVelocityParticles;
    double* yVelocityParticles;

    double* xForseParticles;
    double* yForseParticles;

    Particle_box(unsigned int);
    ~Particle_box();
};

