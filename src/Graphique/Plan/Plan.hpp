/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Plan.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Plan {
    public:
        Plan();
        ~Plan();

        void addPlan(std::string name, sf::Vector2f position, sf::Vector2f size);
        sf::RectangleShape &getPlan(std::string name);
        void update(const sf::Vector2u &windowSize);
        void draw(sf::RenderWindow &window);

    private:
        struct PlanConfig {
            sf::Vector2f position;
            sf::Vector2f size;
        };
        std::map<std::string, PlanConfig> _configs;
        std::map<std::string, sf::RectangleShape> _plans;
};
