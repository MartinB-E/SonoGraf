/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Plan.cpp
*/

#include "Plan.hpp"

Plan::Plan()
{
}

Plan::~Plan()
{
}

void Plan::addPlan(std::string name, sf::Vector2f position, sf::Vector2f size)
{
    _configs[name] = {position, size}; // Store percentages

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(148, 0, 211)); // Violet
    rect.setOutlineThickness(1);
    _plans[name] = rect;
}

sf::RectangleShape &Plan::getPlan(std::string name)
{
    return _plans[name];
}

void Plan::update(const sf::Vector2u &windowSize)
{
    float width = (float)windowSize.x;
    float height = (float)windowSize.y;

    for (auto &element : _configs) {
        std::string name = element.first;
        PlanConfig config = element.second;
        float x = config.position.x * width;
        float y = config.position.y * height;
        float w = config.size.x * width;
        float h = config.size.y * height;
        _plans[name].setPosition({x, y});
        _plans[name].setSize({w, h});
    }
}

void Plan::draw(sf::RenderWindow &window)
{
    for (auto &plan : _plans) {
        window.draw(plan.second);
    }
}
