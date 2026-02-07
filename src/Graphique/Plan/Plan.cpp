/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Plan.cpp
*/

#include "Plan.hpp"

Plan::Plan(sf::Vector2f position, sf::Vector2f size, std::shared_ptr<sf::RenderWindow> window)
    :  _size(size), _position(position), _window(window), _plan(std::make_shared<sf::RectangleShape>(size))
{
}

Plan::~Plan()
{
}

std::shared_ptr<sf::RectangleShape> Plan::getPlan()
{
    return _plan;
}

void Plan::update(const sf::Vector2u &windowSize)
{
    float width = (float)windowSize.x;
    float height = (float)windowSize.y;

    _plan->setPosition({_position.x * width, _position.y * height});
    _plan->setSize({_size.x * width, _size.y * height});
}

void Plan::draw()
{
    _window->draw(*_plan);
}

void Plan::setPosition(float x, float y)
{
    _position = {x, y};
}

void Plan::setSize(float width, float height)
{
    _size = {width, height};
}

sf::Vector2f Plan::getSize() const
{
    return _size;
}

sf::Vector2f Plan::getPosition() const
{
    return _position;
}

void Plan::setPosition(std::string xPercent, std::string yPercent)
{
    _position = {(std::stof(xPercent) / 100.f), (std::stof(yPercent) / 100.f)};
}

void Plan::setSize(std::string widthPercent, std::string heightPercent)
{
    _size = {(std::stof(widthPercent) / 100.f), (std::stof(heightPercent) / 100.f)};
}

void Plan::setColor(const sf::Color &color)
{
    _plan->setFillColor(color);
}

void Plan::setOutlineColor(const sf::Color &color)
{
    _plan->setOutlineColor(color);
}

void Plan::setOutlineThickness(float thickness)
{
    _plan->setOutlineThickness(thickness);
}