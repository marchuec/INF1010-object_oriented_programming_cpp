/****************************************************************
* \class  MedecinResident
* \brief  Contient l'information sur un médecin résident
*
* \author Marc-Antoine Huet et François Dubois-Roy
* \date   07/08/2020
****************************************************************/

#include <iostream>
#include <string>
#include "../include/MedecinResident.h"

//! Constructeur par paramètres de la classe MedecinResident qui hérite de Medecin et Etudiant
//! \param nom              Le nom du médecin
//! \param id               L'identificant du médecin résident
//! \param specialite       La spécialité du médecin résident
//! \param dateDeNaissance  La date de naissance du médecin résident
//! \param matricule        Le matricule du médecin résident
//! \param etablissement    L'établissement du médecin résident
MedecinResident::MedecinResident(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, 
                    const std::string& etablissement, const std::string& id, 
                    Specialite specialite)
    : Medecin::Medecin(nom, id, specialite), 
      Etudiant::Etudiant(nom, dateDeNaissance, matricule, etablissement)
{
}

//! Méthode qui affiche les informations du médecin résident
//! \param stream Le stream dans lequel afficher l'information
void MedecinResident::afficher(std::ostream& stream) const
{
    Medecin::afficher(stream);
    stream << "\n\t";
    Etudiant::afficher(stream);
}


//! Méthode qui retourne le salaire annuel du médecin résident
//! \return le salaire du médecin résident
double MedecinResident::getSalaireAnnuel() const 
{
    return SALAIRE_DE_BASE_MEDECIN_RESIDENT + nombreConsultations_ * getPrixConsultation();
}
