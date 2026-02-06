/*
** EPITECH PROJECT, 2026
** SonoGraf
** File description:
** main
*/

#include "SonoGraf.hpp"
#include <iostream>

int main()
{
    try {
        SonoGraf app;
        return app.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 84;
    }
}