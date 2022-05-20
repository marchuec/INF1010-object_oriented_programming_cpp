#ifndef PATIENTETUDIAT_H
#define PATIENTETUDIAT_H

#include "Patient.h"
#include "Etudiant.h"

class PatientEtudiant : public Patient, 
						public Etudiant
{
public:
	PatientEtudiant() = default;
	PatientEtudiant(const std::string& nom, const std::string dateDeNaissance, 
                    const std::string numeroAssuranceMaladie, const std::string& matricule, 
                	const std::string& etablissement);

	void afficher(std::ostream& stream) const override;

	const std::string& getNom() const;
	const std::string& getDateDeNaissance() const;
	const double getTauxRabais() const;		// Pourquoi retourner const double
	void setNom(const std::string& nom);
	void setDateDeNaissance(const std::string& dateDeNaissance);
	void setTauxRabais(const double tauxRabais);

	const double TAUX_RABAIS = 0.2;

private:
	double tauxRabais_;
};

#endif // PATIENTETUDIAT_H