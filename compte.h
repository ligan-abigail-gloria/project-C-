#ifndef COMPTE_H
#define COMPTE_H

#include <memory>
#include <string>
#include "Client.h"

class Compte {
protected:
    std::string rib;
    double solde;
    std::shared_ptr<Client> client;

public:
    Compte(const std::string& rib, const std::shared_ptr<Client>& client,
           double solde = 0.0);
    virtual ~Compte();

    const std::string& getRib() const;
    double getSolde() const;
    const Client& getClient() const;
    const std::shared_ptr<Client>& getClientPtr() const;

    virtual bool deposer(double montant);
    virtual bool retirer(double montant);
    bool transfererVers(Compte& destinataire, double montant);
    virtual void afficher() const;
};

#endif
