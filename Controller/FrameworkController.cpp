//
//  FrameworkController.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/11/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include "FrameworkController.hpp"

FrameworkController::FrameworkController(FrameworkModel &inModel):
m_model(inModel)
{
	
}

FrameworkController::~FrameworkController()
{

}

FrameworkModel& FrameworkController::GetModel()
{
    return m_model;
}

void FrameworkController::CalculateCumulativeWeights()
{
    m_model.CalculateCumulativeWeights();
}

void FrameworkController::CalculateLikelihoodAndImpact()
{
    m_model.CalculateImpactsLikelihoodsAndRisks();
}

void FrameworkController::ListLikelihoodAndImpact()
{
    m_model.ListImpactsAndLikelihoods();
}

void FrameworkController::CalculateControlScores()
{
    m_model.CalculateControlScores();
}

void FrameworkController::CalculateResidualRisks()
{
    m_model.CalculateResidualRisks();
}
