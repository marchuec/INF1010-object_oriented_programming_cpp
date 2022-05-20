/****************************************************************
* \class  Personnel
* \brief  Contient l'information sur un personnel de l'hôpital
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include "../include/Personnel.h"
#include <iostream>
#include <typeinfo>

//! Constructeur par paramètre de la classe de base Personnel
//! \param nom Nom du personnel
//! \param id  L'identifiant du personnel
Personnel::Personnel(const std::string& nom, const std::string& id) : nom_(nom), id_(id)
{
}

//! Opérateur qui compare un string avec l'identifiant du personnel avec un personnel comme opérande de gauche
//! \param id  L'identifiant  avec le quel on veut comparé le personnel
//! \return vrai si  Les identifiants sont identiques, faux sinon
bool Personnel::operator==(const std::string& id) const
{
	return (id_ == id);
}

//! Opérateur qui compare l'identifiant du personnel avec l'identifiant opérande de gauche.
//! \param id 		 l'identifiant avec le quel on veut comparé le personnel
//! \param personnel le personne avec lequel on compare  de l'identifiant
//! \return vrai si  Les identifiants sont identiques, faux sinon
bool operator==(const std::string& id, const Personnel& personnel)
{
	return (id == personnel.id_);
}

//! Méthode qui affiche les informations du personnel
//! \param stream Le stream dans lequel afficher
void Personnel::afficher(std::ostream& stream) const
{
	std::string typePersonnel = typeid(*this).name();
	filtrerType(typePersonnel);
		                        
	stream << "Personnel: " 		<< nom_ 			
		   << "\n\tType: " 			<< typePersonnel 	
		   << "\n\tIdentifiant: " 	<< id_ 		
		   << "\n\tStatut: " 		<< (estActif_ ? "Actif" : "Inactif");
}

//! Méthode qui retourne le nom du personnel
//! \return nom_ le nom du personnel 
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
//! \return bool le status du personnel
bool Personnel::getEstActif() const
{
	return estActif_;
}

//! Méthode qui met a jours le nom  du personnel
//! \param nom  Le nom du personnel
void Personnel::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui met a jours l'identifiant du personnel
//! \param id  l'identifiant du personnel
void Personnel::setId(const std::string& id)
{
	id_ = id;
}

//! Méthode qui met a jours le statut  du personnel s' il est actif ou non
//! \param boolean indiquant le  nouveau status du personnel
void Personnel::setEstActif(bool estActif)
{
	estActif_ = estActif;
}
