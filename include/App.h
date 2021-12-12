//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#ifndef PHYSICS_APP_H
#define PHYSICS_APP_H

#include <SFML/Graphics.hpp>

#include "scenes/Scene.h"

class App {
    sf::RenderWindow m_window;
    sf::Sprite m_background;
    sf::Texture m_texture;
    Scene m_scene;
    unsigned m_camera_ind = 0;


public:

    App(const sf::Vector2u& window_size, const std::string& title);

    void run();

    void update();

    void refresh();

};


#endif //PHYSICS_APP_H
