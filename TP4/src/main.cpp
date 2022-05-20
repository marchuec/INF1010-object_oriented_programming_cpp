//! Fonction main
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 07 Mai 2020

#include <iostream>
#include "Tests.h"
#include "WindowsUnicodeConsole.h"

//Je dois ajouter ça sinon VisualStudio Code ne réussit pas à linker les fichiers...
//En temps normal je ne devrais pas avoir à les inclure.
#include "Etudiant.cpp"
#include "Patient.cpp"
#include "PatientEtudiant.cpp"
#include "Personnel.cpp"
#include "Medecin.cpp"
#include "MedecinResident.cpp"
#include "GestionnairePatients.cpp"
#include "GestionnairePersonnels.cpp"
#include "Consultation.cpp"
#include "ConsultationEnligne.cpp"
#include "ConsultationPhysique.cpp"
#include "Hopital.cpp"
#include "Tests.cpp"

int main()
{
    initializeConsole();
    Tests::testAll();
}
