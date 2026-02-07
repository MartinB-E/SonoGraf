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
        AudioOutput(AudioProcessor& processor);

        bool onGetData(Chunk& data) override;
        void onSeek(sf::Time) override;
        std::vector<std::int16_t> getVisualizerSamples();

    private:
        sf::InputSoundFile _musicFile;
        std::vector<std::int16_t> _tempBuffer;
        std::vector<std::int16_t> _processed;
        std::vector<std::int16_t> _visuBuffer;
        std::mutex _mutex;
        AudioProcessor& _processor;
};
