/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** SonoGraf
*/


#pragma once
    
    #include <SFML/Graphics.hpp>

    #include "Menu.hpp"
    #include "Plan.hpp"
    #include "Osilator.hpp"
    #include "AudioInput.hpp"
    #include "AudioOutput.hpp"
    #include "AudioProcessor.hpp"

class SonoGraf {
    public:
        SonoGraf();
        int run();

    private:
        void processEvents();
        void update();
        void render();

        AudioInput _input;
        AudioProcessor _processor;
        AudioOutput _output;

        std::shared_ptr<sf::RenderWindow> _window;
        std::vector<Plan> _plans;
        Menu _menu;
        std::vector<std::shared_ptr<Osilator>> _osilators;
        
        float _gain = 1.0f;
        float _pitch = 1.0f;
        float _distortion = 0.0f;
        float _bitcrush = 0.0f;
        float _low = 1.0f;
        float _high = 0.0f;
};