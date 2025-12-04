// Cellule.h
#ifndef CELLULE_H
#define CELLULE_H

class Cellule {
public:
    enum Etat { MORTE, VIVANTE };

private:
    Etat etat_;

public:
    Cellule() : etat_(MORTE) {}
    Cellule(Etat e) : etat_(e) {}

    Etat getEtat() const { return etat_; }
    void setEtat(Etat e) { etat_ = e; }

    bool estVivante() const { return etat_ == VIVANTE; }
};

#endif