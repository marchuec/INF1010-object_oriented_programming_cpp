/****************************************************************
* \class  Hopital
* \brief  Permet de gérer l'hôpital
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include "../include/Hopital.h"
#include "../include/ConsultationPhysique.h"

//! Constructeur par paramètre  de la classe Hopital
//! \param nom       Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse) : nom_(nom), adresse_(adresse)
{
}

//! Methode pour charger la base de donnees de l'hopital
//! \param nomFichierPersonnels  le nom du fichier qui contient les informations du personnel
//! \param adresse  nomFichierPatients le nom du fichier qui contient les informations des patients
bool Hopital::chargerBaseDeDonnees(const std::string& nomFichierPersonnels, const std::string& nomFichierPatients)
{
	return gestionnairePersonnels_.chargerDepuisFichier(nomFichierPersonnels)
		&& gestionnairePatients_.chargerDepuisFichier(nomFichierPatients);
}


//! Opérateur qui ajoute une consultation à un hopital
//! \param consultation à ajouter
//! \return Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(Consultation& consultation)
{	
	auto medecin = consultation.getMedecin();
	auto patient = consultation.getPatient();

	// Si le médecin existe, est actif et que le patient existe.
	if (gestionnairePersonnels_.chercherPersonnel(medecin->getId()) && medecin->getEstActif()
		&& gestionnairePatients_.chercherPatient(patient->getNumeroAssuranceMaladie()))
	{
		if (dynamic_cast<ConsultationPhysique*>(&consultation))
		{
			consultations_.push_back(std::make_shared<ConsultationPhysique>(*dynamic_cast<ConsultationPhysique*>(&consultation)));
		}
		else
		{
			consultations_.push_back(std::make_shared<ConsultationEnLigne>(*dynamic_cast<ConsultationEnLigne*>(&consultation)));
		}
		
		if (!medecin->chercherPatient(patient->getNumeroAssuranceMaladie()))    // Si le patient n'est pas associé au médecin
		{
			if (!(*medecin += patient)) {return false;}
		}

		medecin->incrementNombreConsultations();

		return true;
	}
	
	return false;
}


//! Operateur qui ajoute un médecin à un hopital
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(Personnel& personnel)
{
	return gestionnairePersonnels_ += &personnel;
}

//! Operateur qui ajoute un patient à un hopital
//! \param patient Le patient à ajouter
//! \return Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(Patient& patient)
{
	return gestionnairePatients_ += &patient;
}

//! Méthode qui retourne le nom de l'hopital
//! \return Le nom de l'hopital 
const std::string& Hopital::getNom() const
{
	return nom_;
}

//! Méthode qui retourne l'adresse de l'hopital
//! \return L'adresse de l'hopital 
const std::string& Hopital::getAdresse() const
{
	return adresse_;
}

//! Méthode qui retourne le gestionnaire du personnel
//! \return gestionnaire du personnel
GestionnairePersonnels& Hopital::getGestionnairePersonnels()
{
	return gestionnairePersonnels_;
}

//! Méthode qui retourne le gestionnaire des patients
//! \return gestionnaire des patients
GestionnairePatients& Hopital::getGestionnairePatients()
{
	return gestionnairePatients_;
}

//! Méthode qui retourne les consultations de l'hôpital
//! \return consultations_
const std::vector<std::shared_ptr<Consultation>>& Hopital::getConsultations() const
{
	return consultations_;
}

//! Méthode qui permet de mettre à jour le nom de l'hôpital
//! \Param nom Le nom de l'hopital
void Hopital::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour l'adresse de l'hôpital
//! \param adresse L'adresse de l'hopital
void Hopital::setAdresse(const std::string& adresse)
{
	adresse_ = adresse;
}

