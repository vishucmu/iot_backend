//
//  Risk.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/15/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include "Risk.hpp"

Risk::Risk()
{
    //shouldn't be needing this constructor. Check what's happening here
}

Risk::Risk(std::string inID,std::string inName,double inRiskMin,double inRiskMax):
m_ID(inID),
m_name(inName),
m_riskMin(inRiskMin),
m_riskMax(inRiskMax)
{
    m_likelihood = 0;
    m_impact = 0;
    m_residualRisk = 0.0;
    m_inherentRisk = 0.0;
    m_riskTotal = 1;
}

string Risk::GetName()
{
    return m_name;
}

void Risk::Setlikelihood(double inLikelihood)
{
    m_likelihood = inLikelihood;
}

void Risk::SetImpact(double inImpact)
{
    m_impact = inImpact;
}

double Risk::GetLikelihood()
{
    return m_likelihood;
}

double Risk::GetImpact()
{
    return m_impact;
}

void Risk::SetNumberOfApplicableVulnerabilities(int inNumVul)
{
    m_numApplicableVulnerabilities = inNumVul;
}

int Risk::GetNumberOfApplicableVulnerabilities()
{
    return m_numApplicableVulnerabilities;
}

void Risk::SetRiskTotal(double inRiskTotal)
{
    m_riskTotal = inRiskTotal;
}

void Risk::SetResidualRisk(double inResidualRiskVal)
{
    m_residualRisk = inResidualRiskVal;
}

double Risk::GetResidualRisk()
{
    return m_residualRisk;
}

double Risk::GetNormalisedResidualRisk()
{
    double normalisedRisk = (m_residualRisk/m_riskTotal)*(m_riskMax - m_riskMin) + m_riskMin;
    return normalisedRisk;
}

void Risk::SetInherentRisk(double inInherentRiskVal)
{
    m_inherentRisk = inInherentRiskVal;
}

double Risk::GetInherentRisk()
{
    return m_inherentRisk;
}

double Risk::GetNormalisedInherentRisk()
{
    double normalisedRisk = (m_inherentRisk/m_riskTotal)*(m_riskMax - m_riskMin) + m_riskMin;
    return normalisedRisk;
}

double Risk::GetControlScore()
{
    return m_controlScore;
}

void Risk::SetControlScore(double inControlScore)
{
    m_controlScore = inControlScore;
}
