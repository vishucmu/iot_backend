//
//  Action.hpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/12/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#ifndef Action_hpp
#define Action_hpp

#include "../Common/CommonIncludes.h"

class Action
{
public:
    Action();
    Action(std::string inID,std::string inName,std::string inMechanism,std::string inCategory,vector<double> inWeight,double inWMin,double inWMax);
    std::string GetName();
    double GetWeight(int i);
    double GetAssetWeight(int i);
    void SetAssetWeight(int i, double inWeight);
private:
    std::string m_ID;
    std::string m_name;
    std::string m_mechanism;
    std::string m_category;
    vector<double> m_weight;
    //stores the weights of all the assets that map to this action.
    vector<double> m_assetWeight;
    
    double m_wMax, m_wMin;
};

#endif /* Action_hpp */
