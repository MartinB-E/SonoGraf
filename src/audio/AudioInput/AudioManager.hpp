/*
** EPITECH PROJECT, 2025
** SonoGraf
** File description:
** AudioManager.hpp
*/

#pragma once
    #include <vector>
    #include <SFML/Audio.hpp>

class AudioManager {
    public:
        bool loadAudio(const std::string& path);
        const std::vector<sf::SoundBuffer>& getBuffers() const;

    private:
        std::vector<sf::SoundBuffer> _buffers;
};