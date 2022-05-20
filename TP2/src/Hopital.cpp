/****************************************************************
* \class  Hopital
* \brief  Permet la gestion de l'hopital
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   22/07/2020
****************************************************************/

#include "Hopital.h"

//! Constructeur par paramètre  de la classe Hopital
//! \param nom      Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse)
	: nom_(nom), adresse_(adresse)
{
}

// TODO : chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients)
//! Méthode qui permet de charger les médecins et les patients depuis les fichiers passés en paramètres.
//! \param  nomFichierMedecins Nom du fichier contenant les médecins
//! \param  nomFichierpatients Nom du fichier contenant les patients
//! \return bool 			   True si l'opération a réussit, false sinon
bool Hopital::chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients)
{
	if (gestionnairePatients_.chargerDepuisFichier(nomFichierPatients) &&
		gestionnaireMedecins_.chargerDepuisFichier(nomFichierMedecins))
	{
		return true;
	}
	return false;
}	


// TODO : Operateur += qui permet d'ajouter une consultation à la liste consutltations_ 
//! Opérateur += qui ajoute une consultation à la liste de consultations
//! \param  consultation La consultation à ajouter
//! \return bool		 True si l'opération a réussit, false sinon
bool Hopital::operator+=(const Consultation& consultation)
{
	if (gestionnaireMedecins_.chercherMedecin(consultation.getMedecin()->getNumeroLicence()) != nullptr
		&& consultation.getMedecin()->getEstActif()
		&& gestionnairePatients_.chercherPatient(consultation.getPatient()->getNumeroAssuranceMaladie()) != nullptr)
	{
		consultations_.push_back(std::make_shared<Consultation>(consultation));
		return true;
	}
	return false;
}

// TODO : operater += qui ajoute un médecin au gestionnaire de médecins.
//! Opérateur qui ajoute un médecin au gestionnaire de médecins
//! \param  medecin Le médecin à ajouter
//! \return bool	True si l'opération a réussit, false sinon
bool Hopital::operator+=(const Medecin& medecin) { return gestionnaireMedecins_ += medecin; }


// TODO : operater += qui ajouté un pateint au gestionnaire de patient.
//! Opérateur qui ajoute un patient au gestionnaire de patients
//! \param  patient Le patient à ajouter
//! \return bool 	True si l'opération a réussit, false sinon
bool Hopital::operator+=(const Patient& patient) { return gestionnairePatients_ += patient; }


//! Méthode qui retourne le nom de l'hopital
//! \return le nom de l'hopital 
const std::string& Hopital::getNom() const
{
	return nom_;
}

//! Méthode qui retourne l'adresse de l'hopital
//! \return l'adresse de l'hopital 
const std::string& Hopital::getAdresse() const
{
	return adresse_;
}

//! Méthode qui retourne le gestionnaire des medecins
//! \return gestionnaire des medecins
GestionnaireMedecins& Hopital::getGestionnaireMedecins()
{
	return gestionnaireMedecins_;
}

//! Méthode qui retourne le gestionnaire des patients
//! \return gestionnaire des patients
GestionnairePatients& Hopital::getGestionnairePatients()
{
	return gestionnairePatients_;
}

// TODO : getConsultations() retourne une reference constante vers le vecteur consultation.
//! Méthode qui retourne une référence constante vers le vecteur consultation
//! \return vecteur consultations
const std::vector<std::shared_ptr<Consultation>>& Hopital::getConsultations() const
{
	return consultations_;
}

//! Méthode qui permet de mettre à jour le nom de l'hopital
//! \param nom Le nom de l'hopital
void Hopital::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour l'adresse de l'hopital
//! \param adresse  l'adresse de l'hopital
void Hopital::setAdresse(const std::string& adresse)
{
	adresse_ = adresse;
}
