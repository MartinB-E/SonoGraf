/*
** EPITECH PROJECT, 2025
** SonoGraf
** File description:
** Bouton.cpp
*/

#include "Bouton.hpp"

Bouton::Bouton(const sf::Font &font, const std::string &text, std::function<void()> onClick) : onClick(onClick)
{
    shape.setSize(sf::Vector2f(200, 50));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(3);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);

    sf::FloatRect textRect =  label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    setPosition(0, 0);
}

void Bouton::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    window.draw(label);
}

bool Bouton::isClick(sf::Vector2f mousePos)
{
    if (shape.getGlobalBounds().contains(mousePos))
        if (onClick)
            onClick();
        return true;
    return false;
}

void Bouton::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    sf::Vector2f center = shape.getPosition() + shape.getSize() / 2.0f;
    label.setPosition(center);
}

void Bouton::setSize(float width, float height)
{
    shape.setSize(sf::Vector2f(width, height));
    sf::Vector2f center = shape.getPosition() + shape.getSize() / 2.0f;
    label.setPosition(center);
}