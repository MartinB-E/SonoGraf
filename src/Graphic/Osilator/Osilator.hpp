/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Osilator
*/


#pragma once

    #include <vector>
    #include <memory>
    #include <SFML/Graphics.hpp>

    #include "Plan.hpp"

class Osilator {
    public:
        Osilator(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Plan> targetPlan);
        ~Osilator() = default;

        void update(const std::vector<std::int16_t>& samples);
        void draw();

    private:
        std::shared_ptr<sf::RenderWindow> _window;
        std::shared_ptr<Plan> _targetPlan;
        sf::VertexArray _vertices;
};