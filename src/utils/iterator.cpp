#include "Headers/iterator.h"
#include "Headers/root.h"       
#include "Headers/customs.h"    
#include "Headers/forse.h" 
#include "Headers/particle_box.h"

#include <iostream>
#include <cmath>

Iterator::Iterator(): particle_box(new Particle_box(1184u)) {}

Iterator::~Iterator() {delete particle_box;}

void Iterator::spawn_particle(double x, double y)
{
    particle_box->x_coords_particles[particle_box->now_quantity_particles] = x;
    particle_box->y_coords_particles[particle_box->now_quantity_particles] = y;
    ++(particle_box->now_quantity_particles);
    std::cout << "contact" << std::endl;
}

double* Iterator::getY_coords_particles()
{
    return particle_box->y_coords_particles;
}

double* Iterator::getX_coords_particles()
{
    return particle_box->x_coords_particles;
}

unsigned int Iterator::get_quantity_particles()
{
    return particle_box->now_quantity_particles;
}

void Iterator::show_particles_stats()
{
    for(unsigned int particle {}; particle<particle_box->now_quantity_particles; particle++)
    {
        std::cout << "num of particle" << particle << std::endl;
        std::cout << "coords, x: " << *(particle_box->x_coords_particles+particle) << "\t y: " << *(particle_box->y_coords_particles+particle) << std::endl;
        std::cout << "velosity, x: " << *(particle_box->x_velocity_particles+particle) << "\t y: " << *(particle_box->y_velocity_particles+particle) << std::endl << std::endl;
    }
}

void Iterator::set_cold()
{
    for(unsigned int particle {}; particle<particle_box->now_quantity_particles; particle++)
    {
    *(particle_box->x_velocity_particles+particle) = 0;
    *(particle_box->y_velocity_particles+particle) = 0;
    }
}

void Iterator::doIteration()
{
    ForseSolver();
    Particles_update();

}

void Iterator::ForseSolver()
{
    for(unsigned int particle {}; particle<particle_box->now_quantity_particles; particle++)
    {
        *(particle_box->x_forse_particles+particle) = 0;
        *(particle_box->y_forse_particles+particle) = g;
    }
    unsigned int count_of_interaction {};
    for(unsigned int first_particle {}; first_particle<particle_box->now_quantity_particles; first_particle++)
    {
        for(unsigned int second_particle {first_particle+1}; second_particle<particle_box->now_quantity_particles; second_particle++)
        {
            double delta_x = *(particle_box->x_coords_particles+second_particle) - *(particle_box->x_coords_particles+first_particle);
            double delta_y = *(particle_box->y_coords_particles+second_particle) - *(particle_box->y_coords_particles+first_particle);
            double distance = pow((delta_x*delta_x + delta_y*delta_y), 0.5);

            if(distance == 0)
            {
                std::cout << "Ебать его в рот, ДЕЛЕНИЕ НА НОЛЬ!" << std::endl;
                continue;
            }
            
            // float Forse = -50/distance/distance
            double Forse = SimpleForse(distance);

            // this->show_particles_stats();

            *(particle_box->x_forse_particles+first_particle) += Forse*delta_x/distance;
            *(particle_box->y_forse_particles+first_particle) += Forse*delta_y/distance;

            *(particle_box->x_forse_particles+second_particle) += -Forse*delta_x/distance;
            *(particle_box->y_forse_particles+second_particle) += -Forse*delta_y/distance;

            // this->show_particles_stats();
            count_of_interaction++;
            // std::cout << first_particle << "\t" << second_particle <<std::endl;
        }
    }
    // std::cout << " "<< now_quantity_particles*(now_quantity_particles-1)/2 << "   " <<count_of_interaction << std::endl << std::endl;
}

void Iterator::Particles_update()
{
    for(unsigned int particle {}; particle<particle_box->now_quantity_particles; particle++)
    {
        *(particle_box->x_velocity_particles+particle) += *(particle_box->x_forse_particles+particle);
        *(particle_box->y_velocity_particles+particle) += *(particle_box->y_forse_particles+particle);

        *(particle_box->x_forse_particles+particle) = 0u;
        *(particle_box->y_forse_particles+particle) = 0u;

        
        *(particle_box->x_coords_particles+particle) += *(particle_box->x_velocity_particles+particle);
        *(particle_box->y_coords_particles+particle) += *(particle_box->y_velocity_particles+particle);

        if(*(particle_box->x_coords_particles+particle)<0)
        {
            *(particle_box->x_velocity_particles+particle) *= -1;
            *(particle_box->x_coords_particles+particle) = 0;
        }
        else if(*(particle_box->x_coords_particles+particle)>SW)
        {
            *(particle_box->x_velocity_particles+particle) *= -1;
            *(particle_box->x_coords_particles+particle) = SW;
        }
        if(*(particle_box->y_coords_particles+particle)<0)
        {
            *(particle_box->y_velocity_particles+particle) *= -1;
            *(particle_box->y_coords_particles+particle) = 0;
        }
        else if(*(particle_box->y_coords_particles+particle)>SH)
        {
            *(particle_box->y_velocity_particles+particle) *= -1;
            *(particle_box->y_coords_particles+particle) = SH;
        }                
    }
}