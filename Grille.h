// Grille.h (MISE À JOUR)
#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.h"
#include <vector>
#include <iostream>

class Grille {
private:
    int lignes_;
    int colonnes_;
    std::vector<std::vector<Cellule>> grille_actuelle_;

public:
    // ... (Le constructeur, compterVoisinsVivants, verifierLesCellules sont inchangés) ...

    Grille(int lignes, int colonnes) :
        lignes_(lignes), colonnes_(colonnes),
        grille_actuelle_(lignes, std::vector<Cellule>(colonnes)) {
    }

    void chargerCellules(int ligne, int colonne, Cellule::Etat etat) {
        if (ligne >= 0 && ligne < lignes_ && colonne >= 0 && colonne < colonnes_) {
            grille_actuelle_[ligne][colonne].setEtat(etat);
        }
    }

    // NOUVELLES MÉTHODES POUR L'AFFICHAGE SFML
    int getLignes() const { return lignes_; }
    int getColonnes() const { return colonnes_; }

    // Fournit l'accès à une cellule spécifique
    const Cellule& getCellule(int r, int c) const {
        // Supposons que les coordonnées soient valides (vérifiées par l'appelant ou initialement)
        return grille_actuelle_[r][c];
    }

    // ... (Le reste de la classe Grille comme avant, y compris verifierLesCellules et compterVoisinsVivants) ...
    // Note: Vous devrez copier toutes les méthodes précédentes dans ce fichier .h

    // Inclure ici l'implémentation de verifierLesCellules (ou la déplacer dans un .cpp)
    void verifierLesCellules() {
        std::vector<std::vector<Cellule>> prochaine_grille = grille_actuelle_;

        for (int i = 0; i < lignes_; ++i) {
            for (int j = 0; j < colonnes_; ++j) {
                int vivants = compterVoisinsVivants(i, j);
                Cellule::Etat nouvel_etat = grille_actuelle_[i][j].getEtat();

                if (grille_actuelle_[i][j].estVivante()) {
                    if (vivants < 2 || vivants > 3) {
                        nouvel_etat = Cellule::MORTE;
                    }
                }
                else {
                    if (vivants == 3) {
                        nouvel_etat = Cellule::VIVANTE;
                    }
                }

                prochaine_grille[i][j].setEtat(nouvel_etat);
            }
        }
        grille_actuelle_ = prochaine_grille;
    }

    int compterVoisinsVivants(int r, int c) const; // Déclaration simple si implémentation dans .cpp
};

// Si vous ne voulez pas créer de .cpp, incluez l'implémentation de compterVoisinsVivants ici.

#endif