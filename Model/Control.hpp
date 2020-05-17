//
//  Control.hpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/25/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#ifndef Control_hpp
#define Control_hpp

#include "../Common/CommonIncludes.h"
class Control
{
public:
    Control();
    Control(std::string inID,std::string inName,double weight,double inWMin,double inWMax,double inEffectiveness,double inEMin,double inEMax);
    string GetName();
    double GetWeight();
    double GetOriginalWeight();
    void SetWeight(double inWeight);
    double GetSensitivity();
    void SetSensitivity(double inWeight);
    void SetApplicability(bool inIsApplicable);
    bool GetApplicability();
    double GetEffectiveness();
    double GetOriginalEffectiveness();
private:
    std::string m_ID;
    std::string m_name;
    double m_weight;
    double m_wMax, m_wMin;
    bool m_isApplicable;
    double m_sensitivity;
    double m_effectiveness;
    double m_eMax, m_eMin;
};

#endif /* Control_hpp */
