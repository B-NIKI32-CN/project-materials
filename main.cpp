#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>


#include "Headers/forse.h"
#include "Headers/heat_dissipation.h"
#include "Headers/root.h"
#include "Headers/customs.h"
#include "Headers/iterator.h"

// std::mutex dataMutex;

void renderingThread(sf::RenderWindow* window, const Iterator* iterator)
{
    window->setActive(true);

    sf::CircleShape All_sprites_group[1184];
    sf::CircleShape shape = sf::CircleShape(5.f, 36);
    shape.setOrigin(shape.getGeometricCenter());
    shape.setFillColor(sf::Color::Blue);
    for(unsigned int numOfShape {0}; numOfShape < 1000; numOfShape++)
    {
        
        All_sprites_group[numOfShape] = shape;
        // std::cout << numOfShape << std::endl;
    }

    while(window->isOpen())
    {
        // std::lock_guard<std::mutex> lock(dataMutex);
        window->clear();
        for(unsigned int sprite_num {}; sprite_num<iterator->get_quantityParticles(); sprite_num++)
        {
            // std::cout << sprite_num << std::endl;
            All_sprites_group[sprite_num].setPosition({static_cast<float>(*(iterator->get_xCoordsParticles()+sprite_num)),
                                                       static_cast<float>(*(iterator->get_yCoordsParticles()+sprite_num))});
            window->draw(All_sprites_group[sprite_num]);
            
        }
        window->display();
    }
}





int main()
{
    

    sf::CircleShape All_sprites_group[1184];
    sf::CircleShape shape = sf::CircleShape(5.f, 36);
    shape.setOrigin(shape.getGeometricCenter());
    shape.setFillColor(sf::Color::Blue);
    for(unsigned int numOfShape {}; numOfShape < 1000; numOfShape++)
    {
        
        All_sprites_group[numOfShape] = shape;
        // std::cout << numOfShape << std::endl;
    }

    Iterator iterator(particle_mass, iteration_delta_time, 1184u);

    sf::RenderWindow window(sf::VideoMode({SW, SH}), "How it ");

    window.setActive(false);

    std::thread thread(&renderingThread, &window, &iterator);

    sf::Clock clock;

    float timeBuffer {0.0f};
    float timeCounter {0.0f};
    float timeLeft{0.0f};

    unsigned int iterationCounter {0u};
    float coreCounter {0.0f};

    float completenessIteration {};
    float loopIteration {};

    while (window.isOpen())
    {
        coreCounter+=1;

        timeLeft = clock.restart().asSeconds();
        timeCounter += timeLeft;
        timeBuffer += timeLeft;

        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
                {
                    window.close();
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::A)
                {
                    iterator.get_statsParticles();
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::D)
                {
                    timeBuffer = 0;
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
                    iterator.set_zeroVelosityParticles();
                }
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    iterator.spawnParticle(static_cast<double>(mousePos.x), static_cast<double>(mousePos.y));
                    iterator.get_statsParticles();
                }   
                else if (mousePressed->button == sf::Mouse::Button::Right)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    iterator.spawnHexagon(static_cast<double>(mousePos.x), static_cast<double>(mousePos.y), bondRange, 6);
                    iterator.get_statsParticles();
                }
            } 
                
            
        }
        
        

        if (timeCounter>1)
        {
            completenessIteration = iterationCounter*iteration_delta_time/timeCounter;
            loopIteration = iterationCounter/coreCounter;
            std::cout << " Итераций в секунду "<< iterationCounter/timeCounter << std::endl;
            std::cout << " Полнота итерирования "<< completenessIteration  << std::endl;
            std::cout << " Среднее время цикла  "<<  timeCounter/coreCounter << std::endl;
            std::cout << " Итерируемое  время  "<< iterator.get_deltaTime() << std::endl;
            std::cout << " Итераций на цикл "<< loopIteration << std::endl << std::endl;
            if (completenessIteration < 0.95)
            {
                // iteration_delta_time /= completenessIteration;
                iterator.set_deltaTime(iterator.get_deltaTime()/completenessIteration);
            }

            if (loopIteration >= 100)
            {
                timeBuffer = 0;
            }
            iterationCounter = 0;
            timeCounter = 0;
            coreCounter = 0;
        }

        while(timeBuffer >= iteration_delta_time)
        {
            
            iterator.doIteration();
            iterationCounter += 1;
            timeBuffer -= iteration_delta_time;
        }
    
    }
    thread.join();
    return 0;
}