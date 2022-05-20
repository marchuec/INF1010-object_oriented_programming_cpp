/****************************************************************
* Classe: 		Médecin
* Description:  Contient les informations sur le médecin
*
* Auteurs: 		Marc-Antoine Huet et François Dubois-Roy
* Date: 		17/07/2020
****************************************************************/

#include "Medecin.h"
#include <iostream>
#include "typesafe_enum.h"

constexpr std::size_t CAPACITE_PATIENTS_INITIALE = 2;


/**
 * Fonction: 	Constructeur par paramètres
 * Paramètre:	(nom) Le nom du médecin
 * 				(numeroLicence) Le num. de licence du médecin
 * 				(specialite) La spécialité du médecin
**/
Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite)
    : nom_(nom), numeroLicence_(numeroLicence), specialite_(specialite), capacitePatientsAssocies_(CAPACITE_PATIENTS_INITIALE),
	 patientsAssocies_(std::make_unique<std::shared_ptr<Patient>[]>(capacitePatientsAssocies_)) {};



// Utilisez CAPACIT_PATIENTS_INITIALE pour la taille initiale de patientsAssocies_ (tableau de taille dynamique)


/**
 * Fonction: 	Medecin::ajouterPatient
 * Description: Ajoute un patient à la liste des patients associés au médecin
 * Paramètre:	(patient) Le patient à ajouter
**/
void Medecin::ajouterPatient(Patient patient) {
	static constexpr unsigned int AUGMENTATION_NOMBRE_PATIENTS = 2;
	// TODO
	// Verifier si assez de mémoire est allouée
	// Si pas assez de mémoire, doubler la taille du tableau (AUGMENTATION_NOMBRE_PATIENTS)
	// Ajouter le patient au tableau
	// Utiliser std::unique_ptr<std::shared_ptr<Patient>[]> ainsi que std::move pour transférer le ownership
	// du tableau temporaire vers le tableau membre patientsAssocies_;

	// Double la taille du tableau si nécessaire
	if (nbPatientsAssocies_ == capacitePatientsAssocies_) {
		capacitePatientsAssocies_ *= AUGMENTATION_NOMBRE_PATIENTS;
		auto tableauTemp = std::make_unique<std::shared_ptr<Patient>[]>(capacitePatientsAssocies_);
		for (int i = 0; i <= (nbPatientsAssocies_ - 1); i++)
		{
			tableauTemp[i] = std::move(patientsAssocies_[i]);
		}
		patientsAssocies_ = std::move(tableauTemp);
	}

	// Ajoute le patient
	nbPatientsAssocies_++;
	auto ptrPatient = std::make_shared<Patient>(patient);
	patientsAssocies_[nbPatientsAssocies_ - 1] = ptrPatient;
}


/**
 * Fonction: 	Medecin::supprimerPatient
 * Description: Supprime un patient du médecin
 * Paramètre:	(numeroAssuranceMaladie) Le num. d'assurance maladie du patient
 * Retour:		(bool) Retourne true si la supression a réussit
**/
bool Medecin::supprimerPatient(const std::string& numeroAssuranceMaladie)
{
	for (size_t i = 0; i < nbPatientsAssocies_; i++)
	{
		if (patientsAssocies_[i]->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			patientsAssocies_[i].reset();

			for (size_t j = i; j < nbPatientsAssocies_ - 1; j++)
			{
				patientsAssocies_[j] = patientsAssocies_[j + 1];
			}

			patientsAssocies_[nbPatientsAssocies_ - 1] = nullptr;
			nbPatientsAssocies_--;

			return true;
		}
	}

	return false;
}

/**
 * Fonction: 	Medecin::afficher
 * Description: Affiche les informations du médecin
 * Paramètre:	(stream) dans lequel on écrit les informations du médecin
**/
void Medecin::afficher(std::ostream& stream) const {
	static const std::string SPECIALITES[] = {  "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre"};
	auto index = enum_value(specialite_);
	assert(valid_as_enum<Specialite>(index));
	std::string specialite = SPECIALITES[index];

	std::string statut = estActif_ ? "Actif" : "Inactif";

    stream << "\nMedecin: " << nom_
       << "\n\tNumero de licence: " << numeroLicence_ 
	   << "\n\tSpecialite: " << specialite
	   << "\n\tStatut: " << statut
	   << (nbPatientsAssocies_ == 0 ? "\n\tAucun patient n'est suivi par ce medecin.\n" : "\n\tPatients associes:\n");

	// Patients associées au médecin
	if (nbPatientsAssocies_ != 0) {
		for (int i = 0; i <= (nbPatientsAssocies_ - 1); i++)
    	{
			stream << "\t\tPatient: " << patientsAssocies_[i]->getNom() << " | " 
			   	<< "Date de naissance: " << patientsAssocies_[i]->getDateDeNaissance() << " | "
		       	<< "Numero d'assurance maladie: " << patientsAssocies_[i]->getNumeroAssuranceMaladie() << "\n";
		}
	}
}


/**
 * Fonction: 	Medecin::getNom
 * Description: Retourne le nom du médecin
 * Retour:		(nom_) Le nom du médecin
**/
const std::string& Medecin::getNom() const {
	return nom_;
}


/**
 * Fonction: 	Medecin::getNumeroLicence
 * Description: Retourne le numéro de licence du médecin
 * Retour:		(numeroLicence_) Le num. de licence du médecin
**/
const std::string& Medecin::getNumeroLicence() const {
	return numeroLicence_;
}


/**
 * Fonction: 	Medecin::getEstActif
 * Description: Retourne l'état du médecin
 * Retour:		(estActif_) L'état du médecin
**/
bool Medecin::getEstActif() const {
	return estActif_;
}


/**
 * Fonction: 	Medecin::getSpecialite
 * Description: Retourne la spécialité du médecin
 * Retour:		(specialite_) La spécialité du médecin
**/
const Medecin::Specialite Medecin::getSpecialite() const {
	return specialite_;
}


/**
 * Fonction: 	Medecin::getCapacitePatientAssocies
 * Description: Retourne la capacité de patients du médecin (la taille du tableau)
 * Retour:		(capacitePatientsAssocies_) La capacité de patients du médecin
**/
const size_t Medecin::getCapacitePatientAssocies() const {
	return capacitePatientsAssocies_;
}


/**
 * Fonction: 	Medecin::getNombrePatientsAssocies
 * Description: Retourne le nombre de patients du médecin
 * Retour:		(nbPatientsAssocies_) Le nombre de patients du médecin
**/
const size_t Medecin::getNombrePatientsAssocies() const {
	return nbPatientsAssocies_;
}


/**
 * Fonction: 	Medecin::getPatientsAssocies
 * Description: Retourne les patients du médecin (pointeur vers tableau)
 * Retour:		(patientsAssocies_) Les patients du médecin (pointeur vers tableau)
**/
std::unique_ptr<std::shared_ptr<Patient>[]> Medecin::getPatientsAssocies() const {
	auto patientsAssociesRetour = std::make_unique<std::shared_ptr<Patient>[]>(capacitePatientsAssocies_);
	if (nbPatientsAssocies_ != 0) {
		for (int i = 0; i <= (nbPatientsAssocies_ -1); i++) {
			patientsAssociesRetour[i] = patientsAssocies_[i];
		}
	}
	return patientsAssociesRetour;
}


/**
 * Fonction: 	Medecin::setNom
 * Description: Initialise le nom du médecin
 * Paramètre:	(nom) Le nom du médecin
**/
void Medecin::setNom(const std::string& nom) {
	nom_ = nom;
}


/**
 * Fonction: 	Medecin::setNumeroLicence
 * Description: Initialise le numero de licence du médecin
 * Paramètre:	(numeroLicence) Le num. de licence du médecin
**/
void Medecin::setNumeroLicence(const std::string& numeroLicence) {
	numeroLicence_ = numeroLicence;
}


/**
 * Fonction: 	Medecin::setEstActif
 * Description: Initialise l'état du médecin
 * Paramètre:	(estActif) État du médecin
**/
void Medecin::setEstActif(bool estActif) {
	estActif_ = estActif;
}


/**
 * Fonction: 	Medecin::setSpecialite
 * Description: Initialise la spécialité du médecin
 * Paramètre:	(specialite) La spécialité du médecin
**/
void Medecin::setSpecialite(Specialite specialite) {
	specialite_ = specialite;
}
