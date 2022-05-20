#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include "Patient.h"
#include <vector>
#include "Personnel.h"

class Medecin : public Personnel
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
    Medecin(const std::string& nom, const std::string& id, Specialite specialite);

    bool operator+=(Patient* patient);
    bool operator-=(const std::string& numeroAssuranceMaladiePatient);

    void afficher(std::ostream& stream) const override;

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    void incrementNombreConsultations();

    double getSalaireAnnuel() const override;
    double getPrixConsultation() const;
    const Specialite getSpecialite() const;
    const size_t getNombrePatientsAssocies() const;
    const std::vector<Patient*>& getPatientsAssocies() const;
    const size_t getNombreConsultations() const;
    
    void setSpecialite(Specialite specialite);

    static constexpr size_t SALAIRE_DE_BASE_MEDECIN = 100000;

protected:
    Specialite specialite_;
    std::vector<Patient*> patientsAssocies_;
    size_t nombreConsultations_;

private:
    int trouverIndexPatient(const std::string& numeroAssuranceMaladie);
};

#endif // MEDECIN_H