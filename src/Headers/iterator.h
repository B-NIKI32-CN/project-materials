#pragma once

struct Particle_box;

class Iterator
{
    private:
        Particle_box* particle_box;

    public:
        Iterator();
        ~Iterator();

        void spawn_particle(double , double);

        double* getX_coords_particles();
        double* getY_coords_particles();

        unsigned int get_quantity_particles();

        void show_particles_stats();

        void set_cold();

        void doIteration();
        void ForseSolver();
        void Particles_update();
};