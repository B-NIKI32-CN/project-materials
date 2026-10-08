#pragma once

struct Particle_box;

class Iterator
{
    private:
        Particle_box* particleBox;

        double particleMass;
        double deltaTime;

        double movability;

    public:
        Iterator(double, double, unsigned int);
        Iterator();
        ~Iterator();

        double* get_xCoordsParticles() const;
        double* get_yCoordsParticles() const;
        double get_deltaTime() const;
        unsigned int get_quantityParticles() const;
        void get_statsParticles() const;

        void set_zeroVelosityParticles();
        void set_deltaTime(double);

        unsigned int spawnParticle(double , double);
        unsigned int spawnHexagon(double , double, double, unsigned int);

        void doIteration();
        void forseSolver();
        void updateParticles();
};