//
//  Risk.hpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/15/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#ifndef Risk_hpp
#define Risk_hpp

#include "../Common/CommonIncludes.h"

class Risk
{
public:
    Risk();
    Risk(std::string inID,std::string inName,double inRiskMin,double inRiskMax);
    string GetName();
    void Setlikelihood(double inLikelihood);
    void SetImpact(double inImpact);
    void SetControlScore(double inControlScore);
    int GetNumberOfApplicableVulnerabilities();
    void SetNumberOfApplicableVulnerabilities(int inNumVul);
    double GetResidualRisk();
    double GetNormalisedResidualRisk();
    void SetResidualRisk(double inResidualRisk);
    double GetInherentRisk();
    double GetNormalisedInherentRisk();
    void SetInherentRisk(double inResidualRisk);
    double GetLikelihood();
    double GetImpact();
    double GetControlScore();
    void SetRiskTotal(double inRiskTotal);
private:
    std::string m_ID;
    std::string m_name;
    int m_numApplicableVulnerabilities;
    double m_likelihood;
    double m_impact;
    double m_controlScore;
    double m_residualRisk;
    double m_inherentRisk;
    
    double m_riskMin;
    double m_riskMax;
    double m_riskTotal;
};

#endif /* Risk_hpp */
