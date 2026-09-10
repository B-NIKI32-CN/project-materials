
#include <cmath>
#include <iostream>

#include "forse.h"
#include "root.h"



using namespace std;

class Iterator
{
    private:
        const unsigned int max_quantity_particles;
        unsigned int now_quantity_particles {};

        float* x_coords_particles {new float[max_quantity_particles]};
        float* y_coords_particles {new float[max_quantity_particles]};

        float* x_velocity_particles {new float[max_quantity_particles]};
        float* y_velocity_particles {new float[max_quantity_particles]};

        float* x_forse_particles {new float[max_quantity_particles]};
        float* y_forse_particles {new float[max_quantity_particles]};


    public:

        Iterator() : max_quantity_particles{1184u}
        {
            cout << "Начинаем" << endl; 
        }
        ~Iterator() 
        {
        delete[] x_coords_particles;
        delete[] y_coords_particles;
        delete[] x_velocity_particles;
        delete[] y_velocity_particles;
        delete[] x_forse_particles;
        delete[] y_forse_particles;
        }

        void spawn_particle(float x, float y)
        {
            *(x_coords_particles+now_quantity_particles) = x;
            *(y_coords_particles+now_quantity_particles) = y;

            now_quantity_particles++;
            
        }

        float* getX_coords_particles()
        {
            return x_coords_particles;
        }

        float* getY_coords_particles()
        {
            return y_coords_particles;
        }

        void doIteration()
        {
            ForseSolver();
            Particles_update();

        }

        void ForseSolver()
        {
            for(unsigned int particle {}; particle<now_quantity_particles; particle++)
            {
                *(x_forse_particles+particle) = 0;
            }
            for(unsigned int first_particle {}; first_particle<now_quantity_particles; first_particle++)
            {
                for(unsigned int second_particle {first_particle+1}; second_particle<now_quantity_particles; second_particle++)
                {
                    float delta_x = *(x_coords_particles+second_particle) - *(x_coords_particles+first_particle);
                    float delta_y = *(y_coords_particles+second_particle) - *(y_coords_particles+first_particle);
                    float distance = pow((delta_x*delta_x + delta_y*delta_y), 0.5);

                    if(distance == 0)
                    {
                        cout << "Ебать его в рот, ДЕЛЕНИЕ НА НОЛЬ!" << endl;
                        continue;
                    }
                    
                    float Forse = SimpleForse(distance);

                    *(x_forse_particles+first_particle) += Forse*delta_x/distance;
                    *(y_forse_particles+first_particle) += Forse*delta_y/distance;

                    *(x_forse_particles+second_particle) += -Forse*delta_x/distance;
                    *(y_forse_particles+second_particle) += -Forse*delta_y/distance;

                }
            }
        }

        void Particles_update()
        {
            for(unsigned int particle {}; particle<now_quantity_particles; particle++)
            {
                *(x_velocity_particles+particle) += *(x_forse_particles+particle);
                *(y_velocity_particles+particle) += *(y_forse_particles+particle);

                *(x_forse_particles+particle) = 0u;
                *(y_forse_particles+particle) = 0u;

                
                *(x_coords_particles+particle) = *(x_velocity_particles+particle);
                *(y_coords_particles+particle) = *(y_velocity_particles+particle);

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
};