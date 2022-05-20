/****************************************************************
* \class  ConsultationEnLigne
* \brief  Contient l'information sur une consultation en ligne
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include "../include/ConsultationEnLigne.h"

//! Constructeur par paramètres de la classe ConsultationEnLigne
//! \param diagnostic Le diagnostic de la consultation en ligne
//! \param rabaisConsultationEnLigne Le rabais appliqué à une consultation en ligne
ConsultationEnLigne::ConsultationEnLigne(Medecin& medecin, Patient& patient, const std::string& date,
                                         const std::string& diagnostic = "Aucune diagnostic")
    : Consultation(medecin, patient, date), rabaisConsultationEnLigne_(TAUX_RABAIS_CONSULTATION_ENLIGNE)
{
}

//! Méthode qui retourne le prix de la consultation du médecin
//! \return Le prix de la consultation
const double ConsultationEnLigne::calculerPrix() const
{
    double prix = medecin_->getPrixConsultation();
    // Rabais étudiant
    if (dynamic_cast<PatientEtudiant*>(patient_))
    {
        prix *= (1-dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais());
    }
    // Rabais pour la consultation en ligne
    prix *= (1-rabaisConsultationEnLigne_);
    return prix;
}


//! Méthode qui retourne le diagnostic de la consultation
//! \return diagnostic_ Le diagnostic
const std::string& ConsultationEnLigne::getDiagnostic() const
{
    return diagnostic_;
}

//! Méthode qui retourne le rabais de la consultation
//! \return Le rabais
const double ConsultationEnLigne::getRabaisConsultationEnLigne() const
{
    return rabaisConsultationEnLigne_;
}

//! Méthode qui permet de modifier le diagnostic
//! \param diagnostic Le diagnostic
void ConsultationEnLigne::setDiagnostic(std::string& diagnostic)
{
    diagnostic_ = diagnostic;
}