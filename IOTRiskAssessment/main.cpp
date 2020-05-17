//
//  main.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/11/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include <iostream>
#include "../Controller/FrameworkController.hpp"
#include "../Model/FrameworkModel.hpp"
#include "../Utils/MappingUtility.hpp"

int main(int argc, const char * argv[])
{   
    FrameworkModel  m_model;
    FrameworkController m_controller(m_model);
   
    // cout << "Reading all the mappings in the system" << endl;
    m_model.ReadMapsFromFile();
    
    // cout << endl << "Mappings are loaded. Calculating likelihood and impact now" << endl;
    
    m_controller.CalculateCumulativeWeights();
    m_controller.CalculateLikelihoodAndImpact();
    m_controller.ListLikelihoodAndImpact();
    m_model.DoSensitivityAnalysis();
    
    return 0;
}