/****************************************************************
* \class  Medecin
* \brief  Contient l'information sur un médecin
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include <iostream>
#include "../include/Medecin.h"
#include "../include/typesafe_enum.h"


constexpr int PATIENT_INEXSISTANT = -1;

//! Constructeur par paramètre de la classe héritée Medecin
//! \param nom 		 Le nom du médecin
//! \param id  		 L'identifiant du médecin
//! \param specliate La spécialité du médecin
Medecin::Medecin(const std::string& nom, const std::string& id, Specialite specialite)
	: Personnel::Personnel(nom, id), specialite_(specialite)
{
}

//! Operateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return Un bool qui indique si l'opération a bien fonctionnée
bool Medecin::operator+=(Patient* patient)
{
	if (patient && !chercherPatient(patient->getNumeroAssuranceMaladie())) {
		patientsAssocies_.push_back(patient);

		return true;
	}

	return false;
}

//! Operateur qui supprime un patient de la liste des patients
//! \param numeroAssuranceMaladiePatient Le num. d'assurance maladie du patient à ajouter
//! \return un bool qui indique si l'opération a bien fonctionnée
bool Medecin::operator-=(const std::string& numeroAssuranceMaladiePatient)
{
	int indexPatient = trouverIndexPatient(numeroAssuranceMaladiePatient);
	if (indexPatient == PATIENT_INEXSISTANT)
	{
		return false;
	}

	patientsAssocies_.erase(patientsAssocies_.begin() + indexPatient);

	return true;
}


//! Méthode qui affiche les informations du médecin
//! \param stream Le stream dans lequel afficher
void Medecin::afficher(std::ostream& stream) const
{
	static const std::string SPECIALITES[] = { "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre" };
	auto index = enum_value(specialite_);
	assert(valid_as_enum<Medecin::Specialite>(index));
	std::string specialite = SPECIALITES[index];

	// Afficher les informations du médecin
	Personnel::afficher(stream);

	stream << "\n\tSpecialite: " << specialite
		<< (patientsAssocies_.empty() ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");

	// Afficher les information des patients
	for (const auto& patient : patientsAssocies_)
	{
		stream << "\n\t\t";
		patient->afficher(stream);
	}
}

//! Méhode qui cherche un patient par numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* Medecin::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (auto& patientsAssocie : patientsAssocies_)
	{
		if (*patientsAssocie == numeroAssuranceMaladie)
		{
			return patientsAssocie;
		}
	}

	return nullptr;
}

//! Méthode qui permet d'incrémenter le nombre de consultations
void Medecin::incrementNombreConsultations()
{
	nombreConsultations_++;
}


//! Méthode qui retourne le salaire annuel du médecin
//! \return le salaire annuel du médecin
double Medecin::getSalaireAnnuel() const
{
	return SALAIRE_DE_BASE_MEDECIN + nombreConsultations_ * getPrixConsultation();
}

//! Méthode qui retourne le prix de la consultation qui dépend de la spécialité du médecin.
//! \param specialite La spécialité du médecin
//prix = 100 pour Gynecologue et Ophtalmologue
//prix = 120 pour Cardiologue et Dermatologue
//prix = 80 pour Pediatre
//prix = 60 pour Generaliste ou Autre
//default : throw "La spécialite du médecin n'est pas définie"
double Medecin::getPrixConsultation() const
{
	switch (specialite_)
	{
		case Specialite::Gynecologue: case Specialite::Ophtalmologue: return 100;
		case Specialite::Cardiologue: case Specialite::Dermatologue:  return 120;
		case Specialite::Pediatre: 					 	  			  return 80;
		case Specialite::Generaliste: case Specialite::Autre: 		  return 60;
		default: throw "La spécialite du médecin n'est pas définie";
	}
}


//! Méthode qui retourne la specialite du medecin
//! \return la specialite des medecins
const Medecin::Specialite Medecin::getSpecialite() const
{
	return specialite_;
}

//! Méthode qui retourne le nombre de patients associés
//! \return le nombre de patients associés
const size_t Medecin::getNombrePatientsAssocies() const
{
	return patientsAssocies_.size();
}

//! Méthode qui retourne la liste des patients associés au médecin
//! \return la liste des patients
const std::vector<Patient*>& Medecin::getPatientsAssocies() const
{
	return patientsAssocies_;
}

//! Méthode qui met à jour la spécialité du médecin
//! \param specialite specialité du medecin
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}


//! Méthode qui permet de trouver l'index un médecin dans la liste des médecins
//! \param numeroLicence numero de licence du médecin
//! \return int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le médecin est inexistant
int Medecin::trouverIndexPatient(const std::string& numeroAssuranceMaladie)
{
	for (std::size_t i = 0; i < patientsAssocies_.size(); i++)
	{
		if (*patientsAssocies_[i] == numeroAssuranceMaladie)
		{
			return static_cast<int>(i);
		}
	}
	return PATIENT_INEXSISTANT;
}

//! Méthode qui retourne le nombre de consultations
//! \return Le nombre de consultations
const size_t Medecin::getNombreConsultations() const
{
	return nombreConsultations_;
}
