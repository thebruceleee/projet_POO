#ifndef CELL_HPP
#define CELL_HPP

// On remplace les multiples classes par une énumération typée (C++11).
// Cela tient sur un seul octet en mémoire (char) au lieu d'un pointeur (8 octets).
enum class EtatCellule : char {
    MORTE,
    VIVANTE,
    // Les obstacles sont des états statiques qui ne changent pas
    OBSTACLE_VIVANT,
    OBSTACLE_MORT
};

/**
 * @class Cell
 * @brief Brique fondamentale de la simulation.
 * * Optimisation : Cette classe est conçue comme un "Value Type".
 * Elle ne gère pas de mémoire dynamique (pas de new/delete),
 * ce qui la rend extrêmement rapide à copier et à stocker dans un std::vector.
 */
class Cell {
private:
    int m_x;
    int m_y;
    EtatCellule m_etat;

public:
    // Constructeur : Initialisation directe, pas d'allocation dynamique.
    Cell(int x = 0, int y = 0, EtatCellule etatInit = EtatCellule::MORTE);

    // Le destructeur est implicite et trivial (gain de performance).
    ~Cell() = default;

    // --- Accesseurs ---
    int getX() const { return m_x; }
    int getY() const { return m_y; }

    // --- Logique Métier ---

    // Vérifie si la cellule contribue à la population (Vivant ou Obstacle Vivant)
    bool estVivante() const;

    // Vérifie si la cellule est figée (Obstacle)
    bool estObstacle() const;

    // --- Mutateurs (Actions) ---
    // Ces méthodes remplacent les "new/delete" de l'ancienne version

    void rendreVivante();
    void rendreMorte();

    // Gestion spécifique des obstacles
    void setObstacle(bool actif, bool vivant);
};

#endif // CELL_HPP