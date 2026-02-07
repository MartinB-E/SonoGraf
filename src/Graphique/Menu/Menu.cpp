/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Menu.cpp
*/

#include "Menu.hpp"
#include <iostream>

Menu::Menu(std::shared_ptr<sf::RenderWindow> window)
    : _window(window), _select_item(0)
{
    if (!_font.openFromFile("../assets/arial.ttf")) {
        std::cerr << "Erreur: Impossible de charger assets/arial.ttf" << std::endl;
    }
}

Menu::~Menu()
{
}

void Menu::addButton(const std::string &text, std::function<void()> onClick)
{
    Bouton newButton(_font, text, onClick);
    float y = 10 + _buttons.size() * 60;
    newButton.setPosition(10, y);
    _buttons.push_back(newButton);
}

void Menu::draw()
{
    for (auto &button : _buttons) {
        button.draw(*_window);
    }
}

int Menu::getPressedItem() const
{
    return _select_item;
}

void Menu::handleEvent(const sf::Event &event)
{
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2i pixelPos = { mouseEvent->position.x, mouseEvent->position.y };
            sf::Vector2f mousePos = _window->mapPixelToCoords(pixelPos);
            for (auto &button : _buttons) {
                if (button.isClick(mousePos)) {
                    break;
                }
            }
        }
    }
}