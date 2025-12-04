#include "Grille.hpp"

// Constructeur : 
// On utilise la liste d'initialisation pour configurer les dimensions et 
// allouer le vecteur en une seule fois. C'est plus rapide que de faire des push_back.
Grille::Grille(int largeur, int hauteur)
    : m_largeur(largeur), m_hauteur(hauteur), m_grid(largeur* hauteur)
{
    // Une fois le vecteur alloué, on configure les coordonnées internes de chaque cellule
    initialiserGrille();
}

// Méthode privée pour configurer les cellules après allocation
void Grille::initialiserGrille() {
    for (int y = 0; y < m_hauteur; ++y) {
        for (int x = 0; x < m_largeur; ++x) {
            // On récupère la cellule et on lui dit "tu es en (x,y)"
            // Note : accessCell gère la conversion 2D -> 1D
            accessCell(x, y).setCoords(x, y);
        }
    }
}

// Accesseur Modifiable
// Conversion de coordonnées (x, y) vers l'index linéaire i = y * largeur + x
Cell& Grille::accessCell(int x, int y) {
    return m_grid[y * m_largeur + x];
}

// Accesseur Constant (Lecture seule)
const Cell& Grille::accessCell(int x, int y) const {
    return m_grid[y * m_largeur + x];
}

// Calcul des voisins optimisé (Mathématiques vs Conditionnelles)
// Cette méthode remplace "iteration(Cell* cell)"
int Grille::compterVoisinsVivants(int x, int y) const {
    int voisinsVivants = 0;

    // Parcours des 8 voisins relatifs (-1, 0, +1)
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {

            // On saute la cellule centrale (soi-même)
            if (dx == 0 && dy == 0) continue;

            // Gestion du Tore (Monde circulaire) via l'opérateur Modulo (%).
            // Formule : (coord + delta + dimension) % dimension
            // Cela gère automatiquement les dépassements positifs et négatifs
            // sans avoir besoin de 4 blocs if/else.
            int voisinX = (x + dx + m_largeur) % m_largeur;
            int voisinY = (y + dy + m_hauteur) % m_hauteur;

            // On accède directement à la cellule dans le vecteur contigu
            if (accessCell(voisinX, voisinY).estVivante()) {
                voisinsVivants++;
            }
        }
    }

    return voisinsVivants;
}