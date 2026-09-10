#include <SFML/Graphics.hpp>
#include <iostream>

#include <cmath>

unsigned int SW = 600u;
unsigned int SH = 600u;

float g = 0;

float E1 = -12;
float E2 = 8;
float r1 = 30;
float r2 = 50;
float r3 = 60;

float a1 = 4*E1*r1 / (r2 - r1);
float b1 = -4*E1*std::pow(r1, 2) / (r2 - r1);

float a2 = -4*E1 / std::pow((r2 - r1), 2);
float b2 = 4*E1*(r1+r2) / std::pow((r2 - r1), 2);
float c2 = -4*E1*r1*r2 / std::pow((r2 - r1), 2);

float a3 = -4*std::pow(E1, 2) / E2 / std::pow((r2 - r1), 2);
float b3 = 8*std::pow(E1, 2)*r2 / E2 / std::pow((r2 - r1), 2) - 4*E1 / (r2 - r1);
float c3 = -( (4 * std::pow(E1, 2) * std::pow(r2, 2)) / (E2 * std::pow((r2 - r1), 2)) ) + ( (4 * E1 * r2) / (r2 - r1) );

float A = a3 * std::pow(r3, 2) + b3 * r3 + c3;
float B = 2 * a3 * r3 + b3;

float a4 = A / B + r3;
float b4 = A * (r3 - a4);


float SimpleForse(float r)
{
    if(r < r1)
    {
        return -b1 / std::pow(r, 2);
    }
    else if(r < r2)
    {
        return 2 * a2 * r + b2;
    }
    else if(r<r3)
    {
        return 2 * a3 * r  + b3;
    }
    else
    {
        return -b4 / std::pow((r - a4), 2);
    }
}

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
            std::cout << "Начинаем" << std::endl; 
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
            std::cout << "contact" << std::endl;
        }

        float* getX_coords_particles()
        {
            return x_coords_particles;
        }

        float* getY_coords_particles()
        {
            return y_coords_particles;
        }

        unsigned int get_quantity_particles()
        {
            return now_quantity_particles;
        }

        void show_particles_stats()
        {
            for(unsigned int particle {}; particle<now_quantity_particles; particle++)
            {
                std::cout << "num of particle" << particle << std::endl;
                std::cout << "coords, x: " << *(x_coords_particles+particle) << "\t y: " << *(y_coords_particles+particle) << std::endl;
                std::cout << "velosity, x: " << *(x_velocity_particles+particle) << "\t y: " << *(y_velocity_particles+particle) << std::endl << std::endl;
            }
        }

        void set_cold()
        {
            for(unsigned int particle {}; particle<now_quantity_particles; particle++)
            {
            *(x_velocity_particles+particle) = 0;
            *(y_velocity_particles+particle) = 0;
            }
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
                *(y_forse_particles+particle) = g;
            }
            unsigned int count_of_interaction {};
            for(unsigned int first_particle {}; first_particle<now_quantity_particles; first_particle++)
            {
                for(unsigned int second_particle {first_particle+1}; second_particle<now_quantity_particles; second_particle++)
                {
                    float delta_x = *(x_coords_particles+second_particle) - *(x_coords_particles+first_particle);
                    float delta_y = *(y_coords_particles+second_particle) - *(y_coords_particles+first_particle);
                    float distance = pow((delta_x*delta_x + delta_y*delta_y), 0.5);

                    if(distance == 0)
                    {
                        std::cout << "Ебать его в рот, ДЕЛЕНИЕ НА НОЛЬ!" << std::endl;
                        continue;
                    }
                    
                    // float Forse = -50/distance/distance
                    float Forse = SimpleForse(distance)/2;

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

        void Particles_update()
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
};


int main()
{
    sf::CircleShape All_sprites_group[1184];
    Iterator iterator;
    // В SFML 3 размер передается в фигурных скобках {ширина, высота}
    sf::RenderWindow window(sf::VideoMode({SW, SH}), "How it ");

    window.setFramerateLimit(60);

    // Создаем зеленый круг (в SFML 3 радиус передается через float)
    // sf::CircleShape shape(50.f, 3);
    // shape.setFillColor(sf::Color::Green);
    // shape.setPosition({375.f, 275.f});
    // shape.setOrigin(shape.getGeometricCenter());
    
    // Главный цикл программы
    while (window.isOpen())
    {
        // Новый синтаксис обработки событий для SFML 3
        while (const std::optional event = window.pollEvent())
        {
            // Проверка на закрытие окна
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            // Проверка нажатия клавиши Escape
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
                {
                    window.close();
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::A)
                {
                    iterator.show_particles_stats();
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::Up)
                {
                    g += 0.01;
                    std::cout << "g" << g <<std::endl;
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::Down)
                {
                    g -= 0.01;
                    std::cout << "g" << g <<std::endl;

                }
                if (keyPressed->scancode == sf::Keyboard::Scan::C)
                {
                    iterator.set_cold();
                }
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::CircleShape shape = sf::CircleShape(25.f, 36);
                shape.setOrigin(shape.getGeometricCenter());
                shape.setFillColor(sf::Color::Blue);
                All_sprites_group[iterator.get_quantity_particles()] = shape;

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                iterator.spawn_particle(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                // iterator.show_particles_stats();
            }
            
        }

        iterator.doIteration();

        window.clear();
        for(unsigned int sprite_num {}; sprite_num<iterator.get_quantity_particles();)
        {
            // std::cout << sprite_num << std::endl;
            All_sprites_group[sprite_num].setPosition({*(iterator.getX_coords_particles()+sprite_num), *(iterator.getY_coords_particles()+sprite_num)});
            window.draw(All_sprites_group[sprite_num]);
            sprite_num++;
        }
        // window.draw(shape);
        window.display();
    }

    return 0;
}