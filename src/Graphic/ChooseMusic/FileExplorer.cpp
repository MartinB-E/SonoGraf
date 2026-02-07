/*
** EPITECH PROJECT, 2025
** SonoGraf
** File description:
** FileExplorer.cpp
*/

#include "FileExplorer.hpp"

FileExplorer::FileExplorer(std::shared_ptr<sf::RenderWindow> window, 
    std::stack<std::filesystem::path> previousPath, 
    std::vector<std::filesystem::directory_entry> entry)
    : _window(window), _currentPath(), _previousPath(previousPath), _entry(entry), _backButton(_font, "< Back", [this]() { goBack(); })
{
    const char* home = std::getenv("HOME");
    if (home) {
        _currentPath = home;
    } else {
        _currentPath = std::filesystem::current_path();
    }

    if (!_font.openFromFile("../assets/arial.ttf")) {
        throw "Erreur: Impossible de charger assets/arial.ttf";
    }

    _backButton.setPosition(20.f, 70.f);
    _backButton.setSize(80.f, 30.f);

    loadCurrentDirectory();
}

void FileExplorer::loadCurrentDirectory() {
    _entry.clear();

    for (const auto& entry : std::filesystem::directory_iterator(_currentPath)) {
        const auto name = entry.path().filename().string();

        if (!name.empty() && name[0] == '.')
            continue;

        if (entry.is_directory() || entry.path().extension() == ".wav" ||
        entry.path().extension() == ".mp3" ||
        entry.path().extension() == ".ogg" ||
        entry.path().extension() == ".flac" ||
        entry.path().extension() == ".aac") {
            _entry.push_back(entry);
        }
    }
}

void FileExplorer::enterDirectory(const std::filesystem::path& path) {
    _previousPath.push(_currentPath);
    _currentPath = path;
    loadCurrentDirectory();
}

void FileExplorer::draw() {
    if (_window) {
        if (!canGoBack())
            _backButton.draw((*_window));

        float y = _listStartY;

        for (const auto& entry : _entry) {
            sf::Text text(_font);
            text.setCharacterSize(16);
            if (entry.is_directory())
                text.setFillColor(sf::Color::Cyan);
            else
                text.setFillColor(sf::Color::White);
            text.setString(entry.path().filename().string());
            text.setPosition({_listX, y});
            _window->draw(text);
            y += _itemHeight;
        }
    }
}

void FileExplorer::goBack() {
    if (!_previousPath.empty()) {
        _currentPath = _previousPath.top();
        _previousPath.pop();
        loadCurrentDirectory();
    }
}

bool FileExplorer::canGoBack() const {
    return _previousPath.empty();
}

const std::vector<std::filesystem::directory_entry>& FileExplorer::getEntry() const {
    return _entry;
}

const std::filesystem::path& FileExplorer::getCurrentPath() const {
    return _currentPath;
}

void FileExplorer::handleEvent(const sf::Event& event, AudioManager& audioManager) {
    if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouse->button != sf::Mouse::Button::Left)
            return;

        sf::Vector2f mousePos = _window->mapPixelToCoords({mouse->position.x, mouse->position.y});

        if (!canGoBack() && _backButton.isClick(mousePos))
            return;

        float y = _listStartY;
        for (const auto& entry : _entry) {
            sf::FloatRect bounds({_listX, y}, {_listWidth, _itemHeight});
            if (bounds.contains(mousePos)) {
                if (entry.is_directory()) {
                    enterDirectory(entry.path());
                } else {
                    if (!audioManager.loadAudio(entry.path().string())) {
                        throw std::runtime_error("Failed to load audio: " + entry.path().string());
                    }
                    printf("Loaded audio: %s\n", entry.path().string().c_str());
                }
                return;
            }
            y += _itemHeight;
        }
    }
}