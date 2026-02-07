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
        Plan(sf::Vector2f position = {0.f, 0.f}, sf::Vector2f size = {100.f, 100.f}, std::shared_ptr<sf::RenderWindow> window);
        ~Plan();

        void draw();
        void update(const sf::Vector2u &windowSize);

        void setPosition(float x, float y);
        void setPosition(std::string xPercent, std::string yPercent);
        void setSize(float width, float height);
        void setSize(std::string widthPercent, std::string heightPercent);
        void setColor(const sf::Color &color);
        void setOutlineColor(const sf::Color &color);
        void setOutlineThickness(float thickness);

        sf::Vector2f getSize() const;
        sf::Vector2f getPosition() const;
        std::shared_ptr<sf::RectangleShape> getPlan();

    private:
        sf::Vector2f _size;
        sf::Vector2f _position;
        std::shared_ptr<sf::RenderWindow> _window;
        std::shared_ptr<sf::RectangleShape> _plan;
};
