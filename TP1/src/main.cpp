//! Fonction main qui test le programme
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 07 Mai 2020

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include "Patient.h"
#include "debogageMemoire.h"
#include "GestionnairePatients.h"
#include "Medecin.h"
#include "GestionnaireMedecins.h"
#include "typesafe_enum.h"

// Je n'ai pas été en mesure de faire fonctionner complètement le compilateur
// et j'ai du ajouter ces liens manuellement pour que ça fonctionne. Je vais
// trouver la solution pour le prochain TP
#include "Patient.cpp"
#include "Medecin.cpp"
#include "GestionnairePatients.cpp"
#include "GestionnaireMedecins.cpp"

// NOTE: Pour que le programme compile, vous pouvez changer tous les #if true à des #if false,
// et mettre en commentaire tout le code qui a été écrit pour vous. Ainsi, vous pourrez
// graduellement les #if true et tester des petits blocs de code à la fois. Commencez par
// écrire vos constructeurs!

int main()
{

	initDebogageMemoire();

	GestionnaireMedecins gestionnaireMedecins;
	GestionnairePatients gestionnairePatients;

	std::vector<bool> tests;

#if true
	// Test 1 et 2: Lecture des fichiers et affichage.
	// Assurez-vous de mettre les fichiers à la bonne place pour que
	// le programme puisse les trouver.
	// Chaque fichier se fait charger deux fois, mais le résultat devrait
	// être le même que si chaque fichier se faisait charger une fois.
	// N'oubliez pas de reset les variables nécessaires dans vos méthodes
	// pour que le double chargement ne change rien!

	// Si vous rencontrez des problèmes ici, comparez votre sortie de console
	// à celle de l'énoncé.
	bool resultatLecturePatients = gestionnairePatients.chargerDepuisFichier("patients.txt") &&
		gestionnairePatients.chargerDepuisFichier("patients.txt");

	bool resultatLectureMedecins = gestionnaireMedecins.chargerDepuisFichier("medecins.txt") &&
		gestionnaireMedecins.chargerDepuisFichier("medecins.txt");

	// Test 1: Affichage des patients
	std::stringstream patientsStream;
	gestionnairePatients.afficher(patientsStream);
	std::string patientsString = patientsStream.str();
	std::cout << patientsString << '\n'; // Affichage dans la console
	const std::string sortieAttenduePatients =
		"Patient:JohnLourdes|Datedenaissance:12/12/2001|Numerod'assurancemaladie:louj010304"
		"Patient:GeorgeLucas|Datedenaissance:01/04/1944|Numerod'assurancemaladie:LUCG441212";

	patientsString.erase(
		std::remove_if(patientsString.begin(), patientsString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		patientsString.end());

	tests.push_back(sortieAttenduePatients == patientsString && resultatLecturePatients == true &&
		gestionnairePatients.getNbPatients() == 2);

	// Test 2: Affichage des médecins
	std::stringstream medecinsStream;
	gestionnaireMedecins.afficher(medecinsStream);
	std::string medecinsString = medecinsStream.str();
	std::cout << medecinsString << '\n'; // Affichage dans la console


	const std::string sortieAttendueMedecins =
		"Medecin:LourdesJohnNumerodelicence:tt1234Specialite:CardiologueStatut:ActifAucunpatientn'estsuiviparcemedecin."
		"Medecin:GeorgeLucasNumerodelicence:hhjue2Specialite:DermatologueStatut:ActifAucunpatientn'estsuiviparcemedecin.";

	medecinsString.erase(
		std::remove_if(medecinsString.begin(), medecinsString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		medecinsString.end());

	tests.push_back(sortieAttendueMedecins == medecinsString && resultatLectureMedecins == true &&
		gestionnaireMedecins.getNbMedecins() == 2);


#else
	tests.push_back(false);
	tests.push_back(false);
#endif

#if true
	// Test 3: Fonction d'ajout des patients
	bool test3Reussi = true;
	// Remplir le tableau des patients
	for (auto i = gestionnairePatients.getNbPatients(); i < GestionnairePatients::NB_PATIENT_MAX; i++)
	{
		Patient patient = Patient("Patient" + std::to_string(i), "12/12/2001", "SETT121201" + std::to_string(i));
		bool succes = gestionnairePatients.ajouterPatient(patient);
		if (succes == false)
		{
			test3Reussi = false;
			tests.push_back(false);
			break;
		}
	}
	// Ajouter un autre patient devrait retourner false puisque le tableau est plein
	if (test3Reussi == true)
	{
		bool succes = gestionnairePatients.ajouterPatient(Patient("", "", ""));
		tests.push_back(!succes);
	}
#else
	tests.push_back(false);
#endif


#if true
	// Test 4: Fonction recherche patient dans gestionnairePatients
	std::shared_ptr<Patient> patient = gestionnairePatients.chercherPatient("louj010304");
	std::shared_ptr<Patient>  patientInexistant = gestionnairePatients.chercherPatient("qwerty");
	if (patient == nullptr || patientInexistant != nullptr)
		tests.push_back(false);
	else
		tests.push_back(patient->getDateDeNaissance() == "12/12/2001");
#else
	tests.push_back(false);
#endif

#if true
	// Test 5: Fonction d'ajout de medecin
	bool test5Reussi = true;
	// Remplir le tableau des medecins
	for (auto i = gestionnaireMedecins.getNbMedecins(); i < gestionnaireMedecins.getCapaciteMedecins(); i++)
	{
		std::size_t tailleAvantAjout = gestionnaireMedecins.getNbMedecins();

		std::unique_ptr<Medecin> medecin = std::make_unique<Medecin>("Medecin" + std::to_string(i), "LOU1258" + std::to_string(i), to_enum<Medecin::Specialite, int>(i % 6));
		gestionnaireMedecins.ajouterMedecin(std::move(medecin));

		std::size_t tailleApresAjout = gestionnaireMedecins.getNbMedecins();

		if (tailleApresAjout != tailleAvantAjout + 1)
		{
			test5Reussi = false;
			tests.push_back(false);
			break;
		}
	}
	// Ajouter un autre medecin deverait doubler la capacite
	if (test5Reussi == true)
	{
		gestionnaireMedecins.ajouterMedecin(std::make_unique<Medecin>(Medecin("", "", to_enum<Medecin::Specialite, int>(1))));

		tests.push_back(gestionnaireMedecins.getCapaciteMedecins() == 4);
	}
#else
	tests.push_back(false);
#endif

#if true
	// Test 6: Fonction recherche Medecin
	std::shared_ptr<Medecin> medecin = gestionnaireMedecins.chercherMedecin("tt1234");
	std::shared_ptr<Medecin> medecinInexistant = gestionnaireMedecins.chercherMedecin("qwerty");
	if (medecin == nullptr || patientInexistant != nullptr)
		tests.push_back(false);
	else
		tests.push_back(medecin->getNom() == "Lourdes John");
#else
	tests.push_back(false);
#endif

#if true
	// Test 7: Fonction supprimer medecin
	bool medecinEstSupprime = gestionnaireMedecins.supprimerMedecin("tt1234");
	bool medecinNonSupprime = gestionnaireMedecins.supprimerMedecin("qwerty");
/*
	if (!medecinEstSupprime || medecinNonSupprime)
		tests.push_back(false);
	else
	{
		medecin = gestionnaireMedecins.chercherMedecin("tt1234");
		tests.push_back(medecin != nullptr && !medecin->getEstActif());
	}
*/
#else
	tests.push_back(false);
#endif

#if false
	// Test 8: Fonction ajouter patient dans Medecin
	bool test8Reussi = true;
	Medecin medecinTest = Medecin("Robert Trembley", "ROB1234", to_enum<Medecin::Specialite, int>(1));
	// Remplir le tableau des patients associes au medecin
	for (auto i = medecinTest.getNombrePatientsAssocies(); i < medecinTest.getCapacitePatientAssocies(); i++)
	{
		std::size_t tailleAvantAjout = medecinTest.getNombrePatientsAssocies();

		Patient patient2 = Patient("Patient" + std::to_string(i), "12/12/2001", "SETT121201" + std::to_string(i));
		medecinTest.ajouterPatient(patient2);

		std::size_t tailleApresAjout = medecinTest.getNombrePatientsAssocies();

		if (tailleApresAjout != tailleAvantAjout + 1)
		{
			test8Reussi = false;
			tests.push_back(false);
			break;
		}
	}
	// Ajouter un autre patient deverait doubler la capacite
	if (test8Reussi == true)
	{
		medecinTest.ajouterPatient(Patient("Patient2", "12/12/2001", "SETT1212012"));
		tests.push_back(medecinTest.getCapacitePatientAssocies() == 4);
	}

	// Test 9: Affichage d'un medecin avec patients associes
	std::stringstream medecinStream;
	medecinTest.afficher(medecinStream);
	std::string medecinString = medecinStream.str();
	std::cout << medecinString << '\n'; // Affichage dans la console
	const std::string sortieAttenduMedecin =
		"Medecin:RobertTrembleyNumerodelicence:ROB1234Specialite:CardiologueStatut:ActifPatientsassocies:"
		"Patient:Patient0|Datedenaissance:12/12/2001|Numerod'assurancemaladie:SETT1212010"
		"Patient:Patient1|Datedenaissance:12/12/2001|Numerod'assurancemaladie:SETT1212011"
		"Patient:Patient2|Datedenaissance:12/12/2001|Numerod'assurancemaladie:SETT1212012";

	medecinString.erase(
		std::remove_if(medecinString.begin(), medecinString.end(),
			[](unsigned char c) { return std::isspace(c); }),
		medecinString.end());

	tests.push_back(sortieAttenduMedecin == medecinString && medecinTest.getNombrePatientsAssocies() == 3);

	// Test 10: Supprimer un patient associe a un medecin
	bool estSupprime1 = medecinTest.supprimerPatient("SETT1212011");
	bool estSupprime2 = medecinTest.supprimerPatient("SETT1212012");
	bool estSupprime3 = medecinTest.supprimerPatient("qwerty");

	tests.push_back(estSupprime1 && estSupprime2 && !estSupprime3 && medecinTest.getNombrePatientsAssocies() == 1);
#else
	tests.push_back(false);
#endif

	std::vector<float> ponderationTests = { 0.5, 0.5, 1, 0.5, 1, 0.5, 0.5, 1, 1, 1.5 };

	// Affichage
	float totalPoints = 0;
	for (std::size_t i = 0; i < tests.size(); i++)
	{
		std::string output = "Test " + std::to_string(i + 1) + ": ";
		if (tests[i] == true)
		{
			output += "OK!";
			std::stringstream stream;
			stream << ponderationTests[i] << '/' << ponderationTests[i];
			std::cout << std::left << std::setw(15) << std::left << output << stream.str() << '\n';
			totalPoints += ponderationTests[i];
		}
		else
		{
			output += "ECHEC!";
			std::stringstream stream;
			stream << '0' << '/' << ponderationTests[i];
			std::cerr << std::left << std::setw(15) << output << "0/" << ponderationTests[i] << '\n';
		}
	}
	std::stringstream stream;
	stream << totalPoints << "/"
		<< std::accumulate(ponderationTests.begin(), ponderationTests.end(), 0.0f);
	std::cout << std::left << std::setw(16) << "TOTAL: " << stream.str() << '\n';
}
