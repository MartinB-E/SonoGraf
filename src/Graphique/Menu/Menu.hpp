/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Menu.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>    
#include "../Bouton/Bouton.hpp"
#include <memory>
#include <functional>

class Menu {
    public:
        Menu(sf::RenderWindow &window);
        ~Menu();

        void draw();
        int getPressedItem() const;
        void handleEvent(const sf::Event &event);
        void addButton(const std::string &text, std::function<void()> onClick);
    private:
        sf::RenderWindow &_window;
        int _select_item;
        sf::Font _font;
        std::vector<Bouton> _buttons;
        std::vector<std::shared_ptr<Bouton>> _buttonPtrs;
};
