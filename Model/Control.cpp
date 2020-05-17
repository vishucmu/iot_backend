//
//  Control.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/25/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include "Control.hpp"

Control::Control()
{
    //shouldn't be needing this constructor. Check what's happening here
}

Control::Control(std::string inID,std::string inName,double inWeight,double inWMin,double inWMax,double inEffectiveness,double inEMin,double inEMax):
m_ID(inID),
m_name(inName),
m_weight(inWeight),
m_wMin(inWMin),
m_wMax(inWMax),
m_effectiveness(inEffectiveness),
m_eMin(inEMin),
m_eMax(inEMax)
{
    m_sensitivity = 0;
    m_weight = (m_weight-m_wMin)/(m_wMax - m_wMin);
    m_effectiveness = (m_effectiveness-m_eMin)/(m_eMax - m_eMin);
}

string Control::GetName()
{
    return m_name;
}

double Control::GetWeight()
{
    return m_weight;
}

double Control::GetOriginalWeight()
{
    return (m_weight*(m_wMax-m_wMin)) + m_wMin;
}

void Control::SetSensitivity(double inSensitivity)
{
    m_sensitivity = inSensitivity;
}

double Control::GetSensitivity()
{
    return m_sensitivity;
}

void Control::SetWeight(double inWeight)
{
    m_weight = inWeight;
}

void Control::SetApplicability(bool inIsApplicable)
{
    m_isApplicable = inIsApplicable;
}

bool Control::GetApplicability()
{
    return m_isApplicable;
}

double Control::GetEffectiveness()
{
    return m_effectiveness;
}

double Control::GetOriginalEffectiveness()
{
    return (m_effectiveness*(m_eMax-m_eMin)) + m_eMin;
}
