/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** Osilator
*/

#include "Osilator.hpp"
#include "Osilator.hpp"
#include <cmath>
#include <algorithm>

#include "Osilator.hpp"

Osilator::Osilator(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Plan> targetPlan)
    : _window(window), _targetPlan(targetPlan), _vertices(sf::PrimitiveType::LineStrip)
{
}

void Osilator::update(const std::vector<std::int16_t>& samples)
{
    if (!_targetPlan || samples.empty())
        return;

    sf::FloatRect bounds = _targetPlan->getPlan()->getGlobalBounds();
    _vertices.clear();
    float midY = bounds.position.y + (bounds.size.y / 2.0f);
    float largeurCourbe = bounds.size.x; 
    float debutX = bounds.position.x;
    const std::size_t nbPoints = 300;
    float step = static_cast<float>(samples.size()) / nbPoints;

    for (std::size_t i = 0; i < nbPoints; ++i) {
        float x = debutX + (static_cast<float>(i) / nbPoints) * largeurCourbe;
        std::size_t sampleIdx = static_cast<std::size_t>(i * step);
        if (sampleIdx >= samples.size())
            break;

        float val = static_cast<float>(samples[sampleIdx]) / 32768.0f;
        float y = midY + (val * bounds.size.y * 0.4f);
        _vertices.append(sf::Vertex({x, y}, sf::Color::Cyan));
    }
}

void Osilator::draw()
{
    if (_window && _vertices.getVertexCount() > 0)
        _window->draw(_vertices);
}