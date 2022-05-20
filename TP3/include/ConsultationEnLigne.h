#ifndef CONSULTATIONENLIGNE_H
#define CONSULTATIONENLIGNE_H

#include <string>
#include "Consultation.h"

class ConsultationEnLigne : public Consultation
{
    public:
        ConsultationEnLigne(Medecin& medecin, Patient& patient, const std::string& date, 
                            const std::string& diagnostic);

        const std::string& getDiagnostic() const;
        const double getRabaisConsultationEnLigne() const;

        const double calculerPrix() const override;

        void setDiagnostic(std::string& diagnostic);
        
    private:
        static constexpr double TAUX_RABAIS_CONSULTATION_ENLIGNE = 0.5;

        std::string diagnostic_;
        double rabaisConsultationEnLigne_;
};


#endif // CONSULTATIONENLIGNE_H