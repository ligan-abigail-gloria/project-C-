#include "CompteEpargne.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

const double CompteEpargne::SOLDE_MIN = 5.0;

CompteEpargne::CompteEpargne(const string& rib, const shared_ptr<Client>& client,
                             double solde, double tauxInteret)
    : Compte(rib, client, solde), tauxInteret(tauxInteret) {
    if (!isfinite(tauxInteret) || tauxInteret < 0.0) {
        throw invalid_argument("Le taux d'interet doit etre positif ou nul.");
    }
    if (solde < SOLDE_MIN) {
        cout << "Attention : le solde initial doit etre >= " << SOLDE_MIN
             << " DT. Solde fixe a " << SOLDE_MIN << " DT." << endl;
        this->solde = SOLDE_MIN;
    }
}

double CompteEpargne::getTaux() const { return tauxInteret; }

double CompteEpargne::calculerInteret() const {
    return solde * tauxInteret / 100.0;
}

bool CompteEpargne::retirer(double montant) {
    if (!isfinite(montant) || montant <= 0) {
        cout << "Montant invalide." << endl;
        return false;
    }
    if (solde - montant < SOLDE_MIN) {
        cout << "Retrait refuse : le solde ne peut pas descendre en dessous de "
             << SOLDE_MIN << " DT." << endl;
        return false;
    } else {
        solde -= montant;
        cout << "Retrait de " << montant << " DT effectue. Nouveau solde : " << solde << " DT" << endl;
        return true;
    }
}

void CompteEpargne::afficher() const {
    cout << "--- Compte Epargne ---" << endl;
    Compte::afficher();
    cout << "Taux d'interet : " << tauxInteret << "%" << endl;
    cout << "Interet annuel : " << calculerInteret() << " DT" << endl;
    cout << "Solde minimum  : " << SOLDE_MIN << " DT" << endl;
}
