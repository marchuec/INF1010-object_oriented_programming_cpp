#ifndef GESTIONNAIREMEDECIN_H
#define GESTIONNAIREMEDECIN_H

#include <memory>
#include "Medecin.h"
#include "GestionnairePatients.h"


class GestionnaireMedecins
{
public:
    GestionnaireMedecins();

    //TODO : signature de constructeur de copie
    GestionnaireMedecins(const GestionnaireMedecins& gestionnaireMedecins);

    //TODO : signature d'operateur d'affectation
    GestionnaireMedecins& operator=(const GestionnaireMedecins& gestionnaireMedecins);

    Medecin* chercherMedecin(const std::string& numeroLicence);
    bool chargerDepuisFichier(const std::string& nomFichiers);

    // opérateur<< qui remplace afficher
    friend std::ostream& operator<<(std::ostream& stream, const GestionnaireMedecins& gestionnaireMedecins);
    // opérateur+= qui remplace ajouterMedecin
    bool operator+=(const Medecin& medecin);
    // opérateur-= qui remplace supprimerMedecin
    bool operator-=(const std::string& numeroLicence);

    size_t getNbMedecins() const;
    size_t getCapaciteMedecins() const;

    // TODO : signature de getMedecins() retourne une reference constante vers le vecteur medecins_
    const std::vector<std::shared_ptr<Medecin>>& getMedecins() const;

private:
    bool lireLigneMedecin(const std::string& ligne);
    int trouverIndexMedecin(const std::string& numeroLicence);

    // TODO: remplacer le tableau par un vecteur de shared_ptr de medecin
    std::vector<std::shared_ptr<Medecin>> medecins_;
};

#endif // GESTIONNAIREMEDECIN_H