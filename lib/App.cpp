//
// Created by Mikhail Tsaritsyn on 10.12.2021.
//

#include <iostream>

#include "App.h"

App::App(const sf::Vector2u& window_size, const std::string &title)
        : m_window(sf::VideoMode(window_size.x, window_size.y), title)
{
    auto view = m_scene.getCameraView(m_camera_ind);

    auto scaleX = (float)window_size.x / view.getWidth();
    auto scaleY = (float)window_size.y / view.getHeight();
//    std::cout << scaleX << ' ' << scaleY << '\n';

    m_texture.create(view.getWidth(), view.getHeight());
    m_background = sf::Sprite(m_texture);
    m_background.setScale(scaleX, scaleY);
}

void App::run() {
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        update();
        refresh();
    }
}

void App::refresh() {
    auto view = m_scene.getCameraView(m_camera_ind);
    m_texture.update(view.data());
    m_background.setTexture(m_texture);
    m_window.clear();
    m_window.draw(m_background);
    m_window.display();
}

void App::update() {
    m_scene.updateCameraView(m_camera_ind);
}
