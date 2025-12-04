#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <vector>
#include "Cellule.hpp"

/**
 * @class Grille
 * @brief Représente l'espace de simulation du Jeu de la Vie.
 * * Conception optimisée :
 * Utilise un std::vector linéarisé (1D) pour stocker une grille 2D.
 * Cela garantit la contiguïté mémoire et améliore les performances du cache CPU
 * par rapport à un tableau de pointeurs ou un double vecteur.
 */
class Grille {
private:
    int m_largeur;
    int m_hauteur;

    // Conteneur unique stockant toutes les cellules.
    // L'accès (x, y) est converti en index (y * largeur + x).
    std::vector<Cell> m_grid;

    // Méthode interne pour initialiser ou réinitialiser la grille
    void initialiserGrille();

public:
    // Constructeur : Alloue dynamiquement la mémoire via le vecteur
    Grille(int largeur, int hauteur);

    // Destructeur : Optionnel en C++ moderne car std::vector gère sa propre mémoire.
    // On le définit par défaut pour la clarté.
    ~Grille() = default;

    // --- Accesseurs (Getters) ---

    int getLargeur() const { return m_largeur; }
    int getHauteur() const { return m_hauteur; }

    // Accès en lecture/écriture (retourne une référence)
    Cell& accessCell(int x, int y);

    // Accès en lecture seule (const correctness)
    const Cell& accessCell(int x, int y) const;

    // --- Logique métier ---

    // Calcule le nombre de voisins vivants pour une position donnée.
    // Utilise une logique toroïdale (les bords sont connectés).
    int compterVoisinsVivants(int x, int y) const;

    // Accesseur direct au tableau brut (utile pour l'affichage rapide ou le debug)
    const std::vector<Cell>& getData() const { return m_grid; }
};

#endif // GRILLE_HPP