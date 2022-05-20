#ifndef HOPITAL_H
#define HOPITAL_H

#include <string>
#include <vector>

#include "Consultation.h"
#include "GestionnaireMedecins.h"
#include "GestionnairePatients.h"

class Hopital
{
public:
    Hopital() = default;
    Hopital(const std::string& nom, const std::string& adresse);

    bool chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients);
    
    // opérateur+= qui ajoute une instance de Consultation
    bool operator+=(const Consultation& consultation);
    // opérateur+= qui ajoute une instance de Medecin
    bool operator+=(const Medecin& medecin);
    // opérateur+= qui ajoute une instance de Patient
    bool operator+=(const Patient& patient);


    const std::string& getNom() const;
    const std::string& getAdresse() const;
    GestionnaireMedecins& getGestionnaireMedecins();
    GestionnairePatients& getGestionnairePatients();

    // TODO : la signature de getConsultations()
    const std::vector<std::shared_ptr<Consultation>>& getConsultations() const;


    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);

private:
    std::string nom_;
    std::string adresse_;

    GestionnaireMedecins gestionnaireMedecins_;
    GestionnairePatients gestionnairePatients_;

    //TODO : vecteur de shared_ptr de Consultation consultations_
    std::vector<std::shared_ptr<Consultation>> consultations_;

};

#endif // HOPITAL_H