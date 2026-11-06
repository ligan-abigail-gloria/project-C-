#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private:
    std::string identifiant;
    std::string nom;
    std::string adresse;
    std::string telephone;

public:
    Client(const std::string& identifiant, const std::string& nom,
           const std::string& adresse, const std::string& telephone);
    virtual ~Client();

    const std::string& getIdentifiant() const;
    const std::string& getNom() const;
    const std::string& getAdresse() const;
    const std::string& getTelephone() const;
    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);
    void setTelephone(const std::string& telephone);

    virtual std::string getType() const = 0;
    virtual std::string getConseilCompte() const = 0;
    virtual void afficher() const;
};

class Particulier : public Client {
private:
    std::string prenom;
    std::string cin;

public:
    Particulier(const std::string& identifiant, const std::string& nom,
                const std::string& prenom, const std::string& cin,
                const std::string& adresse, const std::string& telephone);

    const std::string& getPrenom() const;
    const std::string& getCin() const;
    void setPrenom(const std::string& prenom);
    void setCin(const std::string& cin);
    std::string getType() const override;
    std::string getConseilCompte() const override;
    void afficher() const override;
};

class Entreprise : public Client {
private:
    std::string matriculeFiscal;
    std::string contact;

public:
    Entreprise(const std::string& identifiant, const std::string& raisonSociale,
               const std::string& matriculeFiscal, const std::string& contact,
               const std::string& adresse, const std::string& telephone);

    const std::string& getMatriculeFiscal() const;
    const std::string& getContact() const;
    void setMatriculeFiscal(const std::string& matriculeFiscal);
    void setContact(const std::string& contact);
    std::string getType() const override;
    std::string getConseilCompte() const override;
    void afficher() const override;
};

class Association : public Client {
private:
    std::string matricule;
    std::string objet;

public:
    Association(const std::string& identifiant, const std::string& nom,
                const std::string& matricule, const std::string& objet,
                const std::string& adresse, const std::string& telephone);

    const std::string& getMatricule() const;
    const std::string& getObjet() const;
    void setMatricule(const std::string& matricule);
    void setObjet(const std::string& objet);
    std::string getType() const override;
    std::string getConseilCompte() const override;
    void afficher() const override;
};

#endif