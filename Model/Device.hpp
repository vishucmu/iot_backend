//
//  Device.hpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/25/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#ifndef Device_hpp
#define Device_hpp

#include "../Common/CommonIncludes.h"
class Device
{
public:
    Device();
    Device(std::string inID,std::string inName,std::string inClass,std::string inSubclass,double inWeight,double inWMin,double inWMax);
    string GetName();
    double GetWeight();
private:
    std::string m_ID;
    std::string m_name;
    std::string m_class;
    std::string m_subclass;
    double m_weight;
    double m_wMax, m_wMin;
};

#endif /* Device_hpp */
