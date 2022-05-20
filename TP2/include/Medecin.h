#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include "Patient.h"
#include <vector>


class Medecin
{
public:
    enum class Specialite
    {
        first_ = -1,
        Generaliste,
        Cardiologue,
        Dermatologue,
        Gynecologue,
        Pediatre,
        Ophtalmologue,
        Autre,
        last_
    };

    Medecin() = default;
    Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite);

    // opérateur<< qui remplace afficher
    friend std::ostream& operator<<(std::ostream& stream, const Medecin& medecin);

    
    // opérateur+= qui remplace ajouterPatient
    bool operator+=(Patient& patient);
    // opérateur-= qui remplace supprimerPatient
    bool operator-=(const std::string& numeroAssuranceMaladie);
    // opérateur== qui compare un string avec le numéro licence du médecin
    bool operator==(const std::string& numeroLicence) const;
    // opérateur== qui compare un string avec le numéro licence du médecin
    friend bool operator==(const std::string& numeroLicence, const Medecin& medecin);
    
    Patient* chercherPatient(const std::string& numeroAssuranceMaladie) const;

    const std::string& getNom() const;
    const std::string& getNumeroLicence() const;
    bool getEstActif() const;
    const Specialite getSpecialite() const;
    const size_t getCapacitePatientAssocies() const;
    const size_t getNombrePatientsAssocies() const;
    const std::vector<Patient*>& getPatientsAssocies() const;

    void setNom(const std::string& nom);
    void setNumeroLicence(const std::string& numeroLicence);
    void setEstActif(bool estActif);
    void setSpecialite(Specialite specialite);

private:
    // Attributs
    std::string nom_;
    std::string numeroLicence_;
    Specialite specialite_;
    bool estActif_ = true;

    // TODO: remplacer le tableau par un vecteur de Patient*
    std::vector<Patient*> patientsAssocies_;
};

#endif // MEDECIN_H