#pragma once

#include <SFML/Graphics.hpp>


class Scene
{
    private:
        sf::RenderWindow window;

    public:
        void handle_events();
        void update();
        void display();
};