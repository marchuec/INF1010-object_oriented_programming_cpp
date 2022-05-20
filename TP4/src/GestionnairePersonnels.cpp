/****************************************************************
* \class  GestionnairePersonnels
* \brief  Permet de gérer le personnel
*
* \author Marc-Antoine Huet
* \date   11/08/2020
****************************************************************/

#include "GestionnairePersonnels.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

//Ajouts
#include "Foncteurs.h"

constexpr int PERSONNEL_INEXSISTANT = -1;

//! Méthode qui cherche un personnel par son id
//! \param id L'identifiant du personnel à chercher
//! \return Un pointeur vers le personnel. Le pointeur est nullptr si le personnel n'existe pas dans la liste des personnels.
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id) const
{
	auto ite = personnels_.find(id);
	if (ite != personnels_.end())
	{
		return ite->second.get();
	}
	return nullptr;
}


//! Méthode  qui permet de charger les informations des personnels
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succes
bool GestionnairePersonnels::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		personnels_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLignePersonnel(ligne))
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

//! Méthode qui ajoute un personnel à la liste des personnels s'il n'y est pas déjà
//! \param personnel Le personnel à ajouter
//! \return          Un bool qui indique si l'opération a bien fonctionnée. True si réussit.
template<typename T>
bool GestionnairePersonnels::ajouterPersonnel(const T& personnel)
{
	if (!chercherPersonnel(personnel.getId()))
	{
		personnels_.insert({personnel.getId(), std::make_shared<T>(personnel)});
		return true;
	}
	return false;
}

//! Méthode qui supprime un personnel à la liste des personnels s'il n'y est pas déjà
//! \param personnel Le personnel à supprimer
//! \return          Un bool qui indique si l'opération a bien fonctionnée. True si réussit.
template<typename T>
bool GestionnairePersonnels::supprimerPersonnel(const std::string& id)
{
	auto personnel = chercherPersonnel(id);
	if (personnel)
	{
		personnel->setEstActif(false);
		return true;
	}
	return false;
}

//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePersonnels)
{
	// Code fourni
	if constexpr (false)
	{
		for (auto it = gestionnairePersonnels.personnels_.cbegin(); it != gestionnairePersonnels.personnels_.cend(); ++it)
		{
			it->second->afficher(os);
			os << '\n';
		}
		return os;
	}
	else
	{
		for (auto& personnelPaire : gestionnairePersonnels.personnels_)
		{
			personnelPaire.second->afficher(os);
			os << '\n';
		}
		return os;
	}
}

//! Méthode qui retourne la liste de tout le personnel de l'hôpital
//! \return personnels_ La liste du personnel
std::unordered_map<std::string, std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels()
{
	return personnels_;
}

//! Méthode qui retourne une unordered_map contenant les personnels de type T (personnel, médecin ou médecin résident)
//! \return La unordered_map contenant les personnels de type T
template <typename T>
std::unordered_map<std::string, T*> GestionnairePersonnels::getPersonnelsAvecType() const
{
	std::unordered_map<std::string, T*> personnelAvecType;
	for (auto& personnel : personnels_)
	{
		auto personnelAjoutPtr = dynamic_cast<T*>(personnel.second.get());
		if (personnelAjoutPtr)
		{
			personnelAvecType.insert({personnel.first, personnelAjoutPtr});
		}
	}
	return personnelAvecType;
}

//! Méthode qui trie le personnel de l'hôpital en fonction du salaire annuel
//! \return Un vecteur de paires contenant Id et Personnel
std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> GestionnairePersonnels::getPersonnelsTriesSuivantSalaireAnnuel()
{
	std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> personnelTrie;
	copy(personnels_.begin(), personnels_.end(), back_inserter(personnelTrie));
	sort(personnelTrie.begin(), personnelTrie.end(), ComparateurSecondElementPaire<std::string, std::shared_ptr<Personnel>>());

	return personnelTrie;

}

//! Méthode qui retourne le nombre des personnels
//! \return le nombre de tous le pesonnels
size_t GestionnairePersonnels::getNbPersonnels() const
{
	return personnels_.size();
}

//! Méthode qui retourne le nombre de médecins de la liste
//! \return Le nombre de medecins dans la liste
size_t GestionnairePersonnels::getNbMedecins() const
{
	return getPersonnelsAvecType<Medecin>().size();
}

//! Méthode qui retourne le nombre de médecins résidents de la liste
//! \return Le nombre de médecins résidents dans la liste
size_t GestionnairePersonnels::getNbMedecinsResidents() const
{
	return getPersonnelsAvecType<MedecinResident>().size();
}

//! Méthode qui lit les attributs d'un personnel à partir d'une ligne
//! \param ligne Le string qui contient les attributs
//! \return bool True si réussit, false si échec
bool GestionnairePersonnels::lireLignePersonnel(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePersonnel;
	std::string nomPersonnel;
	std::string id;
	std::string dateAdhesion;

	std::string dateDeNaissance;
	std::string matricule;
	std::string etablissement;

	int indexSpecialite;

	if (stream >> indexTypePersonnel >> std::quoted(nomPersonnel) >> std::quoted(id) >> std::quoted(dateAdhesion))
	{
		auto dateAdhesionTm = convertirStringDate(dateAdhesion);
		switch (to_enum<GestionnairePersonnels::TypePersonnel, int>(indexTypePersonnel)) {
		case TypePersonnel::Medecin:
			stream >> indexSpecialite;
			return GestionnairePersonnels::ajouterPersonnel<Medecin>(Medecin(nomPersonnel, id, to_enum<Medecin::Specialite, int>(indexSpecialite), dateAdhesionTm));
		case TypePersonnel::MedecinResident:
			stream >> std::quoted(dateDeNaissance) >> std::quoted(matricule) >> std::quoted(etablissement) >> indexSpecialite;
			return GestionnairePersonnels::ajouterPersonnel<MedecinResident>(MedecinResident(nomPersonnel, dateDeNaissance, matricule, etablissement, 
																			 id, to_enum<Medecin::Specialite, int>(indexSpecialite), dateAdhesionTm));
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
			return false;
		}
	}

	return false;
}