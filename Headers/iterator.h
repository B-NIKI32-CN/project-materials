class Iterator
{
    private:
        const unsigned int max_quantity_particles;
        unsigned int now_quantity_particles;

        float* x_coords_particles;
        float* y_coords_particles;

        float* x_velocity_particles;
        float* y_velocity_particles;

        float* x_forse_particles;
        float* y_forse_particles;

    public:
        Iterator();
        ~Iterator();
        void spawn_particle(float , float );
        float* getX_coords_particles();
        float* getY_coords_particles();
        void doIteration();
        void ForseSolver();
        void Particles_update();
};