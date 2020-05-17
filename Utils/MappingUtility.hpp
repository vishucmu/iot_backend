//
//  MappingUtility.hpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/12/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#ifndef MappingUtility_hpp
#define MappingUtility_hpp

#include "../Common/CommonIncludes.h"
#include "../Controller/FrameworkController.hpp"

class MappingUtility
{
public:
    MappingUtility(FrameworkController& inController);
    void MappingCreator();
    void MappingReader();
    void WriteMapsToFile();
private:
    
    void EditMapping(uint code);
    void EditVulnerabilityToAction();
    
    //TODO, ideally model and controller should be read-only here
    FrameworkController& m_controller;
    FrameworkModel& m_model;
};

#endif /* MappingUtility_hpp */
