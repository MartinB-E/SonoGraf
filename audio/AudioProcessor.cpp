/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** AudioProcessor
*/

#include "AudioProcessor.hpp"

#include <cmath>
#include <algorithm>

void AudioProcessor::setGain(float g)
{
    _gain = g;
}

void AudioProcessor::setDistortion(float d)
{
    _distortion = d;
}

void AudioProcessor::process(const std::vector<std::int16_t>& input, std::vector<std::int16_t>& output)
{
    output.resize(input.size());

    for (std::size_t i = 0; i < input.size(); ++i) {
        float sample = input[i] / 32768.f;

        sample *= _gain;
        sample = std::tanh(sample * (1.f + _distortion));

        sample = std::clamp(sample, -1.f, 1.f);
        output[i] = static_cast<std::int16_t>(sample * 32767);
    }
}

float AudioProcessor::getGain() const
{
    return _gain;
}

float AudioProcessor::getDistortion() const
{
    return _distortion;
}