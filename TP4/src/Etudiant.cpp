//! Class Etudiant
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "Etudiant.h"
#include <iostream>
#include <string>

//! Constructeur par param�tres de la classe de base Etudiant
//! \param nom				Le nom de l'�tudiant
//! \param dateDeNaissance  La date de naissance de l'�tudiant
//! \param matricule		Le matricule de l'�tudiant
//! \param etablissement    L'�tablissement d'�tude de l'�tudiant
Etudiant::Etudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablissement)
	:etablissement_(etablissement)
	, nom_(nom)
	, matricule_(matricule)
	, dateDeNaissance_(dateDeNaissance)
{
}

//! M�thode qui affiche les informations de l'�tudiant
//! \param os Le stream dans lequel afficher
void Etudiant::afficher(std::ostream& stream) const
{
	stream << "Matricule: " << matricule_ << "\n\tEtablissement: " << etablissement_;
}

//! M�thode qui retourne le nom de l'�tudiant
//! \return nom_ le nom du l'�tudiant  
const std::string& Etudiant::getNom() const
{
	return nom_;
}

//! M�thode qui retourne le matricule de l'�tudiant
//! \return matricule_ le matricule
const std::string& Etudiant::getMatricule() const
{
	return matricule_;
}

//! M�thode qui retourne  l'�tablissement de l'�tudiant
//! \return  etablissement_ l'�tablissement de l'�tudiant
const std::string& Etudiant::getEtablissement() const
{
	return etablissement_;
}

//! M�thode qui retourne la date de naissance de l'�tudiant
//! \return dateDeNaissance_ la date de naissance
const std::string& Etudiant::getDateDeNaissance() const
{
	return dateDeNaissance_;
}

//! M�thode qui met a jours le nom  de l'�tudiant
//! \pararm  nom  Le nom de l'�tudiant
void Etudiant::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! M�thode qui met a jours le matricule de l'�tudiant
//! \pararm  matircule le matricule de l'�tudiant
void Etudiant::setMatricule(const std::string& matricule)
{
	matricule_ = matricule;
}

//! M�thode qui met a jours la date de naissance de l'�tudiant
//! \pararm  dateDeNaissance la date de naissance de l'�tudiant
void Etudiant::setDateDeNaissance(const std::string& dateDeNaissance)
{
	dateDeNaissance_ = dateDeNaissance;
}

//! M�thode qui met a jours l'�tablissement de l'�tudiant
//! \pararm  etablissement l'�tablissement de l'�tudiant
void Etudiant::setEtablissement(const std::string& etablissement)
{
	etablissement_ = etablissement;
}