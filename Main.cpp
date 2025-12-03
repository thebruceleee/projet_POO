// main.cpp
#include <ProjetsSFML.cpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Inclure les classes de logique (assurez-vous que ces fichiers sont dans votre projet)
#include "Grille.h"
#include "Cellule.h"
#include "FichierEntree.h" 

// --- Configuration de l'affichage ---
const int TAILLE_CELLULE = 20; // Taille d'un carré en pixels
const float TEMPS_GENERATION = 0.2f; // Délai en secondes entre chaque génération (5 générations/seconde)

/**
 * @brief Fonction pour dessiner la grille dans la fenêtre SFML.
 */
void dessinerGrille(sf::RenderWindow& window, const Grille& grille);

/**
 * @brief Point d'entrée principal du programme.
 */
int main() {

    FichierEntree gestionnaireFichier;
    std::string nomFichier = "config.txt"; // Nom du fichier par défaut

    // --- PHASE 1: INITIALISATION (Lecture du fichier) ---
    // Simule la partie "Vérifier existence" et "Lire le fichier" du diagramme
    if (!gestionnaireFichier.verifierExistence(nomFichier)) {
        std::cerr << "Erreur: Fichier d'entrée '" << nomFichier << "' non trouvé. Créez-le avec les dimensions et les coordonnées.\n";
        return 1;
    }

    auto [lignes, colonnes, vivantes] = gestionnaireFichier.lireLeFichier(nomFichier);

    if (lignes <= 0 || colonnes <= 0) {
        std::cerr << "Erreur: Dimensions de grille invalides dans le fichier.\n";
        return 1;
    }

    // Création et chargement de la grille (Simule "Charger la grille" et "Charger les cellules")
    Grille grille(lignes, colonnes);
    for (const auto& coord : vivantes) {
        grille.chargerCellules(coord.first, coord.second, Cellule::VIVANTE);
    }

    // --- PHASE 2: CONFIGURATION SFML ---
    int largeurFenetre = colonnes * TAILLE_CELLULE;
    int hauteurFenetre = lignes * TAILLE_CELLULE;

    sf::RenderWindow window(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie (SFML)");
    window.setFramerateLimit(60); // Limite le taux de rafraîchissement

    sf::Clock horloge;
    float tempsAccumule = 0.0f;

    // --- PHASE 3: BOUCLE PRINCIPALE (Simulation et Affichage) ---
    while (window.isOpen()) {

        // 1. GESTION DES ÉVÉNEMENTS (Utilisateur)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 2. MISE À JOUR DE LA LOGIQUE (Programme -> Grille -> Cellules)
        // Ceci gère la partie "boucle" du diagramme ("Pour chaque cellule")
        float deltaTime = horloge.restart().asSeconds();
        tempsAccumule += deltaTime;

        if (tempsAccumule >= TEMPS_GENERATION) {
            grille.verifierLesCellules(); // Calcule la nouvelle génération
            tempsAccumule = 0.0f;
        }

        // 3. RENDU (Interface)
        // Simule "Afficher la grille"
        window.clear(sf::Color::Black);
        dessinerGrille(window, grille);
        window.display();
    }

    return 0;
}

// Implementation de la fonction dessinerGrille
void dessinerGrille(sf::RenderWindow& window, const Grille& grille) {
    const int TAILLE_CELLULE = 20;
    sf::RectangleShape forme(sf::Vector2f(TAILLE_CELLULE, TAILLE_CELLULE));
    forme.setOutlineThickness(1.0f);
    forme.setOutlineColor(sf::Color(50, 50, 50));

    for (int i = 0; i < grille.getLignes(); ++i) {
        for (int j = 0; j < grille.getColonnes(); ++j) {
            forme.setPosition(j * TAILLE_CELLULE, i * TAILLE_CELLULE);
            if (grille.getCellule(i, j).estVivante()) {
                forme.setFillColor(sf::Color::Green);
            } else {
                forme.setFillColor(sf::Color::Black);
            }
            window.draw(forme);
        }
    }
}