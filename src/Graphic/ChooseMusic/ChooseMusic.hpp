/*
** EPITECH PROJECT, 2025
** Visual Studio Live Share (Workspace)
** File description:
** ChooseMusic.hpp
*/

#pragma once

#include "../Bouton/Bouton.hpp"

class ChooseMusicButton : public Bouton {
    public:
        ChooseMusicButton(const std::string &text, const sf::Vector2f &position, const sf::Vector2f &size);
        ~ChooseMusicButton() = default;

        void onClick() override;
};