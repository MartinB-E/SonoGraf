/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** AudioInput
*/

#pragma once

    #include <SFML/Audio.hpp>
    #include <vector>
    #include <mutex>

class AudioInput : public sf::SoundRecorder {
    public:
        const std::vector<std::int16_t>& getSamples() const;

        bool onProcessSamples(const std::int16_t* samples, std::size_t count);

    private:
        mutable std::mutex _mutex;
        std::vector<std::int16_t> _buffer;
};
