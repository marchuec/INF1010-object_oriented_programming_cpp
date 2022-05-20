//TODO Entête du fichier

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

//Ajouts
#include "Foncteurs.h"
#include "utils.h"

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients() : patients_(std::vector<std::shared_ptr<Patient>>())
{
}

//! Méhode qui cherche un patient par son numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	auto ite = std::find_if(patients_.begin(), patients_.end(), 
							ComparateurEstEgalAvecId<Patient>(numeroAssuranceMaladie));
	if (ite != patients_.end())
	{
		return ite->get();
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

//! Méthode qui ajoute un patient à la liste des patients s'il n'y est pas déjà
//! \param patient Le patient à ajouter
//! \return        Un bool qui indique si l'opération a bien fonctionnée
template <typename T>
bool GestionnairePatients::ajouterPatient(const T& patient)		// Patient ou patient étudiant
{
	if (patients_.size() <= NB_PATIENT_MAX && !chercherPatient(patient.getNumeroAssuranceMaladie()))
	{
		patients_.push_back(std::make_shared<T>(patient));

		return true;
	}
	return false;
}

//! Méthode qui permet de supprimer un patient
//! \param numeroAssuranceMaladie Le numéro d'assurance maladie du patient
//! \return True si l'opération a réussit, false sinon
bool GestionnairePatients::supprimerPatient(const std::string& numeroAssuranceMaladie)
{
	auto ite = remove_if(patients_.begin(), patients_.end(), 
						 ComparateurEstEgalAvecId<Patient>(numeroAssuranceMaladie));
	if (ite != patients_.end())
	{
		patients_.erase(ite, patients_.end());
		return true;
	}
	return false;
}


//! Opérateur qui affiche les patients
//! \param os Le stream dans lequel afficher
//! \param gestionnairePatients le gestionnaire de patient que l'on veut afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatients)
{
	// Code fourni
	if constexpr (false)
	{
		for (auto it = gestionnairePatients.patients_.cbegin(); it != gestionnairePatients.patients_.cend(); ++it)
		{
			(*it)->afficher(os);
			os << '\n';
		}
		return os;
	}
	else
	{
		for (auto& patient : gestionnairePatients.patients_)
		{
			patient->afficher(os);
			os << '\n';
		}
		return os;
	}
}

//! Méthode qui retourne tous les  patients
//! \return patients_ les patients
const std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients() const
{
	return patients_;
}

//! Méthode qui retourne un vecteur de patients étudiants
//! \return le vecteur de patients étudiants
std::vector<std::shared_ptr<Patient>> GestionnairePatients::getPatientsEtudiants() const	// Pourquoi ça demande de retourner Patient ??
{
	auto patientsEtudiants = std::vector<std::shared_ptr<Patient>>();
	copy_if(patients_.begin(), patients_.end(), back_inserter(patientsEtudiants), ComparateurTypePatient<PatientEtudiant>());
	return patientsEtudiants;

}

//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return patients_.size();
}

//! Méthode qui retourne le nombre des patients étudiants dans la liste
//! \return Le nombre de patients étudiants dans la liste
size_t GestionnairePatients::getNbPatientsEtudiants() const
{
	return getPatientsEtudiants().size();
}


//! Méthode qui lit les attributs d'un patient à partir d'une ligne
//! \param ligne Le string qui contient les attributs
//! \return bool True si réussit, false si échec
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePatient;
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;
	std::string dateAdhesion;

	std::string matricule;
	std::string etablissement;

	if (stream >> indexTypePatient >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie) >> std::quoted(dateAdhesion))
	{
		auto dateAdhesionTm = convertirStringDate(dateAdhesion);
		switch (to_enum<GestionnairePatients::TypePatient, int>(indexTypePatient)) {
		case TypePatient::Patient:
			return ajouterPatient<Patient>(Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, dateAdhesionTm));
		case TypePatient::PatientEtudiant:
			stream >> std::quoted(matricule) >> std::quoted(etablissement);
			return ajouterPatient<PatientEtudiant>(PatientEtudiant(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, dateAdhesionTm, matricule, etablissement));
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
		}

		return true;
	}

	return false;
}
