//
//  Action.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/12/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include "Action.hpp"

Action::Action()
{
    //shouldn't be needing this constructor. Check what's happening here
}

Action::Action(std::string inID,std::string inName,std::string inMechanism,std::string inCategory,vector<double> inWeight,double inWMin,double inWMax):
m_ID(inID),
m_name(inName),
m_mechanism(inMechanism),
m_category(inCategory),
m_weight(inWeight),
m_wMin(inWMin),
m_wMax(inWMax)
{
    for(int i=0;i<m_weight.size();i++)
    {
        m_assetWeight.push_back(0.0);
        m_weight[i] = (m_weight[i]-m_wMin)/(m_wMax - m_wMin);
    }

}

std::string Action::GetName()
{
    return m_name;
}

void Action::SetAssetWeight(int i, double inWeight)
{
    m_assetWeight[i] = inWeight;
}

double Action::GetWeight(int i)
{
    return m_weight[i];
}

double Action::GetAssetWeight(int i)
{
    return m_assetWeight[i];
}
