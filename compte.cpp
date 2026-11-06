#include "compte.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

Compte::Compte(const string& rib, const shared_ptr<Client>& client, double solde)
    : rib(rib), solde(isfinite(solde) && solde > 0.0 ? solde : 0.0), client(client) {
    if (!client) {
        throw invalid_argument("Un compte doit etre associe a un client.");
    }
}

Compte::~Compte() {}

const string& Compte::getRib() const { return rib; }
double Compte::getSolde() const { return solde; }
const Client& Compte::getClient() const { return *client; }
const shared_ptr<Client>& Compte::getClientPtr() const { return client; }

bool Compte::deposer(double montant) {
    if (!isfinite(montant) || montant <= 0 || !isfinite(solde + montant)) {
        cout << "Montant invalide." << endl;
        return false;
    }
    solde += montant;
    cout << "Depot de " << montant << " DT effectue. Nouveau solde : " << solde << " DT" << endl;
    return true;
}

bool Compte::retirer(double montant) {
    if (!isfinite(montant) || montant <= 0) {
        cout << "Montant invalide." << endl;
        return false;
    }
    if (montant > solde) {
        cout << "Retrait refuse : solde insuffisant." << endl;
        return false;
    }
    solde -= montant;
    cout << "Retrait de " << montant << " DT effectue. Nouveau solde : " << solde << " DT" << endl;
    return true;
}

bool Compte::transfererVers(Compte& destinataire, double montant) {
    if (&destinataire == this) {
        cout << "Transfert refuse : les comptes doivent etre differents." << endl;
        return false;
    }
    if (retirer(montant)) {
        if (!destinataire.deposer(montant)) {
            deposer(montant);
            return false;
        }
        cout << "Transfert vers le compte " << destinataire.getRib()
             << " effectue." << endl;
        return true;
    }
    return false;
}

void Compte::afficher() const {
    cout << "RIB    : " << rib << endl;
    client->afficher();
    cout << "Solde  : " << solde << " DT" << endl;
}
