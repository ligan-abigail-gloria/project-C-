#include "Banque.h"
#include "CompteCourant.h"
#include "CompteEpargne.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

Banque::Banque(const std::string& nom) : nom(nom) {}

const std::string& Banque::getNom() const { return nom; }

const std::vector<std::shared_ptr<Client> >& Banque::getClients() const {
    return clients;
}

const std::vector<std::shared_ptr<Compte> >& Banque::getComptes() const {
    return comptes;
}

std::shared_ptr<Client> Banque::trouverClient(const std::string& identifiant) const {
    for (std::size_t index = 0; index < clients.size(); ++index) {
        if (clients[index]->getIdentifiant() == identifiant) {
            return clients[index];
        }
    }
    return std::shared_ptr<Client>();
}

std::shared_ptr<Compte> Banque::trouverCompte(const std::string& rib) const {
    for (std::size_t index = 0; index < comptes.size(); ++index) {
        if (comptes[index]->getRib() == rib) {
            return comptes[index];
        }
    }
    return std::shared_ptr<Compte>();
}

bool Banque::ajouterClient(const std::shared_ptr<Client>& client) {
    if (!client || client->getIdentifiant().empty() ||
        client->getNom().empty() || client->getAdresse().empty() ||
        client->getTelephone().empty() ||
        trouverClient(client->getIdentifiant())) {
        return false;
    }
    const Particulier* particulier = dynamic_cast<const Particulier*>(client.get());
    const Entreprise* entreprise = dynamic_cast<const Entreprise*>(client.get());
    const Association* association = dynamic_cast<const Association*>(client.get());
    if ((particulier && (particulier->getPrenom().empty() || particulier->getCin().empty())) ||
        (entreprise && (entreprise->getMatriculeFiscal().empty() || entreprise->getContact().empty())) ||
        (association && (association->getMatricule().empty() || association->getObjet().empty()))) {
        return false;
    }
    clients.push_back(client);
    return true;
}

bool Banque::ouvrirCompteCourant(const std::string& rib,
                                 const std::string& identifiantClient,
                                 double soldeInitial, double seuilMin) {
    const std::shared_ptr<Client> client = trouverClient(identifiantClient);
    if (!client || rib.empty() || trouverCompte(rib) ||
        !std::isfinite(soldeInitial) || soldeInitial < 0.0 ||
        !std::isfinite(seuilMin) || seuilMin > 0.0) {
        return false;
    }
    comptes.push_back(std::shared_ptr<Compte>(
        new CompteCourant(rib, client, soldeInitial, seuilMin)));
    return true;
}

bool Banque::ouvrirCompteEpargne(const std::string& rib,
                                 const std::string& identifiantClient,
                                 double soldeInitial, double tauxInteret) {
    const std::shared_ptr<Client> client = trouverClient(identifiantClient);
    if (!client || rib.empty() || trouverCompte(rib) ||
        !std::isfinite(soldeInitial) || soldeInitial < 5.0 ||
        !std::isfinite(tauxInteret) || tauxInteret < 0.0) {
        return false;
    }
    comptes.push_back(std::shared_ptr<Compte>(
        new CompteEpargne(rib, client, soldeInitial, tauxInteret)));
    return true;
}

bool Banque::transferer(const std::string& ribSource,
                        const std::string& ribDestinataire, double montant) {
    const std::shared_ptr<Compte> source = trouverCompte(ribSource);
    const std::shared_ptr<Compte> destinataire = trouverCompte(ribDestinataire);
    if (!source || !destinataire) {
        return false;
    }
    return source->transfererVers(*destinataire, montant);
}

void Banque::afficherClients() const {
    if (clients.empty()) {
        std::cout << "Aucun client enregistre." << std::endl;
        return;
    }
    for (std::size_t index = 0; index < clients.size(); ++index) {
        std::cout << "\n--- Client " << index + 1 << " ---" << std::endl;
        clients[index]->afficher();
    }
}

void Banque::afficherComptes() const {
    if (comptes.empty()) {
        std::cout << "Aucun compte ouvert." << std::endl;
        return;
    }
    for (std::size_t index = 0; index < comptes.size(); ++index) {
        std::cout << "\n--- Compte " << index + 1 << " ---" << std::endl;
        comptes[index]->afficher();
    }
}

void Banque::afficherComptesClient(const std::string& identifiantClient) const {
    bool trouve = false;
    for (std::size_t index = 0; index < comptes.size(); ++index) {
        if (comptes[index]->getClient().getIdentifiant() == identifiantClient) {
            comptes[index]->afficher();
            trouve = true;
        }
    }
    if (!trouve) {
        std::cout << "Aucun compte pour ce client." << std::endl;
    }
}

void Banque::afficherDossierClient(const std::string& identifiantClient) const {
    const std::shared_ptr<Client> client = trouverClient(identifiantClient);
    if (!client) {
        std::cout << "Client introuvable." << std::endl;
        return;
    }
    std::cout << "\n========== Dossier client ==========" << std::endl;
    client->afficher();
    std::cout << "Conseil de compte : " << client->getConseilCompte() << std::endl;
    std::cout << "\nComptes associes :" << std::endl;
    afficherComptesClient(identifiantClient);
}