#include "Headers/particle_box.h"

Particle_box::Particle_box(unsigned int max_quantity): max_quantity_particles(max_quantity)
{
    x_coords_particles   = new double[max_quantity_particles];
    y_coords_particles   = new double[max_quantity_particles];
    x_velocity_particles = new double[max_quantity_particles];
    y_velocity_particles = new double[max_quantity_particles];
    x_forse_particles    = new double[max_quantity_particles];
    y_forse_particles    = new double[max_quantity_particles];

}

Particle_box::~Particle_box()
{
    delete[] x_coords_particles;
    delete[] y_coords_particles;
    delete[] x_velocity_particles;
    delete[] y_velocity_particles;
    delete[] x_forse_particles;
    delete[] y_forse_particles;
}