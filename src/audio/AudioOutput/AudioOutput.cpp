/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** AudioOutput
*/

#include "AudioOutput.hpp"
#include <iostream>
AudioOutput::AudioOutput(AudioProcessor& processor)
    : _processor(processor)
{
    if (!_musicFile.openFromFile("../assets/credits.mp3")) {
        std::cerr << "ERREUR : Fichier introuvable" << std::endl;
        return;
    }

    // --- ADAPTATION AUTOMATIQUE ---
    unsigned int channels = _musicFile.getChannelCount();
    unsigned int sampleRate = _musicFile.getSampleRate();
    
    std::vector<sf::SoundChannel> map;
    if (channels == 1) {
        map = {sf::SoundChannel::Mono};
    } else {
        // Si c'est du stéréo ou plus, on mappe Gauche/Droite
        map = {sf::SoundChannel::FrontLeft, sf::SoundChannel::FrontRight};
        channels = 2; // On se limite à 2 pour le processeur
    }

    initialize(channels, sampleRate, map);
    std::cout << "Streaming lance : " << channels << " canaux, " << sampleRate << "Hz" << std::endl;
}

bool AudioOutput::onGetData(Chunk& data)
{
    // On lit suffisamment d'échantillons (ex: 2048)
    static std::vector<std::int16_t> readBuffer(2048);
    
    std::uint64_t read = _musicFile.read(readBuffer.data(), readBuffer.size());

    if (read == 0) {
        _musicFile.seek(sf::Time::Zero); // Loop
        return true;
    }

    // Important : on ajuste la taille réelle lue
    if (_tempBuffer.size() != read) _tempBuffer.resize(read);
    std::copy(readBuffer.begin(), readBuffer.begin() + read, _tempBuffer.begin());

    // Traitement par le processeur
    _processor.process(_tempBuffer, _processed);

    // COPIE POUR LE VISUALISEUR
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _visuBuffer = _processed; // On envoie les données traitées
    }

    data.samples = _processed.data();
    data.sampleCount = _processed.size();
    return true;
}

std::vector<std::int16_t> AudioOutput::getVisualizerSamples()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _visuBuffer;
}

void AudioOutput::onSeek(sf::Time)
{
}