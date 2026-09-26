#pragma once

struct Particle_box;

class Iterator
{
    private:
        Particle_box* particle_box;

        double particle_mass;
        double delta_time;

        double movability;

    public:
        Iterator(double, double, unsigned int);
        Iterator();
        ~Iterator();

        void spawn_particle(double , double);

        double* getX_coords_particles();
        double* getY_coords_particles();
        double get_delta_time();

        unsigned int get_quantity_particles();

        void show_particles_stats();

        void set_cold();

        void doIteration();
        void ForseSolver();
        void Particles_update();
};