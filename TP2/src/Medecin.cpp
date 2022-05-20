/****************************************************************
* \class  Medecin
* \brief  Contient l'information du medecin.
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   22/07/2020
****************************************************************/

#include <iostream>
#include "Medecin.h"
#include "typesafe_enum.h"

constexpr std::size_t CAPACITE_PATIENTS_INITIALE = 2;

//! Constructeur par paramètre  de la classe Medecin
//! \param nom              Nom du medecin
//! \param numeroLicence    Numero de licence du medecin
//! \param specialite       Specialite du medecin
//! \param patientsAssocies Patients associés au médecin
Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite)
	: nom_(nom)
	, numeroLicence_(numeroLicence)
	, specialite_(specialite)
	, patientsAssocies_(std::vector<Patient*>()) 
{
}


// Methode ajouterPatient doit être remplacée par l'operateur +=. il prend en paramètre le patient à ajouter
//! Opérateur qui ajoute un patient au médecin
//! \param patient Le patient à ajouter
//! \return Retourne true si l'opération d'ajout est réussi, false sinon.
bool Medecin::operator+=(Patient& patient)
{
	// Vérifier si le patient est déjà associé (les num. d'assurance maladie sont uniques)
	if (chercherPatient(patient.getNumeroAssuranceMaladie()) == nullptr)
	{
		patientsAssocies_.push_back(&patient);
		return true;
	}
	else 
	{
		return false;
	}
}


//! Méthode qui supprime un patient du médecin
//! \param  numeroAssuranceMaladie Le num. d'assurance maladie du patient
//! \return bool 				   Retourne true si l'opération d'ajout est réussi, false si non.
bool Medecin::operator-=(const std::string& numeroAssuranceMaladie)
{
	for (int i = 0; i < patientsAssocies_.size(); i++) 
	{
		if (patientsAssocies_[i]->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			patientsAssocies_[i] = patientsAssocies_[patientsAssocies_.size() - 1];
			patientsAssocies_.pop_back();

			return true;
		}
	}
	return false;
}

// TODO : La methode afficher doit être remplacée par l’opérateur << 
//! Opérateur qui transmet les informations du medecin dans un stream
//! \param stream dans lequel on ecrit les informations du medecin
std::ostream& operator<<(std::ostream& stream, const Medecin& medecin)
{
	static const std::string SPECIALITES[] = { "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre" };
	auto index = enum_value(medecin.specialite_);
	assert(valid_as_enum<Medecin::Specialite>(index));
	std::string specialite = SPECIALITES[index];

	std::string statut = medecin.estActif_ ? "Actif" : "Inactif";

	stream << "\nMedecin: " << medecin.nom_
		<< "\n\tNumero de licence: " << medecin.numeroLicence_
		<< "\n\tSpecialite: " << specialite
		<< "\n\tStatut: " << statut
		<< (medecin.patientsAssocies_.size() == 0 ? "\n\tAucun patient n'est suivi par ce medecin.\n" : "\n\tPatients associes:");

	for (int i = 0; i < medecin.patientsAssocies_.size(); i++)
	{
		stream << "\n\t\t"
			   << *medecin.patientsAssocies_[i];
	}
	return stream;
}

//! Opérateur qui compare un string avec le numéro de la licence du médecin, avec médecin comme opérande de gauche
//! \param  numeroLicence le numéro de licence du médecin
//! \return bool  		  True si les deux string concordent
bool Medecin::operator==(const std::string& numeroLicence) const
{
	return (numeroLicence_ == numeroLicence);
}

//! Opérateur ==  qui compare le numéro de la licence du médecin avec un le numéro de la licence. Le numéro de licence comme opérande de gauche.
//! \param  numeroLicence le numéro de licence avec lequel comparer
//! \param  medecin 	  le médecin d'intérêt
//! \return bool 		  True si les deux string concordent
bool operator==(const std::string& numeroLicence, const Medecin& medecin)
{
	return (numeroLicence == medecin.numeroLicence_);
}

//! Fonction qui cherche un patient et retourne un pointeur vers le patient
//! \param numeroAssuranceMaladie Le numéro d'assurance maladie du patient
//! \return Patient*			  Le pointeur vers le patient ou nullptr si pas trouvé
Patient* Medecin::chercherPatient(const std::string& numeroAssuranceMaladie) const
{
	for (int i = 0; i < patientsAssocies_.size(); i++) 
	{
		if (patientsAssocies_[i]->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			return patientsAssocies_[i];
		}
	}
	return nullptr;
}

//! Méthode qui retourne le nom du medecin
//! \return le nom du medecin 
const std::string& Medecin::getNom() const
{

	return nom_;
}

//! Méthode qui retourne le numero de licence du medecin
//! \return le numero de licence
const std::string& Medecin::getNumeroLicence() const
{

	return numeroLicence_;
}

//! Méthode qui retourne le status du medecin
//! \return le status du medecin
bool Medecin::getEstActif() const
{

	return estActif_;
}

//! Méthode qui retourne la specialite du medecin
//! \return la specialite des medecins
const Medecin::Specialite Medecin::getSpecialite() const
{

	return specialite_;
}

//! Méthode qui retourne le nombre de patients associés au  médecin
//! \return le nombre patient associes
const size_t Medecin::getNombrePatientsAssocies() const
{

	return patientsAssocies_.size();
}

//! Méthode qui retourne la capacité du tableau patientsAssocies_
//! \return la capacité du tableau patientsAssocies_
const size_t Medecin::getCapacitePatientAssocies() const
{
	return patientsAssocies_.capacity();
}

//! Méthode qui retourne la liste des patients associes au medecin
//! \return la liste des patients
const std::vector<Patient*>& Medecin::getPatientsAssocies() const
{
	return patientsAssocies_;
}

//! Méthode qui met a jours le nom  du medecin
//! \pararm  nom  Le nom du médecin
void Medecin::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui met a jours le numero de licence du medecin
//! \pararm  numeroLicence  le numero de licence du medecin
void Medecin::setNumeroLicence(const std::string& numeroLicence)
{
	numeroLicence_ = numeroLicence;
}

//! Méthode qui met a jours le statut du medecin si il est actif ou non
//! \pararm  boolean indiquant le  nouveau status du medecin
void Medecin::setEstActif(bool estActif)
{
	estActif_ = estActif;
}

//! Méthode qui met a jours la specialité du medecin
//! \pararm  specialite  specialité du medecin
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}
