/*
** EPITECH PROJECT, 2025
** Visual Studio Live Share (Workspace)
** File description:
** ChooseMusic.cpp
*/

#include "ChooseMusic.hpp"

ChooseMusicButton::ChooseMusicButton(std::shared_ptr<sf::RenderWindow> window) : _window(window), _font(), _text(_font), _onClick(nullptr) {
    if (!_font.openFromFile("../assets/arial.ttf")) {
        throw std::runtime_error("Font load failed");
    }

    _shape.setSize({200.f, 40.f});
    _shape.setFillColor(sf::Color(70, 70, 70));

    _text.setString("Enter directory :");
    _text.setCharacterSize(16);
    _text.setFillColor(sf::Color::White);
}

void ChooseMusicButton::setPosition(float x, float y) {
    _shape.setPosition({x, y});
    _text.setPosition({x + 10, y + 8});
}

void ChooseMusicButton::setOnClick(std::function<void()> callback) {
    _onClick = callback;
}

void ChooseMusicButton::handleEvent() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        auto mouse = sf::Mouse::getPosition((*_window));
        if (_shape.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mouse.x), static_cast<float>(mouse.y)))) {
            if (_onClick)
                _onClick();
        }
    }
}

void ChooseMusicButton::draw() {
    (*_window).draw(_shape);
    (*_window).draw(_text);
}
