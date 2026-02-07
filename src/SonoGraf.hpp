/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** SonoGraf
*/


#pragma once
    #include <SFML/Graphics.hpp>
    #include "audio/AudioInput.hpp"
    #include "audio/AudioProcessor.hpp"
    #include "audio/AudioOutput.hpp"
    #include "audio/AudioManager.hpp"
    #include "Graphique/Menu/Menu.hpp"
    #include "Graphique/Plan/Plan.hpp"
    #include "Graphique/ChooseMusic/FileExplorer.hpp"
    #include "Graphique/ChooseMusic/ChooseMusic.hpp"

class SonoGraf {
    public:
        SonoGraf();
        int run();

    private:
        void processEvents();
        void update();
        void render();

        AudioInput _input;
        AudioOutput _output;
        AudioProcessor _processor;
        AudioManager _manager;

        std::shared_ptr<sf::RenderWindow> _window;
        Menu _menu;
        Plan _plan;
        FileExplorer _fileExplorer;
        ChooseMusicButton _choose;

        
        float _gain = 1.0f;
        float _pitch = 1.0f;
        float _distortion = 0.0f;
};