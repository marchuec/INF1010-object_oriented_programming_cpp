/****************************************************************
* \class  Personnel
* \brief  Contient les informations du personnel
*
* \author Marc-Antoine Huet
* \date   11/08/2020
****************************************************************/

#include "Personnel.h"
#include <iostream>
#include <typeinfo>

//! Constructeur par paramètres de la classe Personnel
//! \param nom 			Le nom du personnel
//! \param id 			L'identificant du personnel
//! \param dateAdhesion La date d'adhésion du personnel
Personnel::Personnel(const std::string& nom, const std::string& id, const tm& dateAdhesion) : nom_(nom), id_(id), dateAdhesion_(dateAdhesion)
{
}

//! Opérateur qui compare un string avec l'identifiant du personnel avec un personnel comme opérande de gauche
//! \param id L'identifiant  avec le quel on veut comparé le personnel
//! \return vrai si les identifiants sont identiques, faux sinon
bool Personnel::operator==(const std::string& id) const
{
	return (id_ == id);
}

//! Opérateur qui compare l'identifiant du personnel avec l'identifiant opérande de gauche.
//! \param id L'identifiant avec le quel on veut comparé le personnel
//! \param personnel le personnel avec lequel on compare  de l'identifiant
bool operator==(const std::string& id, const Personnel& personnel)
{
	return (id == personnel.id_);
}

//! Opérateur qui compare deux personnels par leur salaire annuel
//! \param personnel La référence vers le Personnel
bool Personnel::operator<(const Personnel& personnel)
{
	return getSalaireAnnuel() < personnel.getSalaireAnnuel();
}

//! Méthode qui affiche les informations d'un personnel de l'hopital
//! \param stream Le stream dans lequel afficher.
void Personnel::afficher(std::ostream& os) const
{
	std::string typePersonnel = typeid(*this).name();
	os << "Personnel: " << nom_
		<< "\n\tType: " << typePersonnel.substr(6, typePersonnel.length() - 6 + 1)
		<< "\n\tIdentifiant: " << id_
		<< "\n\tStatut: " << (estActif_ ? "Actif" : "Inactif");
}

//! Méthode qui retourne le nom du personnel
//! \return le nom du personnel 
const std::string& Personnel::getNom() const
{

	return nom_;
}


//! Méthode qui retourne l'identifiant du personnel
//! \return id_ l'identifiant du personnel
const std::string& Personnel::getId() const
{

	return id_;
}

//! Méthode qui retourne le status du personnel
//! \return estActif_ le status du personnel
bool Personnel::getEstActif() const
{

	return estActif_;
}

//! Méthode qui retourne la date d'adhésion du patient
//! \return dateDeNaissance_la date d'adhésion du patient
const tm& Personnel::getDateAdhesion() const
{
	return dateAdhesion_;
}

//! Méthode qui met a jours le nom  du personnel
//! \param nom Le nom du personnel
void Personnel::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui met a jours l'identifiant du personnel
//! \param  id  l'identifiant du personnel
void Personnel::setId(const std::string& id)
{
	id_ = id;
}

//! Méthode qui met a jours le statut du personnel s'il est actif ou non
//! \param boolean indiquant le nouveau status du personnel
void Personnel::setEstActif(bool estActif)
{
	estActif_ = estActif;
}

//! Méthode qui permet de mettre à jour la date d'adhésion du patient
//! \param dateAdhesion La date d'adhésion du patient
void Personnel::setDateAdhesion(const tm& dateAdhesion)
{
	dateAdhesion_ = dateAdhesion;
}
