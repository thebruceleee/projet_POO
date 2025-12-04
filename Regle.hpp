#ifndef REGLE_HPP
#define REGLE_HPP

#include <iostream>

// Structure simple pour regrouper les lois biologiques.
// C'est une bonne pratique ("Data Oriented") de grouper les données liées.
struct LoisBiologiques {
    unsigned int isolement;   // Meurt si < à ce nombre (ex: 2)
    unsigned int surpop;      // Meurt si > à ce nombre (ex: 3)
    unsigned int naissance;   // Nait si == à ce nombre (ex: 3)

    // Constructeur par défaut : Règles standards du "Game of Life" (Conway)
    LoisBiologiques(unsigned int iso = 2, unsigned int surp = 3, unsigned int naiss = 3)
        : isolement(iso), surpop(surp), naissance(naiss) {
    }
};

/**
 * @class Regles
 * @brief Gestionnaire de configuration de la simulation.
 * * Cette classe centralise le paramétrage (seuils de vie/mort)
 * ainsi que les limites de la simulation (mode d'affichage, itérations max).
 */
class Regles {
private:
    // Configuration du moteur de jeu
    LoisBiologiques m_lois;

    // Configuration de l'exécution
    bool m_modeGraphique;
    unsigned int m_maxIterations; // 0 signifie "Infini"

public:
    // Constructeur avec valeurs par défaut
    Regles();
    ~Regles() = default;

    // --- Gestion des Lois Biologiques ---

    // Définit de nouvelles règles biologiques via la structure dédiée
    void setLois(const LoisBiologiques& nouvellesLois);

    // Récupère les lois actuelles (lecture seule)
    const LoisBiologiques& getLois() const;

    // --- Gestion de la Simulation ---

    void setModeGraphique(bool actif);
    bool isModeGraphique() const;

    // Définit la limite d'itérations. 0 = Simulation infinie.
    void setMaxIterations(unsigned int max);

    // Vérifie si la simulation a une fin programmée
    bool aUneLimiteDeTemps() const;

    unsigned int getMaxIterations() const;
};

#endif // REGLE_HPP