#ifndef GESTIONNAIREPATIENTS_H
#define GESTIONNAIREPATIENTS_H

#include <string>
#include "Patient.h"
#include <memory>
#include <vector>

class GestionnairePatients
{
public:
    GestionnairePatients();
    GestionnairePatients(const GestionnairePatients& gestionnairePatients);

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);

    GestionnairePatients& operator=(const GestionnairePatients& gestionnairePatients);
    
    // opérateur<< qui remplace afficher
    friend std::ostream& operator<<(std::ostream& stream, const GestionnairePatients& gestionnairePatients);

    // opérateur+= qui remplace ajouterPatient
    bool operator+=(const Patient& patient);

    size_t getNbPatients() const;

    // TODO : signature de getPatients()  retourne une reference constante vers le vecteur patients_
    std::vector<std::shared_ptr<Patient>>& getPatients();

    static constexpr size_t NB_PATIENT_MAX = 16;

private:
    bool lireLignePatient(const std::string& ligne);

    //TODO : remplacer le tableau par un vecteur de shared_ptr de Patient
   std::vector<std::shared_ptr<Patient>> patients_;
};

#endif // GESTIONNAIREPATIENTS_H