#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Headers/forse.h"
#include "Headers/root.h"
#include "Headers/customs.h"
#include "Headers/iterator.h"





int main()
{
    sf::CircleShape All_sprites_group[1184];
    Iterator iterator;
    // В SFML 3 размер передается в фигурных скобках {ширина, высота}
    sf::RenderWindow window(sf::VideoMode({SW, SH}), "How it ");

    window.setFramerateLimit(60); 
    
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
                sf::CircleShape shape = sf::CircleShape(15.f, 36);
                shape.setOrigin(shape.getGeometricCenter());
                shape.setFillColor(sf::Color::Blue);
                All_sprites_group[iterator.get_quantity_particles()] = shape;

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                iterator.spawn_particle(static_cast<double>(mousePos.x), static_cast<double>(mousePos.y));
                // iterator.show_particles_stats();
            }
            
        }

        iterator.doIteration();

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