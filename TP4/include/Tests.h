//! namespace Tests
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef TESTS_H
#define TESTS_H

#define TEST_GESTIONNAIRE_PATIENTS_ACTIF false
#define TEST_GESTIONNAIRE_PERSONNELS_ACTIF false
#define TEST_HOPITAL_ACTIF false
#define AFFICHER_QUESTION_BONUS false

namespace Tests
{
    void testAll();
    double testGestionnairePatients();
    double testGestionnairePersonnels();
    double testHopital();
    void afficherQuestionBonus();
} // namespace Tests

#endif // TESTS_H
