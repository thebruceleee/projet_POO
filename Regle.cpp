#include "Regle.hpp"

using namespace std;

Regles::Regles()
    : m_modeGraphique(false), m_maxIterations(0)
{
    // Les m_lois sont initialisées automatiquement avec les règles de Conway
    // grâce au constructeur par défaut de la struct LoisBiologiques.
}

void Regles::setLois(const LoisBiologiques& nouvellesLois) {
    // On pourrait ajouter ici des assertions pour vérifier la cohérence
    // Exemple : if (nouvellesLois.isolement > nouvellesLois.surpop) ...
    m_lois = nouvellesLois;
}

const LoisBiologiques& Regles::getLois() const {
    return m_lois;
}

void Regles::setModeGraphique(bool actif) {
    m_modeGraphique = actif;
}

bool Regles::isModeGraphique() const {
    return m_modeGraphique;
}

void Regles::setMaxIterations(unsigned int max) {
    m_maxIterations = max;
}

bool Regles::aUneLimiteDeTemps() const {
    // Plus élégant que de gérer un booléen séparé
    return m_maxIterations > 0;
}

unsigned int Regles::getMaxIterations() const {
    return m_maxIterations;
}