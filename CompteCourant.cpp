#include "CompteCourant.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

CompteCourant::CompteCourant(const string& rib, const shared_ptr<Client>& client,
                             double solde, double seuilMin)
        : Compte(rib, client, solde),
            seuilMin(isfinite(seuilMin) && seuilMin <= 0.0 ? seuilMin : 0.0) {
        if (!isfinite(seuilMin) || seuilMin > 0.0) {
                throw invalid_argument("Le seuil minimum doit etre inferieur ou egal a zero.");
        }
}

double CompteCourant::getSeuilMin() const { return seuilMin; }

bool CompteCourant::retirer(double montant) {
    if (!isfinite(montant) || montant <= 0) {
        cout << "Montant invalide." << endl;
        return false;
    }
    if (solde - montant < seuilMin) {
        cout << "Retrait refuse : le solde ne peut pas descendre en dessous de "
             << seuilMin << " DT." << endl;
        return false;
    } else {
        solde -= montant;
        cout << "Retrait de " << montant << " DT effectue. Nouveau solde : " << solde << " DT" << endl;
        return true;
    }
}

void CompteCourant::afficher() const {
    cout << "--- Compte Courant ---" << endl;
    Compte::afficher();
    cout << "Seuil minimum  : " << seuilMin << " DT" << endl;
}
