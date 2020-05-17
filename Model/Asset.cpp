//
//  Asset.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/12/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include "Asset.hpp"

Asset::Asset()
{
    //shouldn't be needing this constructor. Check what's happening here
}

Asset::Asset(std::string inID,std::string inName,std::string inCategory,std::string inSubcategory,vector<double> inWeight,double inWMin,double inWMax):
m_ID(inID),
m_name(inName),
m_subcategory(inSubcategory),
m_category(inCategory),
m_weight(inWeight),
m_wMin(inWMin),
m_wMax(inWMax)
{
    for(int i=0;i<m_weight.size();i++)
    {
    	m_weight[i] = (m_weight[i]-m_wMin)/(m_wMax - m_wMin);
	}
}

string Asset::GetName()
{
    return m_name;
}

string Asset::GetCategory()
{
    return m_category;
}

double Asset::GetWeight(int i)
{
    return m_weight[i];
}
