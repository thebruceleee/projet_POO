#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Constructeur : Initialise la grille et charge les assets
Game::Game(int largeur, int hauteur)
    : m_grille(largeur, hauteur)
{
    initResources();
}

// Destructeur par défaut
Game::~Game() = default;

// Gestion robuste des ressources (Gestion d'erreurs explicite)
void Game::initResources() {
    // Chargement des polices avec gestion d'erreur console
    if (!m_fontRoboto.loadFromFile("assets/fonts/Roboto-Bold.ttf")) {
        cerr << "[ERREUR] Echec chargement Roboto-Bold.ttf" << endl;
    }
    if (!m_fontScript.loadFromFile("assets/fonts/AstonScript.ttf")) {
        cerr << "[ERREUR] Echec chargement AstonScript.ttf" << endl;
    }

    // Chargement musique
    if (!m_music.openFromFile("assets/music/kahoot_music.ogg")) {
        cerr << "[ERREUR] Echec chargement musique" << endl;
    }
    else {
        m_music.setLoop(true);
        m_music.setVolume(50.f); // Volume raisonnable par défaut
    }
}

// Cœur du moteur physique : Evolution d'une génération
// Optimisation : Utilisation d'un tampon (Buffer) pour éviter les effets de bord
void Game::update(const Regles& regles) {
    int w = m_grille.getLargeur();
    int h = m_grille.getHauteur();

    // Allocation dynamique du tampon de comptage (sur la pile ou le tas via vector)
    // Cela remplace le dangereux int tempTab[100][100]
    std::vector<int> voisinsBuffer(w * h);

    // PASSE 1 : Analyse (Lecture seule de la grille)
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            // Si c'est un obstacle, on marque une valeur spéciale (-1)
            if (m_grille.accessCell(x, y).estObstacle()) {
                voisinsBuffer[y * w + x] = -1;
            }
            else {
                // Appel optimisé à la nouvelle méthode de Grille
                voisinsBuffer[y * w + x] = m_grille.compterVoisinsVivants(x, y);
            }
        }
    }

    // PASSE 2 : Écriture (Modification de la grille)
    const auto& lois = regles.getLois(); // Accès direct aux seuils

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int nbVoisins = voisinsBuffer[y * w + x];

            // On ignore les obstacles (-1)
            if (nbVoisins == -1) continue;

            Cell& cell = m_grille.accessCell(x, y);
            bool estVivante = cell.estVivante();

            // Application stricte des règles
            if (!estVivante && nbVoisins == lois.naissance) {
                cell.rendreVivante();
            }
            else if (estVivante) {
                if (nbVoisins < lois.isolement || nbVoisins > lois.surpop) {
                    cell.rendreMorte();
                }
            }
        }
    }
}

// Gestion de l'affichage (Rendering)
// Séparation claire entre le dessin de la grille, de l'UI et des prévisualisations
void Game::render(sf::RenderWindow& window, int cellSize, int modeJeu) {
    window.clear(sf::Color(30, 30, 30)); // Fond gris foncé moderne

    // 1. Dessiner la grille
    drawGrid(window, cellSize);

    // 2. Dessiner l'interface utilisateur (droite)
    drawUI(window, cellSize, modeJeu);

    // 3. Gestion de la souris et prévisualisation (Ghost)
    // On calcule la position une seule fois par frame (Optimisation CPU)
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int gridX = mousePos.x / cellSize;
    int gridY = mousePos.y / cellSize;

    // Vérification que la souris est bien DANS la grille
    if (gridX >= 0 && gridX < m_grille.getLargeur() &&
        gridY >= 0 && gridY < m_grille.getHauteur()) {

        drawPreview(window, cellSize, gridX, gridY, modeJeu);
    }

    window.display();
}

// Sous-fonction pour dessiner la grille
void Game::drawGrid(sf::RenderWindow& window, int cellSize) {
    sf::RectangleShape cellShape(sf::Vector2f(cellSize - 1.f, cellSize - 1.f));

    for (int y = 0; y < m_grille.getHauteur(); ++y) {
        for (int x = 0; x < m_grille.getLargeur(); ++x) {
            const Cell& c = m_grille.accessCell(x, y);

            // On ne dessine que si nécessaire (Optimisation GPU)
            if (c.estVivante() || c.estObstacle()) {
                cellShape.setPosition(static_cast<float>(x * cellSize), static_cast<float>(y * cellSize));

                if (c.estObstacle()) {
                    cellShape.setFillColor(sf::Color(100, 100, 255)); // Bleu Obstacle
                }
                else {
                    cellShape.setFillColor(sf::Color::White); // Blanc Vivant
                }
                window.draw(cellShape);
            }
        }
    }
}

// Sous-fonction pour les prévisualisations (Glider, etc.)
void Game::drawPreview(sf::RenderWindow& window, int cellSize, int gx, int gy, int mode) {
    sf::RectangleShape previewShape(sf::Vector2f(cellSize - 1.f, cellSize - 1.f));

    // Couleur semi-transparente pour l'effet "Fantôme"
    sf::Color ghostColor = (mode == 3) ? sf::Color(0, 0, 255, 128) : sf::Color(255, 0, 0, 128);
    previewShape.setFillColor(ghostColor);

    // Liste des offsets (décalages) pour chaque motif
    // C'est beaucoup plus propre que des if/else imbriqués
    vector<pair<int, int>> offsets;

    switch (mode) {
    case 0: // Normal
    case 3: // Obstacle
        offsets = { {0,0} };
        break;
    case 1: // Glider
        offsets = { {0,-1}, {1,0}, {-1,1}, {0,1}, {1,1} };
        break;
    case 2: // Helicopter (Barre de 3)
        offsets = { {0,0}, {0,-1}, {0,1} };
        break;
    }

    for (auto& p : offsets) {
        // Calcul torique pour l'affichage du fantôme aussi
        int finalX = (gx + p.first + m_grille.getLargeur()) % m_grille.getLargeur();
        int finalY = (gy + p.second + m_grille.getHauteur()) % m_grille.getHauteur();

        previewShape.setPosition(finalX * cellSize, finalY * cellSize);
        window.draw(previewShape);
    }
}

// Dessin de l'interface (simplifié pour la lisibilité)
void Game::drawUI(sf::RenderWindow& window, int cellSize, int mode) {
    float startX = m_grille.getLargeur() * cellSize;

    // Fond du panneau
    sf::RectangleShape panel(sf::Vector2f(600.f, window.getSize().y));
    panel.setFillColor(sf::Color(50, 50, 50));
    panel.setPosition(startX, 0);
    window.draw(panel);

    // Titre
    sf::Text titre("Game of Life", m_fontScript, 40);
    titre.setPosition(startX + 150, 20);
    window.draw(titre);

    // Mode actuel
    string nomMode;
    switch (mode) {
    case 0: nomMode = "NORMAL"; break;
    case 1: nomMode = "GLIDER"; break;
    case 2: nomMode = "HELICOPTER"; break;
    case 3: nomMode = "OBSTACLE"; break;
    default: nomMode = "INCONNU";
    }

    sf::Text txtInfo("MODE: " + nomMode + "\n\n[ESPACE] Pause\n[ENTREE] Play\n[C] Clear\n[Clic G] Placer\n[Clic D] Effacer", m_fontRoboto, 20);
    txtInfo.setPosition(startX + 50, 100);
    window.draw(txtInfo);
}

// Sauvegarde fichier
void Game::saveToText(int generation, const std::string& filename) const {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << "Generation: " << generation << "\n";
        for (int y = 0; y < m_grille.getHauteur(); ++y) {
            for (int x = 0; x < m_grille.getLargeur(); ++x) {
                file << (m_grille.accessCell(x, y).estVivante() ? "1 " : "0 ");
            }
            file << "\n";
        }
        file << "\n";
    }
}