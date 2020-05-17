//
//  Property.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/12/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include "Property.hpp"

Property::Property()
{
    //shouldn't be needing this constructor. Check what's happening here
}

Property::Property(std::string inID,std::string inName,std::string inHighLevel,std::string inLowLevel,double inWeight,double inWMin,double inWMax):
m_ID(inID),
m_name(inName),
m_highLevel(inHighLevel),
m_lowLevel(inLowLevel),
m_weight(inWeight),
m_wMin(inWMin),
m_wMax(inWMax)
{
    m_weight = m_weight-m_wMin;
    m_wMax = m_wMax - m_wMin;
}

string Property::GetName()
{
    return m_name;
}

double Property::GetWeight()
{
    return m_weight;
}

double Property::GetMaxWeight()
{
    return m_wMax;
}
