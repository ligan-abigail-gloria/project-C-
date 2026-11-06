#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "Banque.h"
#include "CompteEpargne.h"

using namespace std;

string lireTexte(const string& message) {
    string valeur;
    cout << message;
    if (!getline(cin, valeur)) {
        return "";
    }
    return valeur;
}

string lireModification(const string& champ) {
    return lireTexte(champ + " (laisser vide pour ne pas modifier) : ");
}

int lireEntier(const string& message) {
    while (true) {
        const string ligne = lireTexte(message);
        if (!cin) return 0;
        istringstream flux(ligne);
        int valeur;
        char reste;
        if (flux >> valeur && !(flux >> reste)) {
            return valeur;
        }
        cout << "Veuillez saisir un nombre entier valide." << endl;
    }
}

double lireMontant(const string& message) {
    while (true) {
        string ligne = lireTexte(message);
        if (!cin) return 0.0;
        replace(ligne.begin(), ligne.end(), ',', '.');
        istringstream flux(ligne);
        double valeur;
        char reste;
        if (flux >> valeur && !(flux >> reste) && isfinite(valeur)) {
            return valeur;
        }
        cout << "Veuillez saisir un nombre valide." << endl;
    }
}

void creerClient(Banque& banque) {
    cout << "\nType de client : 1. Particulier  2. Entreprise  3. Association" << endl;
    const int type = lireEntier("Votre choix : ");
    if (type < 1 || type > 3) {
        cout << "Type de client invalide." << endl;
        return;
    }

    const string identifiant = lireTexte("Identifiant unique du client : ");
    const string nom = lireTexte(type == 2 ? "Raison sociale : " :
                                 type == 3 ? "Nom de l'association : " : "Nom : ");
    const string adresse = lireTexte("Adresse : ");
    const string telephone = lireTexte("Telephone : ");
    shared_ptr<Client> client;

    if (type == 1) {
        const string prenom = lireTexte("Prenom : ");
        const string cin = lireTexte("Numero CIN : ");
        client.reset(new Particulier(identifiant, nom, prenom, cin,
                                     adresse, telephone));
    } else if (type == 2) {
        const string matricule = lireTexte("Matricule fiscal : ");
        const string contact = lireTexte("Nom du contact : ");
        client.reset(new Entreprise(identifiant, nom, matricule, contact,
                                    adresse, telephone));
    } else {
        const string matricule = lireTexte("Matricule de l'association : ");
        const string objet = lireTexte("Objet de l'association : ");
        client.reset(new Association(identifiant, nom, matricule, objet,
                                     adresse, telephone));
    }

    if (banque.ajouterClient(client)) {
        cout << "Client ajoute avec succes." << endl;
    } else {
        cout << "Echec : identifiant deja utilise ou coordonnees obligatoires manquantes." << endl;
    }
}

void modifierClient(Banque& banque) {
    const string identifiant = lireTexte("Identifiant du client a modifier : ");
    const shared_ptr<Client> client = banque.trouverClient(identifiant);
    if (!client) {
        cout << "Client introuvable." << endl;
        return;
    }

    client->afficher();
    string valeur = lireModification("Nom / raison sociale");
    if (!valeur.empty()) client->setNom(valeur);
    valeur = lireModification("Adresse");
    if (!valeur.empty()) client->setAdresse(valeur);
    valeur = lireModification("Telephone");
    if (!valeur.empty()) client->setTelephone(valeur);

    Particulier* particulier = dynamic_cast<Particulier*>(client.get());
    Entreprise* entreprise = dynamic_cast<Entreprise*>(client.get());
    Association* association = dynamic_cast<Association*>(client.get());
    if (particulier) {
        valeur = lireModification("Prenom");
        if (!valeur.empty()) particulier->setPrenom(valeur);
        valeur = lireModification("CIN");
        if (!valeur.empty()) particulier->setCin(valeur);
    } else if (entreprise) {
        valeur = lireModification("Matricule fiscal");
        if (!valeur.empty()) entreprise->setMatriculeFiscal(valeur);
        valeur = lireModification("Contact");
        if (!valeur.empty()) entreprise->setContact(valeur);
    } else if (association) {
        valeur = lireModification("Matricule");
        if (!valeur.empty()) association->setMatricule(valeur);
        valeur = lireModification("Objet");
        if (!valeur.empty()) association->setObjet(valeur);
    }
    cout << "Coordonnees modifiees." << endl;
}

void ouvrirCompte(Banque& banque) {
    if (banque.getClients().empty()) {
        cout << "Ajoutez d'abord un client." << endl;
        return;
    }
    banque.afficherClients();
    const string identifiant = lireTexte("Identifiant du proprietaire : ");
    const shared_ptr<Client> client = banque.trouverClient(identifiant);
    if (!client) {
        cout << "Client introuvable." << endl;
        return;
    }
    client->afficher();
    cout << "Conseil : " << client->getConseilCompte() << endl;

    cout << "Type de compte : 1. Courant  2. Epargne" << endl;
    const int type = lireEntier("Votre choix : ");
    const string rib = lireTexte("RIB / numero de compte unique : ");
    const double solde = lireMontant("Solde initial : ");
    bool resultat = false;
    if (type == 1) {
        const double seuil = lireMontant(
            "Solde minimum autorise (exemple -500, sans decouvert : 0) : ");
        resultat = banque.ouvrirCompteCourant(rib, identifiant, solde, seuil);
    } else if (type == 2) {
        const double taux = lireMontant("Taux d'interet annuel en % : ");
        resultat = banque.ouvrirCompteEpargne(rib, identifiant, solde, taux);
    } else {
        cout << "Type de compte invalide." << endl;
        return;
    }

    cout << (resultat ? "Compte ouvert avec succes."
                      : "Echec : verifiez le RIB, le solde et les parametres.")
         << endl;
}

void gererCompte(Banque& banque) {
    const string rib = lireTexte("RIB du compte a gerer : ");
    const shared_ptr<Compte> compte = banque.trouverCompte(rib);
    if (!compte) {
        cout << "Compte introuvable." << endl;
        return;
    }

    int choix;
    do {
        cout << "\nCompte " << compte->getRib() << " | Proprietaire : "
             << compte->getClient().getNom() << endl;
        cout << "1. Afficher les informations" << endl;
        cout << "2. Crediter" << endl;
        cout << "3. Retirer" << endl;
        cout << "4. Transferer vers un autre compte" << endl;
        if (dynamic_cast<CompteEpargne*>(compte.get())) {
            cout << "5. Calculer l'interet annuel" << endl;
        }
        cout << "0. Retour" << endl;
        choix = lireEntier("Votre choix : ");

        switch (choix) {
            case 1:
                compte->afficher();
                break;
            case 2:
                compte->deposer(lireMontant("Montant a crediter : "));
                break;
            case 3:
                compte->retirer(lireMontant("Montant a retirer : "));
                break;
            case 4: {
                const string destination = lireTexte("RIB du compte destinataire : ");
                const double montant = lireMontant("Montant a transferer : ");
                if (!banque.transferer(rib, destination, montant)) {
                    cout << "Transfert impossible. Verifiez les comptes et les soldes." << endl;
                }
                break;
            }
            case 5: {
                CompteEpargne* epargne = dynamic_cast<CompteEpargne*>(compte.get());
                if (epargne) {
                    cout << "Interet annuel estime : "
                         << epargne->calculerInteret() << " DT" << endl;
                } else {
                    cout << "Choix invalide." << endl;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Choix invalide." << endl;
        }
    } while (choix != 0);
}

int main() {
    Banque banque("Banque de demonstration");
    int choix;
    do {
        cout << "\n========== " << banque.getNom() << " ==========" << endl;
        cout << "1. Ajouter un client" << endl;
        cout << "2. Afficher tous les clients" << endl;
        cout << "3. Modifier les coordonnees d'un client" << endl;
        cout << "4. Ouvrir un compte" << endl;
        cout << "5. Afficher tous les comptes" << endl;
        cout << "6. Consulter le dossier d'un client (profil et comptes)" << endl;
        cout << "7. Gerer un compte" << endl;
        cout << "0. Quitter" << endl;
        choix = lireEntier("Votre choix : ");

        switch (choix) {
            case 1:
                creerClient(banque);
                break;
            case 2:
                banque.afficherClients();
                break;
            case 3:
                modifierClient(banque);
                break;
            case 4:
                ouvrirCompte(banque);
                break;
            case 5:
                banque.afficherComptes();
                break;
            case 6:
                banque.afficherDossierClient(
                    lireTexte("Identifiant du client : "));
                break;
            case 7:
                gererCompte(banque);
                break;
            case 0:
                cout << "Au revoir." << endl;
                break;
            default:
                cout << "Choix invalide." << endl;
        }
    } while (choix != 0);

    return 0;
}
