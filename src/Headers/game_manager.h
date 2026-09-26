#pragma  once
#include <iostream>
#include <SFML/Graphics.hpp>

class Scene;

class GameManager
{
    private:
        Scene* scene;
        sf::RenderWindow window;

    public:
        void work();
        void set_scene(Scene*);

};