/****************************************************************
* Classe: 		Patient 
* Description:  Contient les informations sur le patient
*
* Auteurs: 		Marc-Antoine Huet et François Dubois-Roy
* Date: 		17/07/2020
****************************************************************/

#include "Patient.h"
#include <iostream>
#include <string>


/**
 * Fonction:   Constructeur par paramètres de Patient
 * Paramètres: (nom) Le nom du patient
 * 			   (dateDeNaissance) La date de naissance du patient
 * 			   (numeroAssuranceMaladie) Le numéro d'assurance maladie du patient
**/
Patient::Patient() = default;
Patient::Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie)
    : nom_(nom), dateDeNaissance_(dateDeNaissance), numeroAssuranceMaladie_(numeroAssuranceMaladie) {};


/**
 * Fonction: 	Patient::afficher
 * Description: Affiche les informations du patient
 * Paramètres:  (stream) stream dans lequel on écrit les informations
**/
void Patient::afficher(std::ostream& stream) const {
	// Ne modifiez pas cette fonction
	stream << "Patient: " << nom_ << " | Date de naissance: " << dateDeNaissance_
		<< " | Numero d'assurance maladie: " << numeroAssuranceMaladie_;
}


/**
 * Fonction: 	Patient::getnom
 * Description: Obtient le nom du patient
 * Retour: 	 	(nom_) Le nom du patient
**/
const std::string& Patient::getNom() const {
	return nom_; 
}


/**
 * Fonction: 	Patient::getNumeroAssuranceMaladie
 * Description: Obtient le numero d'assurance maladie du patient
 * Retour: 	 	(numeroAssuranceMaladie_) Le numéro d'assurance maladie du patient
**/
const std::string& Patient::getNumeroAssuranceMaladie() const {
	return numeroAssuranceMaladie_; 
}


/**
 * Fonction: 	Patient::getDateDeNaissance
 * Description: Obtient la date de naissance du patient
 * Retour: 	 	(dateDeNaissance_) La date de naissance du patient
**/
const std::string& Patient::getDateDeNaissance() const {
	return dateDeNaissance_; 
}


/**
 * Fonction: 	Patient::setNom
 * Description: Initialise le nom du patient
 * Paramètre:	(nom) Le nom du patient
**/
void Patient::setNom(const std::string& nom) {
	nom_ = nom; 
}


/**
 * Fonction: 	Patient::setNumeroAssuranceMaladie
 * Description: Initialise le num. d'assurance maladie du patient
 * Paramètre:	(numeroAssuranceMaladie) Le numéro d'assurance maladie du patient
**/
void Patient::setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie) {
	numeroAssuranceMaladie_ = numeroAssuranceMaladie; 
}


/**
 * Fonction: 	Patient::setDateDeNaissance
 * Description: Initialise la date de naissance du patient
 * Paramètre:	(dateDeNaissance) La date de naissance du patient
**/
void Patient::setDateDeNaissance(const std::string& dateDeNaissance) {
	dateDeNaissance_ = dateDeNaissance; 
}


