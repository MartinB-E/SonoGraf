/*
** EPITECH PROJECT, 2025
** SonoGraf
** File description:
** FileExplorer.hpp
*/

#pragma once
    #include "Bouton.hpp"
    #include "AudioManager.hpp"
    #include <SFML/Graphics.hpp>
    #include <filesystem>
    #include <vector>
    #include <stack>
    #include <memory>

class FileExplorer {
    public:
        FileExplorer(std::shared_ptr<sf::RenderWindow> window = nullptr, 
            std::stack<std::filesystem::path> _previousPath = std::stack<std::filesystem::path>(), 
            std::vector<std::filesystem::directory_entry> _entry = std::vector<std::filesystem::directory_entry>());
        
        void enterDirectory(const std::filesystem::path& path);
        void goBack();
        void draw();
        void handleEvent(const sf::Event& event, AudioManager& audioManager);

        const std::vector<std::filesystem::directory_entry>& getEntry() const;
        const std::filesystem::path& getCurrentPath() const;
        bool canGoBack() const;

    private:
        std::shared_ptr<sf::RenderWindow> _window;
        std::filesystem::path _currentPath;
        std::stack<std::filesystem::path> _previousPath;
        std::vector<std::filesystem::directory_entry> _entry;
        sf::Font _font;

        Bouton _backButton;

        float _listX = 20.f;
        float _listStartY = 120.f;
        float _itemHeight = 22.f;
        float _listWidth = 300.f;

        void loadCurrentDirectory();
};
