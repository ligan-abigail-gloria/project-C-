#ifndef BANQUE_H
#define BANQUE_H

#include <memory>
#include <string>
#include <vector>
#include "Client.h"
#include "compte.h"

class Banque {
private:
    std::string nom;
    std::vector<std::shared_ptr<Client> > clients;
    std::vector<std::shared_ptr<Compte> > comptes;

public:
    explicit Banque(const std::string& nom);

    const std::string& getNom() const;
    const std::vector<std::shared_ptr<Client> >& getClients() const;
    const std::vector<std::shared_ptr<Compte> >& getComptes() const;
    std::shared_ptr<Client> trouverClient(const std::string& identifiant) const;
    std::shared_ptr<Compte> trouverCompte(const std::string& rib) const;

    bool ajouterClient(const std::shared_ptr<Client>& client);
    bool ouvrirCompteCourant(const std::string& rib,
                            const std::string& identifiantClient,
                            double soldeInitial, double seuilMin = -500.0);
    bool ouvrirCompteEpargne(const std::string& rib,
                            const std::string& identifiantClient,
                            double soldeInitial, double tauxInteret);
    bool transferer(const std::string& ribSource,
                    const std::string& ribDestinataire, double montant);
    void afficherClients() const;
    void afficherComptes() const;
    void afficherComptesClient(const std::string& identifiantClient) const;
    void afficherDossierClient(const std::string& identifiantClient) const;
};

#endif