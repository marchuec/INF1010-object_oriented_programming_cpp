/****************************************************************
* \class  ConsultationPhysique
* \brief  Contient l'information sur une consultation physique
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include "../include/ConsultationPhysique.h"
#include "../include/PatientEtudiant.h"

//! Constructeur par paramètres de la classe ConsultationPhysique
//! \param prescription La prescription d'une consultation physique
ConsultationPhysique::ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date, 
                                           const std::string& prescription = "Pas de prescription")
    : Consultation(medecin, patient, date)
{
}

//! Méthode qui retourne le prix de la consultation du médecin
//! \return Le prix de la consultation
const double ConsultationPhysique::calculerPrix() const
{
    double prix = medecin_->getPrixConsultation();
    if (dynamic_cast<PatientEtudiant*>(patient_))
    {
        prix -= dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais();
    }
    return prix;
}

//! Méthode qui retourne la prescription
//! \return prescription_ La prescription
const std::string& ConsultationPhysique::getPrescription() const
{
    return prescription_;
}

//! Méthode qui permet de modifier la prescription
//! \param prescription La prescription 
void ConsultationPhysique::setPrescription(const std::string& prescription)
{
    prescription_ = prescription;
}
