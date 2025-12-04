// Programme.h / Programme.cpp (pour la simplicité, combiné ici)
#include "Grille.h"
#include "FichierEntree.h"
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

// Simulation d'une interface très simple
class Interface {
public:
    void afficherGrilleEtEtat(const Grille& grille, int generation) const {
        std::cout << "\033[2J\033[1;1H"; // Efface l'écran (pour Unix/Linux/macOS)
        std::cout << "🚀 Jeu de la Vie - Génération " << generation << "\n";
        grille.afficher();
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Pause
    }

    std::string saisirNomFichier() const {
        std::string nomFichier;
        std::cout << "Veuillez entrer le nom du fichier d'entrée: ";
        std::cin >> nomFichier;
        return nomFichier;
    }

    // Simuler le choix du mode
    std::string choisirMode() const {
        std::string mode;
        std::cout << "Choisissez le mode (graphique/console) : ";
        std::cin >> mode;
        return mode;
    }

    void afficherErreur(const std::string& msg) const {
        std::cerr << "Erreur: " << msg << "\n";
    }
};

class Programme {
private:
    Grille* grille_ = nullptr;
    FichierEntree fichier_entree_;
    Interface interface_;
    int nb_iterations_ = 50; // Nombre de cycles de jeu

public:
    // La boucle principale qui suit les étapes de votre diagramme
    void demarrer() {
        std::cout << "Début du programme du Jeu de la Vie.\n";

        // 1. Utiliteur (saisie) -> Programme (demande) -> Fichier d'entrée (vérification)
        std::string nomFichier = interface_.saisirNomFichier();
        if (!fichier_entree_.verifierExistence(nomFichier)) {
            interface_.afficherErreur("Fichier d'entrée introuvable ou non lisible.");
            return;
        }

        // 2. Programme (lecture) <- Fichier d'entrée (données chargées)
        auto [lignes, colonnes, vivantes] = fichier_entree_.lireLeFichier(nomFichier);

        // 3. Programme (création) -> Grille
        grille_ = new Grille(lignes, colonnes);

        // 4. Programme (chargement) -> Cellules
        for (const auto& coord : vivantes) {
            grille_->chargerCellules(coord.first, coord.second, Cellule::VIVANTE);
        }

        // 5. Boucle de jeu (simulée par nb_iterations)
        // Programme -> Grille (vérification des cellules)
        std::cout << "Chargement terminé. Lancement de la simulation.\n";

        std::string mode = interface_.choisirMode();

        if (mode == "graphique") {
            // mode graphique (simulation)
            for (int k = 0; k < nb_iterations_; ++k) {
                // Programme -> Interface (Afficher la grille)
                interface_.afficherGrilleEtEtat(*grille_, k + 1);
                // Programme -> Grille (Vérification des cellules / Avancement du temps)
                grille_->verifierLesCellules();
            }
        }
        else if (mode == "console") {
            // mode console (simulation)
            for (int k = 0; k < nb_iterations_; ++k) {
                std::cout << "\n--- Génération " << k + 1 << " ---\n";
                grille_->afficher(); // Affichage dans le mode console
                grille_->verifierLesCellules();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        else {
            interface_.afficherErreur("Mode non reconnu.");
        }
    }

    ~Programme() {
        delete grille_; // Libération de la mémoire
    }
};
