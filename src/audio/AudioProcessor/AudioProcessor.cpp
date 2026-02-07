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

void AudioProcessor::setBitcrush(float b)
{
    _bitcrush = b;
}

void AudioProcessor::setLow(float l)
{
    _low = std::clamp(l, 0.01f, 1.0f);
}

void AudioProcessor::setHigh(float h) 
{
    _high = std::clamp(h, 0.0f, 0.99f);
}

void AudioProcessor::process(const std::vector<std::int16_t>& input, std::vector<std::int16_t>& output)
{
    output.resize(input.size());

    for (std::size_t i = 0; i < input.size(); ++i) {
        float res = (static_cast<float>(input[i]) / 32768.f) * _gain;

        if (_bitcrush > 0.01f) {
            float factor = std::pow(2.0f, 16.0f * (1.0f - _bitcrush));
            res = std::round(res * factor) / factor;
        }

        if (_distortion > 0.01f)
            res = std::tanh(res * (1.f + _distortion));

        float alpha = 0.2f; 
        _save = alpha * res + (1.0f - alpha) * _save;
        
        float bass_part = _save;
        float high_part = res - _save;

        if (_low < 0.99f) {
            float bass_boost = 1.0f + ((1.0f - _low) * 5.0f);
            res = (bass_part * bass_boost) + high_part;
        } else if (_high > 0.01f) {
            float high_boost = 1.0f + (_high * 5.0f);
            res = (high_part * high_boost) + bass_part;
        }

        res = std::clamp(res, -1.f, 1.f);
        output[i] = static_cast<std::int16_t>(res * 32767);
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