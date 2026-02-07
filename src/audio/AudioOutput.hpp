/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** AudioOuput
*/

#pragma once

    #include <SFML/Audio.hpp>
    #include <vector>

    #include "AudioProcessor.hpp"
    #include "AudioInput.hpp"

class AudioOutput : public sf::SoundStream {
    public:
        AudioOutput(AudioInput& input, AudioProcessor& processor);

    protected:
        bool onGetData(Chunk& data) override;
        void onSeek(sf::Time) override {}

    private:
        AudioInput& _input;
        AudioProcessor& _processor;
        std::vector<std::int16_t> _processed;
        sf::InputSoundFile _musicFile;
};
