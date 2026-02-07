/*
 EPITECH PROJECT, 2026
 SonoGraf
 File description:
 SonoGraf
*/

#include "SonoGraf.hpp"
#include <iostream>

SonoGraf::SonoGraf() 
    : _output(_processor), _window(std::make_shared<sf::RenderWindow>(sf::VideoMode({1920, 1080}), "SonoGraf")), _menu(_window), _fileExplorer(_window), _choose(_window)
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
    _processor.setLow(1.0f);
    _processor.setHigh(0.0f);
    _processor.setGain(1.0f);
    _choose.setPosition(20.f, 20.f);
    std::cout << "Controls:\n" 
        << "G/H: Decrease/Increase Gain\n" 
        << "D/F: Decrease/Increase Distortion\n" 
        << "O/P: Decrease/Increase Pitch\n"
        << "B/N: Decrease/Increase Bitcrush\n"
        << "K/L: Decrease/Increase Bass Boost\n"
        << "U/I: Decrease/Increase Highs Boost\n"
        << "ESC: Exit\n";
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
        _choose.handleEvent();
        _fileExplorer.handleEvent(*event, _manager);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
        sf::Vector2f worldPos = _window->mapPixelToCoords(mousePos);
        sf::FloatRect bounds = _plans[2].getPlan()->getGlobalBounds();

        if (bounds.contains(worldPos)) {
            float posx = (worldPos.x - bounds.position.x) / bounds.size.x;
            float posy = (worldPos.y - bounds.position.y) / bounds.size.y;

            if (posx < 0.5f) {
                _bitcrush = (0.5f - posx) * 2.0f;
                _distortion = 0.0f;
            } else {
                _distortion = (posx - 0.5f) * 20.0f;
                _bitcrush = 0.0f;
            }
            
            if (posy < 0.5f) {
                float factor = (0.5f - posy) * 2.0f;
                _high = factor;
                _low = 1.0f;
                _pitch = 1.0f + (factor * 0.05f);
            } else {
                float factor = (posy - 0.5f) * 2.0f;
                _low = 1.0f - factor;
                _high = 0.0f;
                _pitch = 1.0f - (factor * 0.05f);
            }
        }
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        _pitch += 0.01f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
        _pitch = std::max(0.1f, _pitch - 0.01f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
        _bitcrush = std::min(1.0f, _bitcrush + 0.01f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
        _bitcrush = std::max(0.0f, _bitcrush - 0.01f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
        _low = std::max(0.01f, _low - 0.01f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
        _low = std::min(1.0f, _low + 0.01f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
        _high = std::min(1.0f, _high + 0.01f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
        _high = std::max(0.0f, _high - 0.01f);
}

void SonoGraf::update()
{
    _processor.setGain(_gain);
    _processor.setDistortion(_distortion);
    _processor.setBitcrush(_bitcrush);
    _processor.setHigh(_high);
    _processor.setLow(_low);
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
    _choose.draw();
    _fileExplorer.draw();
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