#include "Headers/iterator.h"
#include "Headers/root.h"       // если нужны SW/SH
#include "Headers/customs.h"    // если нужен g
#include "Headers/forse.h"      // если нужен SimpleForse

#include <iostream>
#include <cmath>

Iterator::Iterator()
    : max_quantity_particles(1184u)
{
    x_coords_particles   = new double[max_quantity_particles];
    y_coords_particles   = new double[max_quantity_particles];
    x_velocity_particles = new double[max_quantity_particles];
    y_velocity_particles = new double[max_quantity_particles];
    x_forse_particles    = new double[max_quantity_particles];
    y_forse_particles    = new double[max_quantity_particles];

    std::cout << "Начинаем" << std::endl;
}

Iterator::~Iterator()
{
    delete[] x_coords_particles;
    delete[] y_coords_particles;
    delete[] x_velocity_particles;
    delete[] y_velocity_particles;
    delete[] x_forse_particles;
    delete[] y_forse_particles;
}

void Iterator::spawn_particle(double x, double y)
{
    x_coords_particles[now_quantity_particles] = x;
    y_coords_particles[now_quantity_particles] = y;
    ++now_quantity_particles;
    std::cout << "contact" << std::endl;
}

double* Iterator::getY_coords_particles()
{
    return y_coords_particles;
}

double* Iterator::getX_coords_particles()
{
    return x_coords_particles;
}

unsigned int Iterator::get_quantity_particles()
{
    return now_quantity_particles;
}

void Iterator::show_particles_stats()
{
    for(unsigned int particle {}; particle<now_quantity_particles; particle++)
    {
        std::cout << "num of particle" << particle << std::endl;
        std::cout << "coords, x: " << *(x_coords_particles+particle) << "\t y: " << *(y_coords_particles+particle) << std::endl;
        std::cout << "velosity, x: " << *(x_velocity_particles+particle) << "\t y: " << *(y_velocity_particles+particle) << std::endl << std::endl;
    }
}

void Iterator::set_cold()
{
    for(unsigned int particle {}; particle<now_quantity_particles; particle++)
    {
    *(x_velocity_particles+particle) = 0;
    *(y_velocity_particles+particle) = 0;
    }
}

void Iterator::doIteration()
{
    ForseSolver();
    Particles_update();

}

void Iterator::ForseSolver()
{
    for(unsigned int particle {}; particle<now_quantity_particles; particle++)
    {
        *(x_forse_particles+particle) = 0;
        *(y_forse_particles+particle) = g;
    }
    unsigned int count_of_interaction {};
    for(unsigned int first_particle {}; first_particle<now_quantity_particles; first_particle++)
    {
        for(unsigned int second_particle {first_particle+1}; second_particle<now_quantity_particles; second_particle++)
        {
            double delta_x = *(x_coords_particles+second_particle) - *(x_coords_particles+first_particle);
            double delta_y = *(y_coords_particles+second_particle) - *(y_coords_particles+first_particle);
            double distance = pow((delta_x*delta_x + delta_y*delta_y), 0.5);

            if(distance == 0)
            {
                std::cout << "Ебать его в рот, ДЕЛЕНИЕ НА НОЛЬ!" << std::endl;
                continue;
            }
            
            // float Forse = -50/distance/distance
            double Forse = SimpleForse(distance)/2;

            // this->show_particles_stats();

            *(x_forse_particles+first_particle) += Forse*delta_x/distance;
            *(y_forse_particles+first_particle) += Forse*delta_y/distance;

            *(x_forse_particles+second_particle) += -Forse*delta_x/distance;
            *(y_forse_particles+second_particle) += -Forse*delta_y/distance;

            // this->show_particles_stats();
            count_of_interaction++;
            // std::cout << first_particle << "\t" << second_particle <<std::endl;
        }
    }
    // std::cout << " "<< now_quantity_particles*(now_quantity_particles-1)/2 << "   " <<count_of_interaction << std::endl << std::endl;
}

void Iterator::Particles_update()
{
    for(unsigned int particle {}; particle<now_quantity_particles; particle++)
    {
        *(x_velocity_particles+particle) += *(x_forse_particles+particle);
        *(y_velocity_particles+particle) += *(y_forse_particles+particle);

        *(x_forse_particles+particle) = 0u;
        *(y_forse_particles+particle) = 0u;

        
        *(x_coords_particles+particle) += *(x_velocity_particles+particle);
        *(y_coords_particles+particle) += *(y_velocity_particles+particle);

        if(*(x_coords_particles+particle)<0)
        {
            *(x_velocity_particles+particle) *= -1;
            *(x_coords_particles+particle) = 0;
        }
        else if(*(x_coords_particles+particle)>SW)
        {
            *(x_velocity_particles+particle) *= -1;
            *(x_coords_particles+particle) = SW;
        }
        if(*(y_coords_particles+particle)<0)
        {
            *(y_velocity_particles+particle) *= -1;
            *(y_coords_particles+particle) = 0;
        }
        else if(*(y_coords_particles+particle)>SH)
        {
            *(y_velocity_particles+particle) *= -1;
            *(y_coords_particles+particle) = SH;
        }                
    }
}