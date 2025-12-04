#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

// Inclusion des modules refactorisés
#include "Grille.hpp"
#include "Regle.hpp"

/**
 * @class Game
 * @brief Contrôleur principal de l'application (Pattern MVC).
 * * Cette classe orchestre :
 * 1. Le Modèle : La Grille (données) et les Règles (logique).
 * 2. La Vue : Le rendu SFML (méthode render).
 * 3. Les Entrées : Gestion des modes de jeu (Glider, Obstacle, etc.).
 */
class Game {
public:
    // Constructeur : Prépare la grille et charge les assets (RAII)
    Game(int largeur, int hauteur);

    // Destructeur par défaut (les objets SFML et vector se nettoient seuls)
    ~Game();

    // --- Boucle de Jeu ---

    // Met à jour la simulation d'une étape (Calcul physique)
    // Prend les règles en lecture seule (const ref) pour éviter les effets de bord.
    void update(const Regles& regles);

    // Affiche toute la scène (Grille + UI + Fantômes)
    void render(sf::RenderWindow& window, int cellSize, int modeJeu);

    // --- Gestion de fichiers ---

    // Sauvegarde l'état actuel dans un fichier texte (anciennement 'display')
    void saveToText(int generation, const std::string& filename) const;

    // --- Contrôles & Accesseurs ---

    void startMusic() { m_music.play(); }
    void stopMusic() { m_music.stop(); }

    // Accès direct à la grille pour les interactions souris dans le Main
    Grille& getGrille() { return m_grille; }
    const Grille& getGrille() const { return m_grille; }

private:
    // --- Membres (Préfixe m_ pour 'member') ---

    Grille m_grille;

    // Ressources SFML
    sf::Music m_music;
    sf::Font m_fontRoboto;
    sf::Font m_fontScript;

    // --- Méthodes Internes (Helpers) ---
    // Ces fonctions sont cachées de l'utilisateur de la classe

    void initResources();
    void drawGrid(sf::RenderWindow& window, int cellSize);
    void drawUI(sf::RenderWindow& window, int cellSize, int mode);
    void drawPreview(sf::RenderWindow& window, int cellSize, int gx, int gy, int mode);
};

#endif // GAME_HPP