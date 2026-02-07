/*
** EPITECH PROJECT, 2025
** Visual Studio Live Share (Workspace)
** File description:
** ChooseMusic.hpp
*/

#pragma once
    #include <SFML/Graphics.hpp>
    #include <functional>
    #include <memory>

class ChooseMusicButton {
    public:
        ChooseMusicButton(std::shared_ptr<sf::RenderWindow> window = nullptr);

        void setPosition(float x, float y);
        void draw();
        void handleEvent();
        
        void setOnClick(std::function<void()> callback);
    
    private:
        std::shared_ptr<sf::RenderWindow> _window;
        sf::Font _font;
        sf::Text _text;
        sf::RectangleShape _shape;
        std::function<void()> _onClick;
};