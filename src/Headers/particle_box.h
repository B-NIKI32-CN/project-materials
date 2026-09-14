#pragma once

struct Particle_box
{
    const unsigned int max_quantity_particles;    
    unsigned int now_quantity_particles;

    double* x_coords_particles;
    double* y_coords_particles;

    double* x_velocity_particles;
    double* y_velocity_particles;

    double* x_forse_particles;
    double* y_forse_particles;

    Particle_box(unsigned int);
    ~Particle_box();
};

