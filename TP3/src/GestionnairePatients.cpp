/****************************************************************
* \class  GestionnairePatients
* \brief  Permet de gérer les patients
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include "../include/GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "../include/typesafe_enum.h"

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients() : patients_(std::vector<std::shared_ptr<Patient>>())
{
}

//! Méhode qui cherche un patient par son numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (auto& patient : patients_)
	{
		if (*patient == numeroAssuranceMaladie)
		{
			return patient.get();
		}
	}

	return nullptr;
}


//! Méthode  qui permet de charger les informations des patients depuis un fichier
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succès
bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		patients_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLignePatient(ligne))
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

//! Opérateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return        Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePatients::operator+=(Patient* patient)
{
	if (patient && !chercherPatient(patient->getNumeroAssuranceMaladie())) {

		if (patients_.size() >= NB_PATIENT_MAX)
		{
			return false;
		}

		if (typeid(*patient) == typeid(Patient))
		{
			patients_.push_back(std::make_shared<Patient>(*patient));
		}
		else
		{
			patients_.push_back(std::make_shared<PatientEtudiant>(*dynamic_cast<PatientEtudiant*>(patient)));
		}


		return true;
	}
	return false;
}

//! opérateur qui affiche les patients
//! \param os Le stream dans lequel afficher
//! \param gestionnairePatients le gestionnaire de patient que l'on veut afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatients)
{
	for (const auto& patient : gestionnairePatients.patients_)
	{
		patient->afficher(os);
		os << '\n';
	}

	return os;
}

//! Méthode qui retourne tous les  patients
//! \return patients_ les patients
const std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients() const
{
	return patients_;
}

//! Méthode qui retourne un vecteur de patients étudiants
//! \return le vecteur de patients étudiants
std::vector<PatientEtudiant*> GestionnairePatients::getPatientsEtudiants() const
{
	auto patientsEtudiants = std::vector<PatientEtudiant*>();
	for (auto& patient : patients_)
	{
		if (dynamic_cast<PatientEtudiant*>(patient.get()))
		{
			patientsEtudiants.push_back(dynamic_cast<PatientEtudiant*>(patient.get()));
		}
	}
	
	return patientsEtudiants;
}


//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return patients_.size();
}

//! Méthode qui retourne le nombre de patients étudiants dans la liste
//! \param le nombre de patients étudiants
size_t GestionnairePatients::getNbPatientsEtudiants() const
{
	return getPatientsEtudiants().size();
}


//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
//! \return bool True si réussit, false si échec
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePatient; // Indique le type de patient. 0 : Patient , 1 : PatientEtudiant (voir l'enum TypePatient)
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;

	std::string matricule;
	std::string etablissement;


	if (stream >> indexTypePatient >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie))
	{
		auto typePatient = to_enum<TypePatient, int>(indexTypePatient);
		switch(typePatient)
		{
			case TypePatient::Patient:
			{

				if(*this += (std::make_shared<Patient>(nomPatient, anneeDeNaissance, numeroAssuranceMaladie)).get()) 
				{
					return true;
				}

				return false;
			}
			case TypePatient::PatientEtudiant:
			{
				if (stream >> std::quoted(matricule) >> std::quoted(etablissement))
				{
					if(*this += (std::make_shared<PatientEtudiant>(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, matricule, etablissement)).get()) 
					{ 
						return true; 
					}
					
					return false;
				}

				return false;
			}
			default: 
				return false;
		}
	}
	return false;
}
