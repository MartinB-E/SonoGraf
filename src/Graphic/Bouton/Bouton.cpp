/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Bouton.cpp
*/

#include "Bouton.hpp"

Bouton::Bouton(const sf::Font &font, const std::string &text, std::function<void()> onClick) 
    : label(font), onClick(onClick) 
{
    shape.setSize({200.f, 50.f});
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(3);

    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
    
    setPosition(0, 0);
}

void Bouton::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    window.draw(label);
}

bool Bouton::isClick(sf::Vector2f mousePos)
{
    if (shape.getGlobalBounds().contains(mousePos)) {
        if (onClick)
            onClick();
        return true;
    }
    return false;
}

void Bouton::setPosition(float x, float y)
{
    sf::Vector2f pos(x, y);
    shape.setPosition(pos);
    sf::Vector2f center = shape.getPosition() + shape.getSize() / 2.0f;
    label.setPosition(center);
}

void Bouton::setSize(float width, float height)
{
    shape.setSize({width, height});
    sf::Vector2f center = shape.getPosition() + shape.getSize() / 2.0f;
    label.setPosition(center);
}