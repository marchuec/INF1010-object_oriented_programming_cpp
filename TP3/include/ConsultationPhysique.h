#ifndef CONSULTATIONPHYSIQUE_H
#define CONSULTATIONPHYSIQUE_H

#include <string>
#include "Consultation.h"

class ConsultationPhysique : public Consultation
{
    public:
        ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date, 
                             const std::string& prescription);

        const std::string& getPrescription() const;
        void setPrescription(const std::string& prescription);
        
        const double calculerPrix() const override;

    private:
        std::string prescription_;
};

#endif // CONSULTATIONPHYSIQUE_H