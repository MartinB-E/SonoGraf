/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Bouton.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Bouton{
    public:
        Bouton(const sf::Font &font, const std::string &text, std::function<void()> onClick);
        ~Bouton() = default;

        void draw(sf::RenderWindow &window);
        bool isClick(sf::Vector2f mousePos);
        void setPosition(float x, float y);
        void setSize(float width, float height);
    private:
        sf::RectangleShape shape;
        sf::Text label;
        std::function<void()> onClick;
};