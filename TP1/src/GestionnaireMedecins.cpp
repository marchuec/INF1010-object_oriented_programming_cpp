/****************************************************************
* Classe: 		GestionnaireMedecins
* Description:  Permet de gérer les médecins de l'hopital
*
* Auteurs: 		Marc-Antoine Huet et François Dubois-Roy
* Date: 		17/07/2020
****************************************************************/

#include "GestionnaireMedecins.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr size_t CAPACITE_MEDECINS_INITIALE = 2;
constexpr int MEDECIN_INEXSISTANT = -1;

/**
 * Fonction: 	constructeur par défaut
**/
// Utilisez CAPACITE_MEDECINS_INITIALE pour la taille initiale de medecins_ (tableau de taille dynamique)
GestionnaireMedecins::GestionnaireMedecins() 
	: nbMedecins_(size_t(0)), capaciteMedecins_(CAPACITE_MEDECINS_INITIALE),
	  medecins_(std::make_unique<std::shared_ptr<Medecin>[]>(capaciteMedecins_)) {};


/**
 * Fonction: 	GestionnaireMedecins::ajouterMedecin
 * Description: Ajoute un médecin à l'hopital (à medecins_)
 * Paramètre:	(medecin) Le médecin à ajouter
**/
void GestionnaireMedecins::ajouterMedecin(std::unique_ptr<Medecin> medecin) {
	static constexpr unsigned int AUGMENTATION_NOMBRE_MEDECINS = 2;
	// TODO
	// Verifier si assez de mémoire est allouée
	// Si pas assez de mémoire, doubler la taille du tableau (AUGMENTATION_NOMBRE_PATIENTS)
	// Ajouter le patient au tableau
	// Utiliser std::unique_ptr<std::shared_ptr<Patient>[]> ainsi que std::move pour transférer le ownership
	// du tableau temporaire vers le tableau membre patientsAssocies_;

	// Double la taille du tableau si nécessaire
	if (nbMedecins_ == capaciteMedecins_) {
		capaciteMedecins_ *= AUGMENTATION_NOMBRE_MEDECINS;
		auto tableauTemp = std::make_unique<std::shared_ptr<Medecin>[]>(capaciteMedecins_);

		for (int i = 0; i <= (nbMedecins_ - 1); i++)
		{
			tableauTemp[i] = std::move(medecins_[i]);
		}
		medecins_ = std::move(tableauTemp);
	}

	// Ajoute le médecin
	nbMedecins_++;
	auto shared_ptrMedecin = std::make_shared<Medecin>(medecin->getNom(), 
													   medecin->getNumeroLicence(), 
													   medecin->getSpecialite());
	medecins_[nbMedecins_ -1] = shared_ptrMedecin;
}


/**
 * Fonction: 	Medecin::chercherMedecin
 * Description: Cherche le médecin dans la liste medecins_ par son numéro de licence
 * Paramètre:	(numeroLicence_) Le num. de licence du médecin
 * Retour:		(ptrMedecin) Retourne le pointeur vers le médecin si trouvé, sinon nullptr
**/
std::shared_ptr<Medecin> GestionnaireMedecins::chercherMedecin(const std::string& numeroLicence) const {
	if (nbMedecins_ != 0) {
		for (int j = 0; j <= (nbMedecins_ - 1); j++) {
			if (medecins_[j]->getNumeroLicence() == numeroLicence) {
				int indice = j;
				auto ptrMedecin = std::make_shared<Medecin>(medecins_[indice]->getNom(), 
															medecins_[indice]->getNumeroLicence(), 
															medecins_[indice]->getSpecialite());

				return ptrMedecin;
			} 
		}
	}
	return nullptr;		// Si nbMedecins_ == 0 ou si le médecin n'est pas trouvé
}

/**
 * Fonction: 	GestionnaireMedecins::chargerDepuisFichier
 * Description: Charle les informations des médecins depuis un fichier
 * Paramètre: 	(nomFichier) Le nom du fichier
 * Retour:		(aReussit) true si succès, false sinon
**/
bool GestionnaireMedecins::chargerDepuisFichier(const std::string& nomFichier) {
	bool aReussit;
	std::string ligne;
	std::ifstream fichier(nomFichier);
	if (fichier.is_open()) {
		// Réinitialisation des patients pour ne pas lire 2 fois
		auto nouveauTableau = std::make_unique<std::shared_ptr<Medecin>[]>(capaciteMedecins_);
		medecins_ = std::move(nouveauTableau);
		nbMedecins_ = 0;

		while (std::getline(fichier, ligne)) {			
			aReussit = lireLigneMedecin(ligne);
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
 * Fonction: 	GestionnaireMedecins::supprimerMedecin
 * Description: Supprime un médecin de l'hopital (estActif = false)
 * Paramètre: 	(numeroLicence) Le num. de licence du médecin
 * Retour:		(bool) true si réussite, false sinon
**/
// Chercher l'index du medecin dans le tableau medecins_ en faisant appel à la fonction trouverIndexMedecin
// Rendez le medecin inactif. Attention : il ne fait pas retirer le medecin du tableau medecins_
// Retourner true si le medein est trouvé et rendu inactif, sinon retourné false
bool GestionnaireMedecins::supprimerMedecin(const std::string& numeroLicence) {
	int indice = trouverIndexMedecin(numeroLicence);
	std::cout <<"Indice:" <<indice << "\n";
	if (indice == -1) {
		return false;
	} 
	/*
	else {
		medecins_[indice]->setEstActif(false);
		std::cout <<"Set à inactif!\n";
		return true;
	}
	*/
	return true;
}


/**
 * Fonction: 	GestionnaireMedecins::afficher
 * Description: Affiche tous les médecins de l'hopital
 * Paramètre: 	(stream) Le stream contenant les informations des médecins
**/
void GestionnaireMedecins::afficher(std::ostream& stream) const {
	if (nbMedecins_ != 0) {
		for (int i = 0; i <= (nbMedecins_ - 1); i++) {
			medecins_[i]->afficher(stream);
		}
	}
}


/**
 * Fonction: 	GestionnaireMedecins::getNbMedecins()
 * Description: Retourne le nombre de médecins
 * Retour:   	(nbMedecins_) Le nombre de médecins
**/
size_t GestionnaireMedecins::getNbMedecins() const {
	return nbMedecins_;
}


/**
 * Fonction: 	GestionnaireMedecins::getCapaciteMedecins()
 * Description: Retourne la capacité en médecins de l'hopital
 * Retour:   	(capaciteMedecins_) La capacité en médecins de l'hopital
**/
size_t GestionnaireMedecins::getCapaciteMedecins() const{
	return capaciteMedecins_;
}

/**
 * Fonction: 	GestionnaireMedecins::lireLigneMedecin
 * Description: Lit les attribut d'un médecin à partir d'un string
 * Paramètre:   (ligne) Le string contenant les attributs
 * Retour:		(bool) Retourne toujours true
**/
bool GestionnaireMedecins::lireLigneMedecin(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomMedecin;
	std::string numeroLicence;
	std::string indexSpecialiteStr;
	int indexSpecialite;

	// TODO
	// Utiliser l'opérateur d'extraction (>>) depuis le stream
	// Pour extraire tout ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> std::quoted(variable)

	// Hint : utiliser la fonction to_enum<Medecin::Specialite, int>(variable) pour convertir 
	// l'indice de la spécialité en enum Specilité
	// retourner true si l'opération a réussi, sinon false

	stream >> std::quoted(nomMedecin);
	stream >> std::quoted(numeroLicence);
	stream >> std::quoted(indexSpecialiteStr);

	indexSpecialite = std::stoi(indexSpecialiteStr);
	Medecin::Specialite specialite = to_enum<Medecin::Specialite, int>(indexSpecialite);
	auto nouveauMedecin = std::make_unique<Medecin> (Medecin(nomMedecin, numeroLicence, specialite));
	ajouterMedecin(move(nouveauMedecin));

	return true;
}


/**
 * Fonction: 	GestionnaireMedecins::trouverIndexMedecin
 * Description: Chercher l'indice du médecin à partir de son num. de licence
 * Paramètre:   (numeroLicence) Le num. de licence du médecin
 * Retour:		(int) L'indice si trouvé ou -1 sinon (MEDECIN_INEXISTANT)	
**/
int GestionnaireMedecins::trouverIndexMedecin(const std::string& numeroLicence) {
	for (int i = 0; i < nbMedecins_ -1; i++) {
		if (medecins_[i]->getNumeroLicence() == numeroLicence) {
			return i;
		}
	}

	return -1;
}