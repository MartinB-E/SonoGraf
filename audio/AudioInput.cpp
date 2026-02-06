/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** AudioInput
*/

#include "AudioInput.hpp"

bool AudioInput::onProcessSamples(const std::int16_t* samples, std::size_t count)
{
    std::lock_guard lock(_mutex);
    _buffer.assign(samples, samples + count);
    return true;
}

const std::vector<std::int16_t>& AudioInput::getSamples() const
{
    return _buffer;
}
