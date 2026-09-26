#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Headers/forse.h"
#include "Headers/heat_dissipation.h"
#include "Headers/root.h"
#include "Headers/customs.h"
#include "Headers/iterator.h"





int main()
{
    sf::CircleShape All_sprites_group[1184];

    Iterator iterator(particle_mass, iteration_delta_time, 1184u);

    sf::RenderWindow window(sf::VideoMode({SW, SH}), "How it ");

    // std::cout << static_cast<unsigned int>(1/iterator.get_delta_time()) << std::endl;

    std::cout << "Число итераций на кадр: " << static_cast<unsigned int>(1/ (FPS * iteration_delta_time)) << std::endl;

    window.setFramerateLimit(FPS);
    
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
                    if(g<0)
                    {
                        g = 0;
                    }
                    g = (g+1)*2;
                    std::cout << "g - " << g <<std::endl;
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::Down)
                {
                    if(g>0)
                    {
                        g = 0;
                    }
                    g = (g-1)*2;
                    std::cout << "g - " << g <<std::endl;

                }
                if (keyPressed->scancode == sf::Keyboard::Scan::C)
                {
                    iterator.set_cold();
                }
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::CircleShape shape = sf::CircleShape(5.f, 36);
                shape.setOrigin(shape.getGeometricCenter());
                shape.setFillColor(sf::Color::Blue);
                All_sprites_group[iterator.get_quantity_particles()] = shape;

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                iterator.spawn_particle(static_cast<double>(mousePos.x), static_cast<double>(mousePos.y));
                iterator.show_particles_stats();
            }
            
        }
        for(unsigned i {}; i<static_cast<unsigned int>(1/ (FPS * iteration_delta_time)); i++)
        {
        iterator.doIteration();
        }
        

        window.clear();
        for(unsigned int sprite_num {}; sprite_num<iterator.get_quantity_particles();)
        {
            // std::cout << sprite_num << std::endl;
            All_sprites_group[sprite_num].setPosition({static_cast<float>(*(iterator.getX_coords_particles()+sprite_num)),
                                                       static_cast<float>(*(iterator.getY_coords_particles()+sprite_num))});
            window.draw(All_sprites_group[sprite_num]);
            sprite_num++;
        }
        // window.draw(shape);
        window.display();
    }
    return 0;
}