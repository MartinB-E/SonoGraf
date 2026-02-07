/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** AudioProcessor
*/

#pragma once

    #include <vector>
    #include <SFML/Audio.hpp>

class AudioProcessor {
    public:
        void process(const std::vector<std::int16_t>& input, std::vector<std::int16_t>& output);

        void setGain(float g);
        void setDistortion(float d);
        void setBitcrush(float b);
        void setLow(float l);
        void setHigh(float h);

        float getGain() const;
        float getDistortion() const;

    private:
        float _gain = 1.f;
        float _distortion = 0.f;
        float _bitcrush = 0.0f;
        float _low = 1.0f;
        float _high = 0.0f;
        float _save = 0.0f;
};
