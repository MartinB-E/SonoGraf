/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** AudioOutput
*/

#include "AudioOutput.hpp"

AudioOutput::AudioOutput(AudioInput& input, AudioProcessor& processor)
    : _input(input), _processor(processor)
{
    std::vector<sf::SoundChannel> channels = {sf::SoundChannel::Mono};
    initialize(1, 44100, channels);
    if (!_musicFile.openFromFile("../assets/credits.mp3"))
        throw std::runtime_error("Impossible de charger le fichier audio");
}


bool AudioOutput::onGetData(Chunk& data)
{
    static std::vector<std::int16_t> readBuffer(44100 / 10); 
    
    std::uint64_t read = _musicFile.read(readBuffer.data(), readBuffer.size());

    if (read == 0) {
        _musicFile.seek(sf::Time::Zero);
        return true; 
    }

    if (readBuffer.size() != read)
        readBuffer.resize(read);

    _processor.process(readBuffer, _processed);

    data.samples = _processed.data();
    data.sampleCount = _processed.size();
    return true;
}