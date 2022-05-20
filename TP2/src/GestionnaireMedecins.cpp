/****************************************************************
* \class  GestionnaireMedecins
* \brief  Permet de gérer les médecins
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   22/07/2020
****************************************************************/

#include "GestionnaireMedecins.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr int MEDECIN_INEXSISTANT = -1;

//! Constructeur par defaut de la classe GestionnaireMedecins
GestionnaireMedecins::GestionnaireMedecins()
{
}

//! Constructeur de copie
//! \param gestionnaireMedecins L'objet à copier
GestionnaireMedecins::GestionnaireMedecins(const GestionnaireMedecins& gestionnaireMedecins)
	: medecins_(std::vector<std::shared_ptr<Medecin>>(gestionnaireMedecins.getNbMedecins()))
{
	for (int i = 0; i < gestionnaireMedecins.getNbMedecins(); i++)
	{
		medecins_[i] = std::make_shared<Medecin>(*gestionnaireMedecins.medecins_[i]);
	
	}
}

//! Opérateur d'affectation
//! \param gestionnaireMedecins L'objet à affecter
GestionnaireMedecins& GestionnaireMedecins::operator=(const GestionnaireMedecins& gestionnaireMedecins)
{
	if (this != &gestionnaireMedecins)
	{
		GestionnaireMedecins gestionnaireMedecinsTemp = GestionnaireMedecins(gestionnaireMedecins);
		std::swap(this->medecins_, gestionnaireMedecinsTemp.medecins_);
	}
	return *this;
}

//! Méthode qui cherche un medecin par son numéro de licence
//! \param numeroLicence Le nom de licence à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le medecin n'existe pas dans la liste des medecin.
Medecin* GestionnaireMedecins::chercherMedecin(const std::string& numeroLicence)
{
	for (int i = 0; i < medecins_.size(); i++)
	{
		// Adapater la ligne ci-dessous en utilisant l'operateur == pour la comparaison
		if (*medecins_[i] == numeroLicence)
		{
			// TODO retourner un pointeur vers le medecin 
			return medecins_[i].get();
		}
	}

	return nullptr;
}

//! Méthode  qui permet de charger les informations des medecins depuis un fichier
//! \param  nomFichier   Le nom du fichier à charger
//! \return bool         Un bool qui indique si le fichier a été chargé avec succes
bool GestionnaireMedecins::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		// Réinitialiser les médecins
		if (medecins_.size() != 0)
		{
			medecins_ = std::vector<std::shared_ptr<Medecin>>();	
		}

		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (lireLigneMedecin(ligne) == false)
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


// TODO: Methode ajouterMedecin doit être remplacée par l'opérteur +=. il prend en paramètre une référence vers le medecin à ajouter
//! Opérateur += qui ajoute un médecin à la liste des médecins
//! \param  medecin Le médecin à ajouter
//! \return bool 	True si l'opération a bien fonctionnée, false sinon
bool GestionnaireMedecins::operator+=(const Medecin& medecin)
{
	if (chercherMedecin(medecin.getNumeroLicence()) == nullptr)
	{
		medecins_.push_back(std::make_shared<Medecin>(medecin));
		return true;
	}
	return false;
}


// TODO: Methode supprimerMedecin doit être remplacée par l'operteur -= Il prend en paramètre le numéro de licence 
//! Opérateur -= qui supprime un médecin de la liste des médecin (estActif = inactif)
//! \param  numeroLicence Le num. de licence du médecin à supprimer
//! \return bool		  True si l'opération a bien fonctionnée, false sinon
bool GestionnaireMedecins::operator-=(const std::string& numeroLicence)
{
	int indice = trouverIndexMedecin(numeroLicence);
	if (indice != MEDECIN_INEXSISTANT)
	{
		medecins_[indice]->setEstActif(false);
		return true;
	}
	return false;
}

// TODO : La methode afficher doit être remplacée par l’opérateur << 
//! Opérateur pour afficher la liste des medecins
//! \param stream Le stream dans lequel afficher
std::ostream& operator<<(std::ostream& stream, const GestionnaireMedecins& gestionnaireMedecins)
{
	for (size_t i = 0; i < gestionnaireMedecins.getNbMedecins(); i++)
	{
		stream << *gestionnaireMedecins.medecins_[i];
	}
	return stream;
}


//! Méthode qui retourne le nombre des medecins dans la liste
//! \return Le nombre de medecins dans la liste
size_t GestionnaireMedecins::getNbMedecins() const
{
	return medecins_.size();
}

// TODO : getMedecins() retourne une reference constante vers le vecteur medecins_
//! Méthode qui retourne les médecins
//! \return Le vecteur de médecins
const std::vector<std::shared_ptr<Medecin>>& GestionnaireMedecins::getMedecins() const
{
	return medecins_;
}

//! Méthode qui retour la capacité de médecins
//! \return La capacité de médecins
size_t GestionnaireMedecins::getCapaciteMedecins() const
{

	return medecins_.capacity();
}

//! Méthode qui lit les attributs d'un medecin
//! \param ligne  Le string qui contient les attributs
//! \return True si l'opération est réussit, false sinon
bool GestionnaireMedecins::lireLigneMedecin(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomMedecin;
	std::string numeroLicence;
	int indexSpecialite;

	// Pour extraire ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> quoted(variable)

	if (stream >> std::quoted(nomMedecin) >> std::quoted(numeroLicence) >> indexSpecialite)
	{
		// Adapter cette méthode pour utiliser l'opérateur+=
		*this += Medecin(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite));

		return true;
	}

	return false;
}


//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
//! \return Retourne un int qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
int GestionnaireMedecins::trouverIndexMedecin(const std::string& numeroLicence)
{
	// À Adapter pour vecteur et l'utilisation l'opérateur == 
	for (std::size_t i = 0; i < medecins_.size(); i++)
	{
		if (medecins_[i]->getNumeroLicence() == numeroLicence)
		{
			return static_cast<int>(i);
		}
	}
	return MEDECIN_INEXSISTANT;
}
