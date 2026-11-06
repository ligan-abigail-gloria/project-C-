#ifndef COMPTEEPARGNE_H
#define COMPTEEPARGNE_H

#include "compte.h"

class CompteEpargne : public Compte {
private:
    double tauxInteret;
    static const double SOLDE_MIN;

public:
    CompteEpargne(const std::string& rib, const std::shared_ptr<Client>& client,
                  double solde, double tauxInteret);

    double getTaux() const;
    double calculerInteret() const;

    bool retirer(double montant) override;
    void afficher() const override;
};

#endif
