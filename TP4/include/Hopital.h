#ifndef HOPITAL_H
#define HOPITAL_H

#include <string>
#include <vector>

#include "Consultation.h"
#include "GestionnairePersonnels.h"
#include "GestionnairePatients.h"

class Hopital
{
public:
    enum class TypeConsultation
    {
        first_ = -1,
        ConsultationEnLigne,
        ConsultationPhysique,
        last_
    };

    Hopital() = default;
    Hopital(const std::string& nom, const std::string& adresse);

    bool chargerBaseDeDonnees(const std::string& nomFichierPersonnels, const std::string& nomFichierPatients, const std::string& nomFichierConsultations);
    bool chargerDepuisFichierConsultation(const std::string& nomFichier);

    const double getAncienneteMoyenneDesPersonnels();

    std::vector<std::shared_ptr<Consultation>> getConsultationsEntreDates(const tm& date1, const tm& date2);

    template <typename T>
    bool ajouterConsultation(T& consultation);

    //! Méthode qui ajoute un patient au gestionnaire de personnels de l'hôpital
    //! \param personnel Le personnel à ajouter
    //! \return True si l'opération a réussit
    template <typename T>
    bool ajouterPersonnel(T& personnel)
    {
        return gestionnairePersonnels_.ajouterPersonnel<T>(personnel);
    }

    //! Méthode qui ajoute un patient au gestionnaire de patients de l'hôpital
    //! \param patient Le patient à ajouter
    //! \return True si l'opération a réussit
    template <typename T>
    bool ajouterPatient(T& patient)
    {
        return gestionnairePatients_.ajouterPatient<T>(patient);
    }

    const std::string& getNom() const;
    const std::string& getAdresse() const;
    GestionnairePersonnels& getGestionnairePersonnels();
    GestionnairePatients& getGestionnairePatients();
    const std::vector<std::shared_ptr<Consultation>>& getConsultations() const;

    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);

private:
    bool lireLigneConsultation(const std::string& ligne);

    std::string nom_;
    std::string adresse_;

    GestionnairePersonnels gestionnairePersonnels_;
    GestionnairePatients gestionnairePatients_;
    std::vector<std::shared_ptr<Consultation>> consultations_;
};

#endif // HOPITAL_H