/****************************************************************
* \class  Étudiant
* \brief  Contient l'information sur l'étudiant
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include "../include/Etudiant.h"
#include <iostream>
#include <string>

//! Constructeur par paramètre de la classe de base Etudiant
//! \param nom 				le nom de l'étudiant
//! \param dateDeNaissance  la date de naissance de l'étudiant
//! \param matricule 		le matricule de l'étudiant
//! \param etablissement 	l'établissement de l'étudiant
Etudiant::Etudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, 
				   const std::string& etablissement)
	: nom_(nom), dateDeNaissance_(dateDeNaissance), matricule_(matricule), etablissement_(etablissement) 
{	
}

//! Méthode qui affiche les informations de l'étudiant
//! \param stream Le stream dans lequel afficher
void Etudiant::afficher(std::ostream& stream) const
{
	stream << "Matricule: " << matricule_ << "\n\tEtablissement: " << etablissement_;
}

//! Méthode qui retourne le nom de l'étudiant
//! \return nom_ le nom de l'étudiant
const std::string& Etudiant::getNom() const
{
	return nom_;
}

//! Méthode qui retourne le matricule de l'étudiant
//! \return matricule_ le matricule de l'étudiant
const std::string& Etudiant::getMatricule() const
{
	return matricule_;
}

//! Méthode qui retourne l'établissement de l'étudiant
//! \return etablissement_ l'établissement de l'étudiant
const std::string& Etudiant::getEtablissement() const
{
	return etablissement_;
}

//! Méthode qui retourne la date de naissance de l'étudiant
//! \return dateDeNaissance_ la date de naissance de l'étudiant
const std::string& Etudiant::getDateDeNaissance() const
{
	return dateDeNaissance_;
}

//! Méthode qui permet de mettre à jour le nom de l'étudiant
//! \param nom le nom de l'étudiant
void Etudiant::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour la date de naissance de l'étudiant
//! \param dateDeNaissance la date de naissance de l'étudiant
void Etudiant::setDateDeNaissance(const std::string& dateDeNaissance)
{
	dateDeNaissance_ = dateDeNaissance;
}

//! Méthode qui permet de mettre à jour l'établissement de l'étudiant
//! \param etablissement l'établissement de l'étudiant
void Etudiant::setEtablissement(const std::string& etablissement)
{
	etablissement_ = etablissement;
}