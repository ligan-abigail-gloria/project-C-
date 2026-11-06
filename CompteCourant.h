#ifndef COMPTECOURANT_H
#define COMPTECOURANT_H

#include "compte.h"

class CompteCourant : public Compte {
private:
    double seuilMin;

public:
    CompteCourant(const std::string& rib, const std::shared_ptr<Client>& client,
                  double solde = 0.0, double seuilMin = -500.0);

    double getSeuilMin() const;

    bool retirer(double montant) override;
    void afficher() const override;
};

#endif
