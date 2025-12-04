#include "Cellule.hpp"

// Constructeur : simple affectation des membres
Cell::Cell(int x, int y, EtatCellule etatInit)
    : m_x(x), m_y(y), m_etat(etatInit)
{
}

// Logique combinée : une cellule est "vivante" au sens du jeu 
// si elle est VIVANTE (standard) ou OBSTACLE_VIVANT (fixe).
bool Cell::estVivante() const {
    return (m_etat == EtatCellule::VIVANTE || m_etat == EtatCellule::OBSTACLE_VIVANT);
}

bool Cell::estObstacle() const {
    return (m_etat == EtatCellule::OBSTACLE_VIVANT || m_etat == EtatCellule::OBSTACLE_MORT);
}

void Cell::rendreVivante() {
    // Règle de sécurité : un obstacle ne peut pas être modifié par la simulation
    if (!estObstacle()) {
        m_etat = EtatCellule::VIVANTE;
    }
}

void Cell::rendreMorte() {
    if (!estObstacle()) {
        m_etat = EtatCellule::MORTE;
    }
}

void Cell::setObstacle(bool actif, bool vivant) {
    if (!actif) {
        // Si on désactive l'obstacle, la cellule devient morte par défaut
        m_etat = EtatCellule::MORTE;
        return;
    }

    // Sinon on applique l'état obstacle correspondant
    m_etat = vivant ? EtatCellule::OBSTACLE_VIVANT : EtatCellule::OBSTACLE_MORT;
}