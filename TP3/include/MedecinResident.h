#ifndef MEDECINRESIDENT_H
#define MEDECINRESIDENT_H

#include <string>
#include "Medecin.h"
#include "Etudiant.h"

class MedecinResident : public Medecin, public Etudiant
{
public:
    MedecinResident(const std::string& nom, const std::string& dateDeNaissance, const std::string& id, 
                    const std::string& etablissement, const std::string& matricule, 
                    Specialite specialite);

    void afficher(std::ostream& stream) const override;

    double getSalaireAnnuel() const override;
    
    static constexpr size_t SALAIRE_DE_BASE_MEDECIN_RESIDENT = 50000;
};

#endif // MEDECINRESIDENT_H