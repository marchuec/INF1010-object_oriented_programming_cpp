/****************************************************************
* \class  Foncteurs
* \brief  Foncteurs personnalisés du programme
*
* \author Marc-Antoine Huet
* \date   11/08/2020
****************************************************************/

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include <memory>
#include <utility>

// Ajouts
#include "Personnel.h"
#include "utils.h"
#include "Consultation.h"

//! \class ComparateurSecondElementPaire
//! Foncteur prédicat binaire qui compare les seconds éléments de paires pour déterminer si elles sont en ordre
//! \param paire1 La première paire
//! \param paire2 La deuxième paire
//! \return True si le second élément de la première paire est strictement inférieur au second élément de la deuxième paire, sinon false
template <typename T1, typename T2>
class ComparateurSecondElementPaire
{
public:
    ComparateurSecondElementPaire() = default;
    bool operator() (std::pair<T1, T2>& paireInferieure, std::pair<T1, T2>& paireSuperieure)
    {
        return *paireInferieure.second < *paireSuperieure.second;
    }

};

//! \class ComparateurEstEgalAvecId
//! Foncteur prédicat unaire servant à comparer un objet avec un id de type string
//! \param id       L'identifiant auquel comparer
//! \param objet    Objet avec lequel comparer l'id
//! \return True si l'id correspond, false sinon
template <typename T>
class ComparateurEstEgalAvecId
{
public:
    ComparateurEstEgalAvecId(const std::string& id) : id_(id) {};

    bool operator() (const std::shared_ptr<T> objet)
    {
        return (*objet == id_);
    }

private:
    const std::string id_;
};

//! \class AccumulateurPeriodePersonnel
//! Foncteur qui se charge de l'ajout de la période passée par les personnels à l'hôpital à une somme
//! \param somme La somme initiale
//! \param paire Une paire de string et de shared_ptr de Personnel
//! \return La somme du paramètre somme et de l'ancienneté du personnel passé en paramètre
class AccumulateurPeriodePersonnel
{
public:
    double operator() (double somme, const std::pair<const std::string, std::shared_ptr<Personnel>>& paire)
    {
        return somme + (getDateCourante().tm_year - paire.second->getDateAdhesion().tm_year);
    }
};

//! \class ComparateurTypePatient
//! Foncteur prédicat servant à comparer un objet de type Patient à un objet d'un autre type
//! \param patient Le patient à comparer
//! \return True si le patient est du même type que l'objet
template <typename T>
class ComparateurTypePatient
{
public:
    bool operator() (const std::shared_ptr<Patient> patient)
    {
        if (dynamic_cast<T*>(patient.get()))
        {
            return true;
        }
        return false;
    }
};

//! \class EstDansIntervalleDatesConsultation
//! Foncteur prédicat servant à déterminer si une consultation est réalisée entre deux dates
//! \param patient Le patient à comparer
//! \return True si l'objet est de type Patient et false sinon.
class EstDansIntervalleDatesConsultation
{
public:
    EstDansIntervalleDatesConsultation(const tm& dateInferieure, const tm& dateSuperieure) : dateInferieure_(dateInferieure), dateSuperieure_(dateSuperieure) {};

    bool operator() (const std::shared_ptr<Consultation>& consultation)
    {
        tm dateConsultation = convertirStringDate(consultation->getDate());
        return (comparerDate(dateConsultation, dateInferieure_) && comparerDate(dateSuperieure_, dateConsultation));
    }

private:
    tm dateInferieure_;
    tm dateSuperieure_;
};

#endif // FONCTEURS_H
