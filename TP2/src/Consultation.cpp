/****************************************************************
* \class  Consultation
* \brief  Permet de gérer une consultation
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   22/07/2020
****************************************************************/

#include "Consultation.h"
#include <iostream>
#include <string>

// TODO : compléter Constructeur par paramètre de la classe Consulation en utilisant la liste d'initialisation
// Assurer d'ajouter le patient à la liste des patients assoicés au medecin s'il n'y existe pas.
//! Constructeur par paramètres
//! \param medecin Le médecin qui fait la consultation
//! \param patient Le patient consulté
//! \param date    La date de la consultation
Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date)
	: medecin_(new Medecin(medecin)), patient_(new Patient(patient)), date_(date)
{
	if (medecin.chercherPatient(patient.getNumeroAssuranceMaladie()) == nullptr)
	{
		medecin += patient;
	}
}

// TODO : operateur<< pour afficher les informations d'une consultation.
// Voir l'enoncé pour avoir un exemple d'affichage d'une consultation. 
// Si l'affichage n'est pas respecté, le test de l'affichage de consultation ne passera pas.
//! Opérateur << qui affiche les information de la consultation dans un stream
//! \param stream 		Le stream dans lequel afficher
//! \param consultation La consultation à afficher
std::ostream& operator<<(std::ostream& stream, const Consultation& consultation)
{
	stream << "\nConsultation: \n"
		   << "\t\tMedecin: " << consultation.medecin_->getNom() << "\n"
		   << "\t\t" << *consultation.patient_
		   << "\t\tDate de consultation: " << consultation.date_;

	return stream;
}

//! Méthode qui retourne le médecin de la consultation
//! \return Medecin*
Medecin* Consultation::getMedecin() const
{
	return medecin_;
}

//! Méthode qui retourne le patient de la consultation
//! \return Patient*
Patient* Consultation::getPatient() const
{
	return patient_;
}

//! Méthode qui retourne lea date de la consultation
//! \return const std::string
const std::string& Consultation::getDate() const
{
	return date_;
}
