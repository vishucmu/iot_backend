//
//  Property.hpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/12/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#ifndef Property_hpp
#define Property_hpp

#include "../Common/CommonIncludes.h"

class Property
{
public:
    Property();
    Property(std::string inID,std::string inName,std::string inHighLevel,std::string inLowLevel,double inWeight,double inWMin,double inWMax);
    string GetName();
    double GetWeight();
    double GetMaxWeight();
private:
    std::string m_ID;
    std::string m_name;
    std::string m_highLevel;
    std::string m_lowLevel;
    double m_weight;
    double m_wMax, m_wMin;
};

#endif /* Property_hpp */
