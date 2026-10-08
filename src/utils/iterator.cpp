#include "Headers/iterator.h"
#include "Headers/root.h"       
#include "Headers/customs.h"    
#include "Headers/forse.h" 
#include "Headers/heat_dissipation.h"
#include "Headers/particle_box.h"

#include <iostream>
#include <cmath>

using namespace std;

// Связь параметров итератора с числом проходящих итераций на данной расстонянии: N = (delta_r * sqrt(particleMass) / (deltaTime * sqrt(2*E)),
// E - энергия частицы
// delta_r - выбранная дистанция, выбирается исхотя из функции сил 
// particleMass - масса частицы
// deltaTime - время итерации
// N - число произошедших итераций на выделенной дистанции, эмпирически выявлено что оптимальное число для интересующей дистанции не менне 10 будет достаточным

Iterator::Iterator(double mass, double deltaTime, unsigned int max_quantity_particles): particleBox(new Particle_box(max_quantity_particles))
{
    this->particleMass = mass;
    this->deltaTime = deltaTime;

    this->movability = 1/particleMass;
}

Iterator::Iterator(): Iterator(1.f, 0.01f, 1184u) {}

Iterator::~Iterator()
{
    delete particleBox;
}



double* Iterator::get_yCoordsParticles() const
{
    return particleBox->yCoordsParticles;
}

double* Iterator::get_xCoordsParticles() const
{
    return particleBox->xCoordsParticles;
}
double Iterator::get_deltaTime() const
{
    return deltaTime;
}

unsigned int Iterator::get_quantityParticles() const
{
    return particleBox->nowQuantityParticles;
}

void Iterator::get_statsParticles() const
{
    for(unsigned int particle {}; particle<particleBox->nowQuantityParticles; particle++)
    {   
        std::cout << "num of particle" << particle << std::endl;
        std::cout << "coords, x: " << *(particleBox->xCoordsParticles+particle) << "\t y: " << *(particleBox->yCoordsParticles+particle) << std::endl;
        std::cout << "velosity, x: " << *(particleBox->xVelocityParticles+particle) << "\t y: " << *(particleBox->yVelocityParticles+particle) << std::endl << std::endl;
    }
}



void Iterator::set_zeroVelosityParticles()
{
    for(unsigned int particle {}; particle<particleBox->nowQuantityParticles; particle++)
    {
    particleBox->xVelocityParticles[particle] = 0;
    particleBox->yVelocityParticles[particle] = 0;
    }
}

void Iterator::set_deltaTime(double time)
{
    this->deltaTime = time; 
}



unsigned int Iterator::spawnParticle(double cursorX, double cursorY)
{
    particleBox->xCoordsParticles[particleBox->nowQuantityParticles] = cursorX;
    particleBox->yCoordsParticles[particleBox->nowQuantityParticles] = cursorY;
    ++(particleBox->nowQuantityParticles);
    return 1u;
}

unsigned int Iterator::spawnHexagon(double cursorX, double cursorY, double radius, unsigned int countOfParticleOnSide)
{
    double diagonalDeltaX {radius/2}; 
    double diagonalDeltaY {radius/2 * sqrt(3)};

    unsigned int maxHeight {countOfParticleOnSide*2-2};
    unsigned int midHeight {countOfParticleOnSide-1};

    for(unsigned int height {}; height <= maxHeight; height++)
    {
        unsigned int maxWidth {maxHeight - abs(static_cast<int>((midHeight - height)))}; // число атомов в линии -1
        for(unsigned int width {}; width <= maxWidth; width++)
        {
            Iterator::spawnParticle(cursorX + diagonalDeltaX * abs(static_cast<int>((midHeight - height))) + radius * width,
                                     cursorY + diagonalDeltaY * height);
        }
    }
    return 3*(pow(countOfParticleOnSide, 2) - countOfParticleOnSide) + 1; 
}



void Iterator::doIteration()
{
    forseSolver();
    updateParticles();

}

void Iterator::forseSolver()
{
    for(unsigned int particle {}; particle<particleBox->nowQuantityParticles; particle++)
    {
        particleBox->xForseParticles[particle] = 0;
        particleBox->yForseParticles[particle] = g*particleMass;
    }
    unsigned int count_of_interaction {};
    for(unsigned int first_particle {}; first_particle<particleBox->nowQuantityParticles; first_particle++)
    {
        for(unsigned int second_particle {first_particle+1}; second_particle<particleBox->nowQuantityParticles; second_particle++)
        {
            double delta_x = particleBox->xCoordsParticles[second_particle] - particleBox->xCoordsParticles[first_particle];
            double delta_y = particleBox->yCoordsParticles[second_particle] - particleBox->yCoordsParticles[first_particle];
            double distance = pow((delta_x*delta_x + delta_y*delta_y), 0.5);

            if(distance == 0)
            {
                std::cout << "Ебать его в рот, ДЕЛЕНИЕ НА НОЛЬ!" << std::endl;
                continue;
            }
            
            double Forse = SimpleForse(distance);

            particleBox->xForseParticles[first_particle] += Forse*delta_x/distance;
            particleBox->yForseParticles[first_particle] += Forse*delta_y/distance;

            particleBox->xForseParticles[second_particle] += -Forse*delta_x/distance;
            particleBox->yForseParticles[second_particle] += -Forse*delta_y/distance;
        }
    }
}

void Iterator::updateParticles()
{
    for(unsigned int particle {}; particle<particleBox->nowQuantityParticles; particle++)
    {
        particleBox->xVelocityParticles[particle] += particleBox->xForseParticles[particle] * movability * deltaTime;
        particleBox->yVelocityParticles[particle] += particleBox->yForseParticles[particle] * movability * deltaTime;

        heat_dissipation(particleBox->xVelocityParticles+particle, &deltaTime);
        heat_dissipation(particleBox->yVelocityParticles+particle, &deltaTime);

        particleBox->xForseParticles[particle] = 0u;
        particleBox->yForseParticles[particle] = 0u;

        
        particleBox->xCoordsParticles[particle] += particleBox->xVelocityParticles[particle] * deltaTime;
        particleBox->yCoordsParticles[particle] += particleBox->yVelocityParticles[particle] * deltaTime;

        if(*(particleBox->xCoordsParticles+particle)<0)
        {
            particleBox->xVelocityParticles[particle] *= -1;
            particleBox->xCoordsParticles[particle] = 0;
        }
        else if(*(particleBox->xCoordsParticles+particle)>SW)
        {
            particleBox->xVelocityParticles[particle] *= -1;
            particleBox->xCoordsParticles[particle] = SW;
        }
        if(*(particleBox->yCoordsParticles+particle)<0)
        {
            particleBox->yVelocityParticles[particle] *= -1;
            particleBox->yCoordsParticles[particle] = 0;
        }
        else if(*(particleBox->yCoordsParticles+particle)>SH)
        {
            particleBox->yVelocityParticles[particle] *= -1;
            particleBox->yCoordsParticles[particle] = SH;
        }                
    }
}