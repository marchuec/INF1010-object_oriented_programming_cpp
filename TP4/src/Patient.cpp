/****************************************************************
* \class  Patient
* \brief  Contient les informations du patient
*
* \author Marc-Antoine Huet
* \date   11/08/2020
****************************************************************/

#include "Patient.h"
#include <iostream>
#include <string>

//! Constructeur par paramètres de la classe Patient
//! \param nom 						Le nom du patient
//! \param numeroAssuranceMaladie 	Le numéro d'assurance maladie du patient
//! \param dateDeNaissance 			La date de naissance du patient
//! \param dateAdhesion 			La date d'adhésion du patient
Patient::Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie,
				 const tm& dateAdhesion)
	: nom_(nom)
	, numeroAssuranceMaladie_(numeroAssuranceMaladie)
	, dateDeNaissance_(dateDeNaissance)
	, dateAdhesion_(dateAdhesion)
{
}

//! Opérateur qui compare un string avec le numero d'assurance maladie du patient avec patient comme opérande de gauche
//! \param numeroAssuranceMaladie le numero d'assurance  avec le quel on veut comparé le patient
//! \return vrai si les les numeros d'assurance sont identiques, faux sinon
bool Patient::operator==(const std::string& numeroAssuranceMaladie) const
{
	return (numeroAssuranceMaladie_ == numeroAssuranceMaladie);
}

//! Opérateur qui compare le numero d'assurance maladie du patient avec le numero d'assurance comme opérande de gauche.
//! \param numeroAssuranceMaladie le numero d'assurance avec le quel on veut comparé le patient
//! \param patient le patient avec lequel on compare le numero d'assurance
bool operator==(const std::string& numeroAssuranceMaladie, const Patient& patient)
{
	return (numeroAssuranceMaladie == patient.numeroAssuranceMaladie_);
}

//! Méthode qui affiche les informations d'un patient
//! \param stream Le stream dans lequel afficher.
void Patient::afficher(std::ostream& stream) const
{
	stream << "Patient: ";
	std::string typePatient = typeid(*this).name();
	stream << "\n\tType: " << typePatient.substr(6, typePatient.length() - 6 + 1);
	stream << "\n\tNom: " << nom_ << " | Date de naissance: " << dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << numeroAssuranceMaladie_;
}

//! Méthode qui retourne le nom du patient
//! \return nom_ le nom du patient
const std::string& Patient::getNom() const
{
	return nom_;
}

//! Méthode qui retourne le numéro d'assurance maladie du patient
//! \return numeroAssuranceMaladie_ le numéro d'assurance maladie du patient
const std::string& Patient::getNumeroAssuranceMaladie() const
{
	return numeroAssuranceMaladie_;
}

//! Méthode qui retourne la date de naissance du patient
//! \return dateDeNaissance_la date de naissnace du patient 
const std::string& Patient::getDateDeNaissance() const
{
	return dateDeNaissance_;
}

//! Méthode qui retourne la date d'adhésion du patient
//! \return dateAdhesion_ la date d'adhésion du patient
const tm& Patient::getDateAdhesion() const
{
	return dateAdhesion_;
}

//! Méthode qui permet de mettre à jour le nom du patient
//! \param nom Le nom du patient
void Patient::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour le nom du numero d'assurance maladie du patient
//! \param numeroAssuranceMaladie Le numero d'assurance maladie
void Patient::setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie)
{
	numeroAssuranceMaladie_ = numeroAssuranceMaladie;
}

//! Méthode qui permet de mettre à jour la date de naissance du patient
//! \param dateDeNaissance La date de naissance du patient
void Patient::setDateDeNaissance(const std::string& dateDeNaissance)
{
	dateDeNaissance_ = dateDeNaissance;
}

//! Méthode qui permet de mettre à jour la date d'adhésion du patient
//! \param dateAdhesion La date d'adhésion du patient
void Patient::setDateAdhesion(const tm& dateAdhesion)
{
	dateAdhesion_ = dateAdhesion;
}

