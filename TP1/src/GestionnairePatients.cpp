/****************************************************************
* Classe: 		GestionnairePatients
* Description:  Permet de gérer les patients de l'hopital
*
* Auteurs: 		Marc-Antoine Huet et François Dubois-Roy
* Date: 		17/07/2020
****************************************************************/

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>


/**
 * Fonction: 	Constructeur par défaut
 * Paramètres:	(patients_[]) Tableau des patients
 * 				(nbPatients_) Nombre de patients de l'hopital 
**/
GestionnairePatients::GestionnairePatients()
	: nbPatients_(size_t(0)) {};


/**
 * Fonction: 	GestionnairePatients::ajouterPatient
 * Description:	Ajoute un patient au tableau patients_
 * Paramètres:	(patient) Le patient à ajouter
 * Retour:		(bool) Retourne true si l'ajout a réussit ou false s'il a échoué
**/
bool GestionnairePatients::ajouterPatient(const Patient& patient) {
	if (nbPatients_ >= NB_PATIENT_MAX) {
		return false;
	}
	else {
		nbPatients_++;
		patients_[nbPatients_ -1] = patient;
		return true;
	}
}


/**
 * Fonction: 	GestionnairePatients::chercherPatient
 * Description:	Cherche un patient dans la liste patients_ par son num. d'assurance maladie
 * Paramètres:	(numeroAssuranceMaladie) Le num. d'assurance maladie du patient
 * Retour:		(ptrPatient) Retourne un pointeur intelligent vers le patient s'il est trouvé, sinon nullptr
**/
std::shared_ptr<Patient> GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie) const {
	if (nbPatients_ != 0) {
		for (int j = 0; j <= (nbPatients_ - 1); j++) {
			if (patients_[j].getNumeroAssuranceMaladie() == numeroAssuranceMaladie) {
				int indice = j;
				auto ptrPatient = std::make_shared<Patient>(patients_[j]);

				return ptrPatient;
			} 
		}
	}
	return nullptr;		// Si nbPatients_ == 0 ou si le patient n'est pas trouvé
}


/**
 * Fonction: 	GestionnairePatients::chargerDepuisFichier
 * Description:	Permet de charger les informations des patients depuis un fichier
 * Paramètres:	(nomFichier) Le nom du fichier
 * Retour:		(bool) Retour true si succès ou false si échec
**/
bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier) {
	bool aReussit;
	std::string ligne;
	std::ifstream fichier(nomFichier);
	if (fichier.is_open()) {
		// Réinitialisation des patients pour ne pas lire 2 fois
		if (nbPatients_ != 0) {
			for (int i = 0; i <= (nbPatients_ -1); i++) {
				patients_[i] = Patient();
			}
		nbPatients_ = 0;
		}

		while (std::getline(fichier, ligne)) {			
			aReussit = lireLignePatient(ligne);
			if (aReussit == false) {
				break;
			}
		}
	fichier.close();
	}
	else {
		aReussit = false;
		std::cerr << "Le fichier " << nomFichier
			<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
	}
	return aReussit;
}

/**
 * Fonction: 	GestionnairePatients::afficher
 * Description:	Affiche tous les patients du tableau dans un stream
 * Paramètres:	(stream) stream dans lequel on écrit les informations
**/
void GestionnairePatients::afficher(std::ostream& stream) const {
	if (nbPatients_ == 0) {
		stream << "Aucun patient\n";
	}
	else {
		for (int i = 0; i <= (nbPatients_ - 1); i++) {
			patients_[i].afficher(stream);
			stream << "\n";
		}
	}
}


/**
 * Fonction: 	GestionnairePatients::getNbPatients
 * Description:	Retourne le nombre de patients de l'hopital
 * Paramètres:	(nbPatients_) Le nombre de patients de l'hopital
**/
size_t GestionnairePatients::getNbPatients() {
	return nbPatients_;
}


/**
 * Fonction: 	GestionnairePatients::lireLignePatient
 * Description:	Lit les attribut d'un patient à partir d'une ligne et l'ajouter au tableau
 * Paramètre:	(ligne) Ligne contenant les attribut entre ""
 * Retour:		(bool) True si réussite ou false si échec
**/

bool GestionnairePatients::lireLignePatient(const std::string& ligne) 
{
	std::istringstream stream(ligne);
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;

	// TODO
	// Utiliser l'opérateur d'extraction (>>) depuis le stream
	// Pour extraire tout ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> std::quoted(variable)
	// retourner true si l'opération a réussi, sinon false

	stream >> std::quoted(nomPatient);
	stream >> std::quoted(anneeDeNaissance);
	stream >> std::quoted(numeroAssuranceMaladie);
	Patient nouveauPatient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie);
	bool aReussit = ajouterPatient(nouveauPatient);

	return aReussit;
}