/****************************************************************
* \class  GestionnairePatients
* \brief  Permet de gérer les patients
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   22/07/2020
****************************************************************/

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//! Constructeur par défaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients()
{
}

//! Constructeur de copie
//! \param gestionnairePatients L'objet gestionnairePatients à copier
GestionnairePatients::GestionnairePatients(const GestionnairePatients& gestionnairePatients)
	: patients_(std::vector<std::shared_ptr<Patient>>(gestionnairePatients.getNbPatients()))	// Pour init. la capacité
{
	std::vector<std::shared_ptr<Medecin>> nouveauVecteur;
	
	for (int i = 0; i < gestionnairePatients.getNbPatients(); i++)
	{
		patients_[i] = std::make_shared<Patient>(*gestionnairePatients.patients_[i]);
	}
	
}

//! Opérateur d'affectation
//! \param  gestionnairePatients L'objet gestionnairePatients à affecter
GestionnairePatients& GestionnairePatients::operator=(const GestionnairePatients& gestionnairePatients)
{
	if (this != &gestionnairePatients)
	{
		GestionnairePatients gestionnairePatientsTemp = GestionnairePatients(gestionnairePatients);
		std::swap(this->patients_, gestionnairePatientsTemp.patients_);
	}
	return *this;
}


//! Méhode qui cherche un patient par son numéro d'assurance maladie
//! \param numeroAssuranceMaladie Le numéro d'assurance maladie du patient
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (int i = 0; i < patients_.size(); i++)
	{
		// À adapter au vecteur et pour l'opérateur==
		if (*patients_[i] == numeroAssuranceMaladie)
		{
			return patients_[i].get();
		}
	}
	return nullptr;
}

//! Méthode  qui permet de charger les informations des patients depuis un fichier et de les ajouter aux patients
//! \param  nomFichier   Le nom du fichier à charger
//! \return bool         True si les patients ont été transférés du fichier avec succès, false sinon
bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		// Réinitialiser les patients
		if (patients_.size() != 0)
		{
			patients_ = std::vector<std::shared_ptr<Patient>>();	
		}
		
		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			if (lireLignePatient(ligne) == false)
			{
				return false;
			}
		}
		return true;
	}

	std::cerr << "Le fichier " << nomFichier
		      << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";

	return false;
}

// TODO: Methode ajouterPatientdoit être remplacée par l'operteur +=. il prend en paramètre une référence vers le patient à ajouter
//! Opérateur += qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePatients::operator+=(const Patient& patient)
{
	if (chercherPatient(patient.getNumeroAssuranceMaladie()) == nullptr && patients_.size() < NB_PATIENT_MAX)
	{
		patients_.push_back(std::make_shared<Patient>(patient));

		return true;
	}
	return false;
}


// TODO : La methode afficher  doit être remplacée L’opérateur << 
//! Opérateur << pour afficher la liste des patients
//! \param stream 	Le stream dans lequel afficher
//! \param patients Les patients à afficher
std::ostream& operator<<(std::ostream& stream, const GestionnairePatients& gestionnairePatients)
{
	for (int i = 0; i < gestionnairePatients.patients_.size(); i++) 
	{
		stream << *gestionnairePatients.patients_[i];
	}
	return stream;
}


//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return patients_.size();
}

// TODO : getPatients()  retourne une reference constante vers le vecteur patients_
//! Méthode qui retourne une référence constante vers le vecteur patients_
//! \return Le vecteur patients_
std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients()
{
	return patients_;
}

//! Méthode qui lit les attributs d'un patient et l'ajoute aux patients
//! \param ligne  Le string qui contient les attributs
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;

	// Pour extraire ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> quoted(variable)

	if (stream >> quoted(nomPatient) >> quoted(anneeDeNaissance) >> quoted(numeroAssuranceMaladie))
	{
		return *this += Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie);
	}
	else 
	{
		return false;
	}
}