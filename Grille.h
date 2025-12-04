// Grille.h
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
    Grille(int lignes, int colonnes) :
        lignes_(lignes), colonnes_(colonnes),
        grille_actuelle_(lignes, std::vector<Cellule>(colonnes)) {
    }

    void chargerCellules(int ligne, int colonne, Cellule::Etat etat) {
        if (ligne >= 0 && ligne < lignes_ && colonne >= 0 && colonne < colonnes_) {
            grille_actuelle_[ligne][colonne].setEtat(etat);
        }
    }

    int compterVoisinsVivants(int r, int c) const {
        int vivants = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue; // Ne pas compter la cellule elle-même

                int voisin_r = (r + i + lignes_) % lignes_; // Gestion des bords (toroidale)
                int voisin_c = (c + j + colonnes_) % colonnes_;

                if (grille_actuelle_[voisin_r][voisin_c].estVivante()) {
                    vivants++;
                }
            }
        }
        return vivants;
    }

    // Corresponds à la boucle 'pour chaque cellule' de votre diagramme
    void verifierLesCellules() {
        std::vector<std::vector<Cellule>> prochaine_grille = grille_actuelle_;

        for (int i = 0; i < lignes_; ++i) {
            for (int j = 0; j < colonnes_; ++j) {
                int vivants = compterVoisinsVivants(i, j);
                Cellule::Etat nouvel_etat = grille_actuelle_[i][j].getEtat();

                // 1. Si vivante, et < 2 voisins ou > 3 voisins -> MORTE
                // 2. Si morte, et 3 voisins -> VIVANTE
                // 3. Sinon, l'état reste le même.

                if (grille_actuelle_[i][j].estVivante()) {
                    if (vivants < 2 || vivants > 3) {
                        nouvel_etat = Cellule::MORTE; // "Si vivante et (<2 ou >3) adjacents vivants => morte"
                    }
                }
                else {
                    if (vivants == 3) {
                        nouvel_etat = Cellule::VIVANTE; // "Si morte et 3 adjacents vivants => vivante"
                    }
                }

                prochaine_grille[i][j].setEtat(nouvel_etat);
            }
        }
        grille_actuelle_ = prochaine_grille;
    }

    void afficher() const {
        for (int i = 0; i < lignes_; ++i) {
            for (int j = 0; j < colonnes_; ++j) {
                std::cout << (grille_actuelle_[i][j].estVivante() ? 'O' : '.');
            }
            std::cout << "\n";
        }
    }
};

#endif
