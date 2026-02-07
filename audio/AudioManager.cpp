/*
** EPITECH PROJECT, 2025
** SonoGraf
** File description:
** AudioManager.cpp
*/

#include "AudioManager.hpp"
#include <iostream>

bool AudioManager::loadAudio(const std::string& path) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(path)) {
        std::cerr << "Error: loading audio " << path << std::endl;
        return false;
    }
    _buffers.push_back(buffer);
    return true;
}

const std::vector<sf::SoundBuffer>& AudioManager::getBuffers() const {
    return _buffers;
}