#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

// <optional> n'est pas nécessaire pour SFML 2.6.1

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));

void initializeGrid() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = std::rand() % 2;
        }
    }   
}

void renderGrid(sf::RenderWindow& window) {
    window.clear();

    // Correction pour SFML 2.6 : On utilise le constructeur classique (x, y) sans accolades doubles
    sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1)));

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grid[x][y] == 1) {
                // Correction pour SFML 2.6 : setPosition(x, y) directement
                cell.setPosition(static_cast<float>(x * cellSize), static_cast<float>(y * cellSize));
                window.draw(cell);
            }
        }
    }
    window.display();
}

int main() {
    auto width = static_cast<unsigned int>(gridWidth * cellSize);
    auto height = static_cast<unsigned int>(gridHeight * cellSize);

    // Correction SFML 2.6 : Pas d'accolades {} autour de width et height
    sf::RenderWindow window(sf::VideoMode(width, height), "Game of Life");

    initializeGrid();

    while (window.isOpen()) {

        // --- CORRECTION MAJEURE ICI (Version 2.6.1) ---
        sf::Event event; // 1. On déclare la variable AVANT
        while (window.pollEvent(event)) { // 2. On la passe en argument

            // 3. On vérifie le type avec "event.type" (et non event->is<...>)
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        // ----------------------------------------------

        renderGrid(window);

        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}