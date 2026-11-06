#include "Client.h"
#include <iostream>

Client::Client(const std::string& identifiant, const std::string& nom,
               const std::string& adresse, const std::string& telephone)
    : identifiant(identifiant), nom(nom), adresse(adresse), telephone(telephone) {}

Client::~Client() {}

const std::string& Client::getIdentifiant() const { return identifiant; }
const std::string& Client::getNom() const { return nom; }
const std::string& Client::getAdresse() const { return adresse; }
const std::string& Client::getTelephone() const { return telephone; }
void Client::setNom(const std::string& valeur) { nom = valeur; }
void Client::setAdresse(const std::string& valeur) { adresse = valeur; }
void Client::setTelephone(const std::string& valeur) { telephone = valeur; }

void Client::afficher() const {
    std::cout << "Type : " << getType() << std::endl;
    std::cout << "Identifiant : " << identifiant << std::endl;
    std::cout << "Nom : " << nom << std::endl;
    std::cout << "Adresse : " << adresse << std::endl;
    std::cout << "Telephone : " << telephone << std::endl;
}

Particulier::Particulier(const std::string& identifiant, const std::string& nom,
                         const std::string& prenom, const std::string& cin,
                         const std::string& adresse, const std::string& telephone)
    : Client(identifiant, nom, adresse, telephone), prenom(prenom), cin(cin) {}

const std::string& Particulier::getPrenom() const { return prenom; }
const std::string& Particulier::getCin() const { return cin; }
void Particulier::setPrenom(const std::string& valeur) { prenom = valeur; }
void Particulier::setCin(const std::string& valeur) { cin = valeur; }
std::string Particulier::getType() const { return "Particulier"; }
std::string Particulier::getConseilCompte() const {
    return "Compte courant pour les operations quotidiennes; compte epargne pour constituer une reserve.";
}

void Particulier::afficher() const {
    Client::afficher();
    std::cout << "Prenom : " << prenom << std::endl;
    std::cout << "CIN : " << cin << std::endl;
}

Entreprise::Entreprise(const std::string& identifiant,
                       const std::string& raisonSociale,
                       const std::string& matriculeFiscal,
                       const std::string& contact, const std::string& adresse,
                       const std::string& telephone)
    : Client(identifiant, raisonSociale, adresse, telephone),
      matriculeFiscal(matriculeFiscal), contact(contact) {}

const std::string& Entreprise::getMatriculeFiscal() const { return matriculeFiscal; }
const std::string& Entreprise::getContact() const { return contact; }
void Entreprise::setMatriculeFiscal(const std::string& valeur) { matriculeFiscal = valeur; }
void Entreprise::setContact(const std::string& valeur) { contact = valeur; }
std::string Entreprise::getType() const { return "Entreprise"; }
std::string Entreprise::getConseilCompte() const {
    return "Compte courant pour les recettes et depenses professionnelles; epargne possible pour une tresorerie disponible.";
}

void Entreprise::afficher() const {
    Client::afficher();
    std::cout << "Matricule fiscal : " << matriculeFiscal << std::endl;
    std::cout << "Contact : " << contact << std::endl;
}

Association::Association(const std::string& identifiant, const std::string& nom,
                         const std::string& matricule, const std::string& objet,
                         const std::string& adresse, const std::string& telephone)
    : Client(identifiant, nom, adresse, telephone),
      matricule(matricule), objet(objet) {}

const std::string& Association::getMatricule() const { return matricule; }
const std::string& Association::getObjet() const { return objet; }
void Association::setMatricule(const std::string& valeur) { matricule = valeur; }
void Association::setObjet(const std::string& valeur) { objet = valeur; }
std::string Association::getType() const { return "Association"; }
std::string Association::getConseilCompte() const {
    return "Compte courant pour les cotisations et depenses; epargne possible pour les fonds non affectes.";
}

void Association::afficher() const {
    Client::afficher();
    std::cout << "Matricule : " << matricule << std::endl;
    std::cout << "Objet : " << objet << std::endl;
}