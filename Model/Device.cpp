//
//  Device.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/25/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include "Device.hpp"

Device::Device()
{
    //shouldn't be needing this constructor. Check what's happening here
}

Device::Device(std::string inID,std::string inName,std::string inClass,std::string inSubclass,double inWeight,double inWMin,double inWMax):
m_ID(inID),
m_name(inName),
m_class(inClass),
m_subclass(inSubclass),
m_weight(inWeight),
m_wMin(inWMin),
m_wMax(inWMax)
{
    m_weight = (m_weight-m_wMin)/(m_wMax - m_wMin);
}

string Device::GetName()
{
    return m_name;
}

double Device::GetWeight()
{
    return m_weight;
}
