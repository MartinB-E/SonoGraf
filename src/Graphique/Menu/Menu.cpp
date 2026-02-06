/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Menu.cpp
*/

#include "Menu.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow &window) : _window(window), _select_item(0)
{
    if (!_font.loadFromFile("assets/arial.ttf"))
        std::cerr << "Erreur: Impossible de charger assets/arial.ttf" << std::endl;
}

Menu::~Menu()
{
}

void Menu::addButton(const std::string &text, std::function<void()> onClick)
{
    Bouton newButton(_font, text, onClick);
    float y = 50 + _buttons.size() * 70;
    newButton.setPosition(50, y);
    _buttons.push_back(newButton);
}

void Menu::draw()
{
    for (auto &button : _buttons) {
        button.draw(_window);
    }
}

int Menu::getPressedItem() const
{
    return _select_item;
}

void Menu::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pixelPos = { event.mouseButton.x, event.mouseButton.y };
            sf::Vector2f mousePos = _window.mapPixelToCoords(pixelPos);
            for (auto &button : _buttons) {
                if (button.isClick(mousePos)) {
                    break;
                }
            }
   }
    }
}