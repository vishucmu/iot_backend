//
//  MappingUtility.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/12/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include "MappingUtility.hpp"

MappingUtility::MappingUtility(FrameworkController& inController):
m_controller(inController),
m_model(inController.GetModel())
{
    
}

void MappingUtility::MappingReader()
{
    cout << "We are going to read the maps from the files" << endl;
    m_model.ReadMapsFromFile();
}

void MappingUtility::MappingCreator()
{
    cout << "Welcome to mapping creator" << endl;
    cout << "Select a mapping to create: " << endl;
    cout << "1. Vulnerability to Action \t 2. Vulnerability to property \n 3. Action to asset " << endl;
    
    char ans;
    
    cin >> ans;
    
    EditMapping(ans-'0');
    WriteMapsToFile();
}

void MappingUtility::EditMapping(uint code)
{
    switch(code)
    {
        case 1:
            EditVulnerabilityToAction();
            break;
        default:
            break;
    }
}

void MappingUtility::EditVulnerabilityToAction()
{
    std::unordered_map<std::string,Vulnerability> vuls = m_model.GetVulnerabilities();
    
    std::unordered_map<std::string,Vulnerability>::iterator it = vuls.begin();
    cout << "For every vulnerability listed below enter an action it maps to. If you are done, enter -1" << endl;
    for(;it!=vuls.end();it++)
    {
        int assetNumber;
        cout << it->second.GetName() << endl;
        cin >> assetNumber;
        m_model.AddVul2ActionMapping(it->first, "");
        while(assetNumber!=-1)
        {
            m_model.AddVul2ActionMapping(it->first, to_string(assetNumber));
            cout << "Mapped asset \t Enter another asset to be mapped" << endl;
            cin >> assetNumber;
        }
    }
}

void MappingUtility::WriteMapsToFile()
{
    m_model.WriteMapsToFile();
}
