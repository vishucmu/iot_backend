//
//  FrameworkController.hpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/11/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#ifndef FrameworkController_hpp
#define FrameworkController_hpp

#include "../Common/CommonIncludes.h"
#include "../Model/FrameworkModel.hpp"

class FrameworkController
{
private:
    FrameworkModel& m_model;
    
public:
    FrameworkController(FrameworkModel& inModel);
    FrameworkModel& GetModel();
    void CalculateLikelihoodAndImpact();
    void CalculateControlScores();
    void CalculateResidualRisks();
    void CalculateCumulativeWeights();
    void ListLikelihoodAndImpact();
    ~FrameworkController();
};

#endif /* FrameworkController_hpp */
