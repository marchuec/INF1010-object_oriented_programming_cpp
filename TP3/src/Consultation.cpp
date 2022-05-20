/****************************************************************
* \class  Consultation
* \brief  Contient l'information sur une consultation
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include "../include/Consultation.h"
#include <iostream>
#include <string>
#include "../include/utils.h"

//! Constructeur par paramètres de la classe abstraite Consultation
//! \param medecin Le medecin responsable de la consultation
//! \param patient Le patient qui demande une consultation
//! \param date    La date de la consultation
Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date) :
	medecin_(&medecin), patient_(&patient), date_(date), prix_(PRIX_DE_BASE)
{
}

Classe:Classe(params):
	attribut1_(medecin)

//! Méthode qui affiche les informations d'une consultation
//! \param os Le stream dans lequel afficher
void Consultation::afficher(std::ostream& os) const
{
	std::string typeConsultation = typeid(*this).name();
	std::string typeMedecin = typeid(*medecin_).name(); 
	std::string typePatient = typeid(*patient_).name();
	filtrerType(typeConsultation); 
	filtrerType(typeMedecin); 
	filtrerType(typePatient);

	os << "Consultation: "
		<< "\n\tType: " << typeConsultation 			
		<< "\n\t\t" 	<< typeMedecin 		<< ": " << medecin_->getId() 
		<< "\n\t\t" 	<< typePatient 		<< ": " << patient_->getNumeroAssuranceMaladie()
		<< "\n\t\t" 	<< "Date de consultation: " << date_;
}

//! Méthode qui retourne le médecin de la consultation
//! \return medecin_ le pointeur vers le médecin de la consultation
Medecin* Consultation::getMedecin() const
{
	return medecin_;
}

//! Méthode qui retourne le patient de la consultation
//! \return patient_ le pointeur vers le patient de la consultation
Patient* Consultation::getPatient() const
{
	return patient_;
}

//! Méthode qui retourne la date de la consultation
//! \return date_ la date de la consultation
const std::string& Consultation::getDate() const
{
	return date_;
}
