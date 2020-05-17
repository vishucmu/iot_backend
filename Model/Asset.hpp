//
//  Asset.hpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/12/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#ifndef Asset_hpp
#define Asset_hpp

#include "../Common/CommonIncludes.h"

class Asset
{
public:
    Asset();
    Asset(std::string inID,std::string inName,std::string inCategory,std::string inSubcategory,vector<double> inWeight,double inWMin,double inWMax);
    string GetName();
    double GetWeight(int i);
    string GetCategory();
private:
    std::string m_ID;
    std::string m_name;
    std::string m_category;
    std::string m_subcategory;
    vector<double> m_weight;
    double m_wMax, m_wMin;
};

#endif /* Asset_hpp */
