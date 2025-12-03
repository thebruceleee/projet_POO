#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

// On inclut optional car SFML 3 l'utilise pour les événements
#include <optional> 

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));

void initializeGrid() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Petit cast pour éviter les warnings
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = std::rand() % 2;
        }
    }
}

void renderGrid(sf::RenderWindow& window) {
    window.clear();

    // En SFML 3, il est préférable d'utiliser l'initialisation par accolades pour les vecteurs
    sf::RectangleShape cell(sf::Vector2f({ static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1) }));

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grid[x][y] == 1) {
                // setPosition attend des floats, on convertit les entiers
                cell.setPosition({ static_cast<float>(x * cellSize), static_cast<float>(y * cellSize) });
                window.draw(cell);
            }
        }
    }
    window.display();
}

int main() {
    // Modification 1 : VideoMode prend un Vector2u (entiers non signés), on utilise les accolades {}
    // On static_cast pour être propre, car gridWidth * cellSize est un int signé
    auto width = static_cast<unsigned int>(gridWidth * cellSize);
    auto height = static_cast<unsigned int>(gridHeight * cellSize);

    sf::RenderWindow window(sf::VideoMode({ width, height }), "Game of Life");

    initializeGrid();

    while (window.isOpen()) {
        // Modification 2 : Nouvelle boucle d'événements SFML 3.0
        while (const std::optional event = window.pollEvent()) {
            // Modification 3 : Vérification du type d'événement
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        renderGrid(window);

        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}