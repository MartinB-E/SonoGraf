/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** SonoGraf
*/

#include "SonoGraf.hpp"
#include <iostream>

SonoGraf::SonoGraf() 
    : _output(_input, _processor), _window(sf::VideoMode({800, 600}), "SonoGraf"), _menu(_window)
{
    _window.setFramerateLimit(60);
    _menu.addButton("PLAY", [this]() {
        std::cout << "Bouton Play cliqué !" << std::endl;
        _output.play(); 
    });
    _menu.addButton("PAUSE", [this]() {
        std::cout << "Bouton Pause cliqué !" << std::endl;
        _output.pause(); 
    });
    std::cout << "Controls:\n" << "H/G: Increase/Decrease Gain\n" << "F/D: Increase/Decrease Distortion\n" << "O/P: Increase/Decrease Pitch\n" << "ESC: Exit\n";
    // _output.play();
}

void SonoGraf::processEvents()
{
    while (const std::optional event = _window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            _window.close();
        _menu.handleEvent(*event);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        _window.close();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
        _gain += 0.02f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
        _gain = std::max(0.1f, _gain - 0.02f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) 
        _distortion += 0.01f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        _distortion = std::max(0.0f, _distortion - 0.01f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
        _pitch += 0.01f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        _pitch = std::max(0.1f, _pitch - 0.01f);
}

void SonoGraf::update()
{
    _processor.setGain(_gain);
    _processor.setDistortion(_distortion);
    _output.setPitch(_pitch);
}

void SonoGraf::render()
{
    _window.clear(sf::Color(30, 30, 30));
    _menu.draw();
    _window.display();
}

int SonoGraf::run()
{
    while (_window.isOpen()) {
        processEvents();
        update();
        render();
    }
    return 0;
}