// FichierEntree.h
#ifndef FICHIERENTREE_H
#define FICHIERENTREE_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include "Cellule.h"

class FichierEntree {
public:
    // tuple<lignes, colonnes, liste_de_coordonnees_vivantes>
    using DonneeGrille = std::tuple<int, int, std::vector<std::pair<int, int>>>;

    bool verifierExistence(const std::string& nomFichier) const {
        std::ifstream fichier(nomFichier);
        return fichier.is_open();
    }

    // Récupère les dimensions et les positions des cellules vivantes
    DonneeGrille lireLeFichier(const std::string& nomFichier) {
        std::ifstream fichier(nomFichier);
        int lignes = 0;
        int colonnes = 0;
        std::vector<std::pair<int, int>> vivantes;

        // Lire la première ligne pour les dimensions (ex: 10 10)
        std::string ligne_dim;
        if (std::getline(fichier, ligne_dim)) {
            std::stringstream ss(ligne_dim);
            ss >> lignes >> colonnes;
        }

        // Lire les coordonnées des cellules vivantes (ex: 1 5)
        std::string ligne;
        while (std::getline(fichier, ligne)) {
            std::stringstream ss(ligne);
            int r, c;
            if (ss >> r >> c) {
                vivantes.push_back({ r, c });
            }
        }

        fichier.close();
        return std::make_tuple(lignes, colonnes, vivantes);
    }
};

#endif