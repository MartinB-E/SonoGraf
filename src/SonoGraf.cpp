/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** SonoGraf
*/

#include "SonoGraf.hpp"
#include <iostream>

SonoGraf::SonoGraf() 
    : _output(_processor), _window(std::make_shared<sf::RenderWindow>(sf::VideoMode({1920, 1080}), "SonoGraf")), _menu(_window)
{
    _window->setFramerateLimit(60);
    
    Plan planSide({0.0f, 0.0f}, {0.20f, 1.0f}, _window);
    Plan planBottomBar({0.20f, 0.85f}, {1.0f, 0.15f}, _window);
    Plan planOsilator({0.20f, 0.0f}, {0.80f, 0.85f}, _window);
    planSide.setSize("20", "100");
    planBottomBar.setPosition("20", "85");
    planOsilator.setPosition("20", "0");
    planOsilator.setSize("80", "85");
    planBottomBar.setSize("100", "15");
    planSide.setColor(sf::Color(50, 50, 50));
    planBottomBar.setColor(sf::Color(50, 50, 50));
    planSide.setOutlineColor(sf::Color(160, 32, 240)); 
    planSide.setOutlineThickness(2.f);
    planBottomBar.setOutlineColor(sf::Color(160, 32, 240));
    planBottomBar.setOutlineThickness(2.f);
    planOsilator.setColor(sf::Color(30, 30, 30));
    planOsilator.setOutlineColor(sf::Color(160, 32, 240));
    planOsilator.setOutlineThickness(2.f);
    _plans.push_back(planSide);
    _plans.push_back(planBottomBar);
    _plans.push_back(planOsilator);
    Osilator osilator(_window, std::make_shared<Plan>(planOsilator));
    _osilators.push_back(std::make_shared<Osilator>(osilator));
    std::cout << "Controls:\n" << "H/G: Increase/Decrease Gain\n" << "F/D: Increase/Decrease Distortion\n" << "O/P: Increase/Decrease Pitch\n" << "ESC: Exit\n";
    _output.play();
}

void SonoGraf::processEvents()
{
    while (const std::optional event = _window->pollEvent()) {
        if (event->is<sf::Event::Closed>())
            _window->close();
        else if (const auto* resizeEvent = event->getIf<sf::Event::Resized>()) {
            sf::Vector2u newSize = resizeEvent->size;
            sf::FloatRect visibleArea({0, 0}, {static_cast<float>(newSize.x), static_cast<float>(newSize.y)});
            _window->setView(sf::View(visibleArea));
            for (auto& plan : _plans)
                plan.update(newSize);
        }
        _menu.handleEvent(*event);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        _window->close();

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
    for (auto& osilator : _osilators)
        osilator->update(_output.getVisualizerSamples());
}

void SonoGraf::render()
{
    _window->clear(sf::Color(30, 30, 30));
    for (auto& plan : _plans)
        plan.draw();
    _menu.draw();
    for (auto& osilator : _osilators)
        osilator->draw();
    _window->display();
}

int SonoGraf::run()
{
    while (_window->isOpen()) {
        processEvents();
        update();
        render();
    }
    return 0;
}