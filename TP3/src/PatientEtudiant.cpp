/****************************************************************
* \class  PatientEtudiant
* \brief  Contient l'information d'un patient qui est étudiant
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include "../include/PatientEtudiant.h"
#include <iostream>
#include <string>

//! Constructeur par paramètre de la classe héritée PatientEtudiant
//! \param nom                      le nom du patient étudiant
//! \param dateDeNaissance          la date de naissance du patient étudiant
//! \param matricule                le matricule du patient étudiant
//! \param numeroAssuranceMaladie   le numéro d'assurance maladie du patient étudiant
//! \param etablissement            l'établissement du patient étudiant
//! \param tauxRabais               le taux de rabais appliqué au patient étudiant
PatientEtudiant::PatientEtudiant(const std::string& nom, const std::string dateDeNaissance, 
                                 const std::string numeroAssuranceMaladie, const std::string& matricule, 
                                 const std::string& etablissement) 
    : Patient::Patient(nom, dateDeNaissance, numeroAssuranceMaladie), 
      Etudiant::Etudiant(nom, dateDeNaissance, matricule, etablissement),
      tauxRabais_(TAUX_RABAIS)
{
}

//! Méthode qui affiche les informations du patient étudiant
//! \param stream Le stream dans lequel écrire les informations
void PatientEtudiant::afficher(std::ostream& stream) const
{
    Patient::afficher(stream);
    stream << " | ";
    Etudiant::afficher(stream);
    stream << " | " << "Taux de rabais: " << tauxRabais_;
}

//! Méthode qui retourne le nom du patient étudiant
//! \return nom_ le nom du patient étudiant
const std::string& PatientEtudiant::getNom() const
{
	return Patient::getNom();
}

//! Méthode qui retourne la date de naissance du patient étudiant
//! \return dateDeNaissance_la date de naissnace du patient étudiant
const std::string& PatientEtudiant::getDateDeNaissance() const
{
	return Patient::getDateDeNaissance();
}

//! Méthode qui retourne le taux de rabais du patient étudiant
//! \return tauxRabais le taux de rabais appliqué au patient étudiant
const double PatientEtudiant::getTauxRabais() const
{
	return tauxRabais_;
}

//! Méthode qui permet de mettre à jour le nom du patient étudiant
//! \param nom Le nom du patient étudiant
void PatientEtudiant::setNom(const std::string& nom)
{
	Patient::setNom(nom);
    Etudiant::setNom(nom);
}

//! Méthode qui permet de mettre à jour la date de naissance du patient étudiant
//! \param dateDeNaissance La date de naissance du patient étudiant
void PatientEtudiant::setDateDeNaissance(const std::string& dateDeNaissance)
{
	Patient::setDateDeNaissance(dateDeNaissance);
    Etudiant::setDateDeNaissance(dateDeNaissance);
}

//! Méthode qui permet de mettre à jour le taux de rabais du patient étudiant
//! \param tauxRabais le taux de rabais appliqué au patient étudiant
void PatientEtudiant::setTauxRabais(const double tauxRabais)
{
	tauxRabais_ = tauxRabais;
}