#pragma once

class Iterator
{
    private:
        const unsigned int max_quantity_particles;
        unsigned int now_quantity_particles;

        double* x_coords_particles;
        double* y_coords_particles;

        double* x_velocity_particles;
        double* y_velocity_particles;

        double* x_forse_particles;
        double* y_forse_particles;

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