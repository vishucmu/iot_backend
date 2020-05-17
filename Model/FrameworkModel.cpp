//
//  FrameworkModel.cpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/11/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#include "FrameworkModel.hpp"
#include <cassert> 

#include <unistd.h>
#include <algorithm>
#define GetCurrentDir getcwd

FrameworkModel::FrameworkModel()
{
    m_parameterFileName = "../Data/parameters.csv";
    m_deviceFileName = "../Data/devices.csv";
    m_vulnerabilityFileName = "../Data/vulnerabilities.csv";
    m_actionFileName = "../Data/actions.csv";
    m_assetFileName = "../Data/assets.csv";
    m_propertyFileName = "../Data/properties.csv";
    m_riskFileName =    "../Data/risks.csv";
    m_controlFileName = "../Data/controls.csv";
    m_v2aFileName = "../Data/v2aMap.csv";
    m_a2aFileName = "../Data/a2aMap.csv";
    m_v2pFileName = "../Data/v2pMap.csv";
    m_r2vFileName = "../Data/r2vMap.csv";
    m_r2cFileName = "../Data/r2cMap.csv";
    m_c2vFileName = "../Data/c2vMap.csv";
    m_d2vFileName = "../Data/d2vMap.csv";
    // m_parameterFileName = "../Test/parameters.csv";
    // m_deviceFileName = "../Test/devices.csv";
    // m_vulnerabilityFileName = "../Test/vulnerabilities.csv";
    // m_actionFileName = "../Test/actions.csv";
    // m_assetFileName = "../Test/assets.csv";
    // m_propertyFileName = "../Test/properties.csv";
    // m_riskFileName =    "../Test/risks.csv";
    // m_controlFileName = "../Test/controls.csv";
    // m_v2aFileName = "../Test/v2aMap.csv";
    // m_a2aFileName = "../Test/a2aMap.csv";
    // m_v2pFileName = "../Test/v2pMap.csv";
    // m_r2vFileName = "../Test/r2vMap.csv";
    // m_r2cFileName = "../Test/r2cMap.csv";
    // m_c2vFileName = "../Test/c2vMap.csv";
    // m_d2vFileName = "../Test/d2vMap.csv";
    
    //TODO: For now populating here, but may have to move this out as a separate function
    PopulateModel();
}

FrameworkModel::~FrameworkModel()
{

}

void FrameworkModel::PopulateModel()
{
    GetParameters();
    PopulateVulnerabilities();
    GetNumberOfThreatActors();
    PopulateActions();
    PopulateAssets();
    PopulateProperties();
    PopulateRisks();
    PopulateControls();
    PopulateDevices();
}

void FrameworkModel::GetParameters()
{
    //read file
    std::ifstream pFile(m_parameterFileName);
    if(!pFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening parameters file" << endl;
    }
    string name,minScore,maxScore;
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,'\n');
    m_useDeviceWeights = (bool) std::atof(minScore.c_str());
    cout << "Use device prevalency scores: " << std::atof(minScore.c_str()) << endl;
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,'\n');
    m_controlDelta = std::atof(minScore.c_str());
    cout << "Control sensitivity delta: " << m_controlDelta << endl;
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,',');
    std::getline(pFile,maxScore,'\n');
    m_assetMinScore = std::atof(minScore.c_str());
    m_assetMaxScore = std::atof(maxScore.c_str());
    cout << "Asset likelihood score range: " << m_assetMinScore << "-" << m_assetMaxScore << endl;
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,',');
    std::getline(pFile,maxScore,'\n');
    m_actionMinScore = std::atof(minScore.c_str());
    m_actionMaxScore = std::atof(maxScore.c_str());
    cout << "Action likelihood score range: " << m_actionMinScore << "-" << m_actionMaxScore << endl;
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,',');
    std::getline(pFile,maxScore,'\n');
    m_vulnerabilityMinScore = std::atof(minScore.c_str());
    m_vulnerabilityMaxScore = std::atof(maxScore.c_str());
    cout << "Vulnerability prevalency score range: " << m_vulnerabilityMinScore << "-" << m_vulnerabilityMaxScore << endl;
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,',');
    std::getline(pFile,maxScore,'\n');
    m_impactMinScore = std::atof(minScore.c_str());
    m_impactMaxScore = std::atof(maxScore.c_str());
    cout << "Impact score range: " << m_impactMinScore << "-" << m_impactMaxScore << endl;
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,',');
    std::getline(pFile,maxScore,'\n');
    m_deviceMinScore = std::atof(minScore.c_str());
    m_deviceMaxScore = std::atof(maxScore.c_str());
    cout << "Device prevalency score range: " << m_deviceMinScore << "-" << m_deviceMaxScore << endl;
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,',');
    std::getline(pFile,maxScore,'\n');
    m_controlMinScore = std::atof(minScore.c_str());
    m_controlMaxScore = std::atof(maxScore.c_str());
    cout << "Control implementation score range: " << m_controlMinScore << "-" << m_controlMaxScore << endl;
    m_controlDelta = m_controlDelta/(m_controlMaxScore - m_controlMinScore);
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,',');
    std::getline(pFile,maxScore,'\n');
    m_controlEMinScore = std::atof(minScore.c_str());
    m_controlEMaxScore = std::atof(maxScore.c_str());
    cout << "Control effectiveness score range: " << m_controlEMinScore << "-" << m_controlEMaxScore << endl;
    std::getline(pFile,name,',');
    std::getline(pFile,minScore,',');
    std::getline(pFile,maxScore,'\n');
    m_riskMinScore = std::atof(minScore.c_str());
    m_riskMaxScore = std::atof(maxScore.c_str());
    cout << "Risk score range: " << m_riskMinScore << "-" << m_riskMaxScore << endl;
}

void FrameworkModel::PopulateVulnerabilities()
{
    //read file
    //populate the vector
    std::ifstream vFile(m_vulnerabilityFileName);
    if(!vFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening vulnerability file" << endl;
    }
    //skipping the first line as it has headers
    string ID,name,layer,category,weight;
    
    std::getline(vFile,ID,',');
    std::getline(vFile,name,',');
    std::getline(vFile,layer,',');
    std::getline(vFile,category,',');
    std::getline(vFile,weight,'\n');
    
    while(vFile.good())
    {
        std::getline(vFile,ID,',');
        std::getline(vFile,name,',');
        std::getline(vFile,layer,',');
        std::getline(vFile,category,',');
        //TODO: This will be a nasty bug eventually. For now letting it be
        //Basically we need to figure out how to safely parse CSV files created in different platforms
        //On mac, it seems like the CSVs created end with \n
        std::getline(vFile,weight,'\n');
        
        Vulnerability vTemp(ID,name,layer,category,std::atof(weight.c_str()),m_useDeviceWeights,m_vulnerabilityMinScore,m_vulnerabilityMaxScore);
        m_vulnerabilities.insert(std::make_pair(ID, vTemp));
    }
    
    cout << "Total number of vulnerabilities read: " << m_vulnerabilities.size() << endl;
}

void FrameworkModel::GetNumberOfThreatActors()
{
    //read file
    std::ifstream aFile(m_assetFileName);
    if(!aFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening asset file" << endl;
    }
    //skipping the first 2 lines as they have headers
    string temp,commas;
    std::getline(aFile,temp,'\n');
    std::getline(aFile,temp,'\n');

    std::getline(aFile,temp,',');
    std::getline(aFile,temp,',');
    std::getline(aFile,temp,',');
    std::getline(aFile,temp,',');
    std::getline(aFile,commas,'\n');
    m_numOfThreatActors = std::count(commas.begin(),commas.end(),',')+1;

    cout << "Total number of threat actors read: " << m_numOfThreatActors << endl;
}

void FrameworkModel::PopulateActions()
{
    //read file
    //populate the vector
    std::ifstream aFile(m_actionFileName);
    if(!aFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening action file" << endl;
    }
    //skipping the first 2 lines as they have headers
    string altID,ID,name,mechanism,category,weight;
    vector<double> weightVec(m_numOfThreatActors);
    
    std::getline(aFile,ID,'\n');
    std::getline(aFile,ID,'\n');
    
    while(aFile.good())
    {
        std::getline(aFile,ID,',');
        std::getline(aFile,name,',');
        std::getline(aFile,mechanism,',');
        std::getline(aFile,category,',');
        //TODO: This will be a nasty bug eventually. For now letting it be
        //Basically we need to figure out how to safely parse CSV files created in different platforms
        //On mac, it seems like the CSVs created end with \n
        int i = 0;
        for(i=0;i<m_numOfThreatActors-1;i++)
        {
            std::getline(aFile,weight,',');
            weightVec[i] = std::atof(weight.c_str());
        }
        std::getline(aFile,weight,'\n');
        weightVec[i] = std::atof(weight.c_str());
        
        Action aTemp(ID,name,mechanism,category,weightVec,m_actionMinScore,m_actionMaxScore);
        m_actions[ID]  = aTemp;
    }
    
    cout << "Total number of actions read: " << m_actions.size() << endl;
}

void FrameworkModel::PopulateAssets()
{
    //read file
    //populate the vector
    std::ifstream aFile(m_assetFileName);
    if(!aFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening asset file" << endl;
    }
    //skipping the first 2 lines as they have headers
    string ID,name,category,subcategory,weight;
    vector<double> weightVec(m_numOfThreatActors);
    
    std::getline(aFile,ID,'\n');
    std::getline(aFile,ID,'\n');
    
    while(aFile.good())
    {
        std::getline(aFile,ID,',');
        std::getline(aFile,name,',');
        std::getline(aFile,category,',');
        std::getline(aFile,subcategory,',');
        //TODO: This will be a nasty bug eventually. For now letting it be
        //Basically we need to figure out how to safely parse CSV files created in different platforms
        //On mac, it seems like the CSVs created end with \n
        int i = 0;
        for(i=0;i<m_numOfThreatActors-1;i++)
        {
            std::getline(aFile,weight,',');
            weightVec[i] = std::atof(weight.c_str());
        }
        std::getline(aFile,weight,'\n');
        weightVec[i] = std::atof(weight.c_str());
        
        Asset aTemp(ID,name,category,subcategory,weightVec,m_assetMinScore,m_assetMaxScore);
        m_assets[ID]  = aTemp;
    }
    cout << "Total number of assets read: " << m_assets.size() << endl;
}

void FrameworkModel::PopulateProperties()
{
    //read file
    //populate the vector
    std::ifstream pFile(m_propertyFileName);
    if(!pFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening property file" << endl;
    }
    //skipping the first line as it has headers
    string ID,name,highLevel,lowLevel,weight;
    
    std::getline(pFile,ID,',');
    std::getline(pFile,name,',');
    std::getline(pFile,highLevel,',');
    std::getline(pFile,lowLevel,',');
    std::getline(pFile,weight,'\n');
    
    while(pFile.good())
    {
        std::getline(pFile,ID,',');
        std::getline(pFile,name,',');
        std::getline(pFile,highLevel,',');
        std::getline(pFile,lowLevel,',');
        //TODO: This will be a nasty bug eventually. For now letting it be
        //Basically we need to figure out how to safely parse CSV files created in different platforms
        //On mac, it seems like the CSVs created end with \n
        std::getline(pFile,weight,'\n');
        
        Property pTemp(ID,name,highLevel,lowLevel,std::atof(weight.c_str()),m_impactMinScore,m_impactMaxScore);
        m_properties[ID]  = pTemp;
    }
    
    cout << "Total number of properties read: " << m_properties.size() << endl;
    pFile.close();
}

void FrameworkModel::PopulateRisks()
{
    //read file
    //populate the vector
    std::ifstream rFile(m_riskFileName);
    if(!rFile.is_open())
    {
        //TODO: should throw an exception here!
        //cerr << "Error: " << strerror(errno);
        cout << "Error opening risk file" << endl;
    }
    //skipping the first line as it has headers
    string ID,name;
    
    std::getline(rFile,ID,',');
    std::getline(rFile,name,'\n');
    
    while(rFile.good())
    {
        std::getline(rFile,ID,',');
        std::getline(rFile,name,'\n');
        
        Risk rTemp(ID,name,m_riskMinScore,m_riskMaxScore);
        m_risk[ID]  = rTemp;
    }
    
    cout << "Total number of risks read: " << m_risk.size() << endl;
}

void FrameworkModel::PopulateControls()
{
    //read file
    //populate the vector
    std::ifstream cFile(m_controlFileName);
    if(!cFile.is_open())
    {
        //TODO: should throw an exception here!
        //cerr << "Error: " << std::strerror(errno);
        cout << "Error opening control file" << endl;
    }
    //skipping the first line as it has headers
    string ID,name,weight,effectiveness;
    
    std::getline(cFile,ID,',');
    std::getline(cFile,name,',');
    std::getline(cFile,weight,',');
    std::getline(cFile,effectiveness,'\n');
    
    while(cFile.good())
    {
        std::getline(cFile,ID,',');
        std::getline(cFile,name,',');
        std::getline(cFile,weight,',');
        std::getline(cFile,effectiveness,'\n');
        Control sTemp(ID,name,std::atof(weight.c_str()),m_controlMinScore,m_controlMaxScore,std::atof(effectiveness.c_str()),m_controlEMinScore,m_controlEMaxScore);
        m_controls[ID]  = sTemp;
    }
    
    cout << "Total number of controls read: " << m_controls.size() << endl;
}

void FrameworkModel::PopulateDevices()
{
    //read file
    //populate the vector
    std::ifstream dFile(m_deviceFileName);
    if(!dFile.is_open())
    {
        //TODO: should throw an exception here!
        //cerr << "Error: " << std::strerror(errno);
        cout << "Error opening device file" << endl;
    }
    //skipping the first line as it has headers
    string ID,name,dclass,dsubclass,weight;
    
    std::getline(dFile,ID,',');
    std::getline(dFile,name,',');
    std::getline(dFile,dclass,',');
    std::getline(dFile,dsubclass,',');
    std::getline(dFile,weight,'\n');
    
    while(dFile.good())
    {
        std::getline(dFile,ID,',');
        std::getline(dFile,name,',');
        std::getline(dFile,dclass,',');
        std::getline(dFile,dsubclass,',');
        std::getline(dFile,weight,'\n');
        
        Device dTemp(ID,name,dclass,dsubclass,std::atof(weight.c_str()),m_deviceMinScore,m_deviceMaxScore);
        m_devices[ID]  = dTemp;
    }
    
    cout << "Total number of devices read: " << m_devices.size() << endl;
}

void FrameworkModel::ListActions()
{
    unordered_map<string,Action>::iterator it = m_actions.begin();
    cout << "Total number of actions read: " << m_actions.size() << endl;
    while(it!=m_actions.end())
    {
        cout << it->second.GetName() << " Asset likelihood:";
        for(int i=0;i<m_numOfThreatActors;i++)
        {
            cout << " " << it->second.GetAssetWeight(i);
        }
        cout << endl;
        it++;
    }
}

void FrameworkModel::ListVulnerabilities()
{
    unordered_map<string,Vulnerability>::iterator it = m_vulnerabilities.begin();
    cout << "Total number of vulnerabilities read: " << m_vulnerabilities.size() << endl;
    while(it!=m_vulnerabilities.end())
    {
        cout << it->second.GetName() << " Inherent risk: " << it->second.GetInherentRisk() << " Vulnerability mitigation score: " << it->second.GetControlWeight() <<
        " Residual risk: " << it->second.GetResidualRisk() << endl;
        it++;
    }
        
}

std::unordered_map<std::string,Vulnerability>& FrameworkModel::GetVulnerabilities()
{
    return m_vulnerabilities;
}

void FrameworkModel::AddVul2ActionMapping(string vulID, string actionID)
{
    assert(m_actions.find(actionID)!=m_actions.end());
    assert(m_vulnerabilities.find(vulID)!=m_vulnerabilities.end());
    cout << "Adding a mapping from vulnerability: " << vulID << " to action: " << actionID << endl;
    m_vulnerability2Action[vulID].push_back(actionID);
}

void FrameworkModel::AddAction2AssetMapping(string actionID, string assetID)
{

    assert(m_actions.find(actionID)!=m_actions.end());
    assert(m_assets.find(assetID)!=m_assets.end());
    cout << "Adding a mapping from action: " << actionID << " to asset: " << assetID << endl;
    m_action2Asset[actionID].push_back(assetID);
}

void FrameworkModel::AddVul2PropertyMapping(string vulID, string propertyID)
{
    assert(m_vulnerabilities.find(vulID)!=m_vulnerabilities.end());
    assert(m_properties.find(propertyID)!=m_properties.end());
    cout << "Adding a mapping from vulnerability: " << vulID << " to property: " << propertyID << endl;
    m_vulnerability2Property[vulID].push_back(propertyID);
}

void FrameworkModel::AddRisk2VulMapping(string rID, string vulID)
{
    assert(m_vulnerabilities.find(vulID)!=m_vulnerabilities.end());
    assert(m_risk.find(rID)!=m_risk.end());
    cout << "Adding a mapping from risk: " << rID << " to vulnerability: " << vulID << endl;
    m_risk2Vulnerability[rID].push_back(vulID);
}

void FrameworkModel::AddRisk2ControlMapping(string rID, string controlID)
{
    assert(m_controls.find(controlID)!=m_controls.end());
    assert(m_risk.find(rID)!=m_risk.end());
    cout << "Adding a mapping from risk: " << rID << " to control: " << controlID << endl;
    m_risk2Control[rID].push_back(controlID);
}

void FrameworkModel::AddControl2VulnerabilityMapping(string controlID, string vulID)
{
    assert(m_controls.find(controlID)!=m_controls.end());
    assert(m_vulnerabilities.find(vulID)!=m_vulnerabilities.end());
    cout << "Adding a mapping from control: " << controlID << " to vulnerability: " << vulID << endl;
    m_control2Vulnerability[controlID].push_back(vulID);
}

void FrameworkModel::AddDevice2VulnerabilityMapping(string deviceID, string vulID)
{
    assert(m_devices.find(deviceID)!=m_devices.end());
    assert(m_vulnerabilities.find(vulID)!=m_vulnerabilities.end());
    cout << "Adding a mapping from device: " << deviceID << " to vulnerability: " << vulID << endl;
    m_device2Vulnerability[deviceID].push_back(vulID);
}

void FrameworkModel::WriteMapsToFile()
{
    //TODO: there is some error here. Fix it when time permits
    //writing V2A map
    ofstream V2AFile;
    V2AFile.open ("VulnerabilitiesToActions.csv");
    std::unordered_map<std::string,vector<std::string>>::iterator v2aIt = m_vulnerability2Action.begin();
    
    while(v2aIt!=m_vulnerability2Action.end())
    {
        string line="";
        line += m_vulnerabilities[v2aIt->first].GetName();
        line += ",";
        line += v2aIt->first;
        line += ",";
        
        vector<string> actions = v2aIt->second;
        for(int j=0;j<actions.size();j++)
        {
            line+=actions[j];
            line+=",";
        }
        line.pop_back();
        line+='\r';
        V2AFile << line;
        v2aIt++;
    }
    
    V2AFile.close();
}

//TODO: Refactor this class. Way too much redundant code

void FrameworkModel::UpdateVulnerabilityDeviceWeights()
{
    std::unordered_map<std::string,vector<std::string>>::iterator d2vIt = m_device2Vulnerability.begin();
    
    while(d2vIt!=m_device2Vulnerability.end())
    {
        vector<string> linkedVuls = d2vIt->second;
        
        vector<string>::iterator vulIt = linkedVuls.begin();
        
        
        cout << "updating vulnerability prevalency score: " << *vulIt << endl;
        while(vulIt!=linkedVuls.end())
        {
            assert(m_vulnerabilities.find(*vulIt)!=m_vulnerabilities.end());
            m_vulnerabilities[*vulIt].SetDeviceWeight( m_devices[d2vIt->first].GetWeight() ) ;
            vulIt++;
        }
        
       
        d2vIt++;
    }
    
    cout << "Vulnerability prevalency score updated: " << endl;
}

void FrameworkModel::ReadMapsFromFile()
{
    //Reading V2A Map
    std::ifstream v2aFile(m_v2aFileName);
    if(!v2aFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening vulnerabilities to assets file" << endl;
    }
    
    string headerID;
    string headerName;
    std::getline(v2aFile,headerID,',');
    std::getline(v2aFile,headerName,'\n');
    
    
    while(v2aFile.good())
    {
        string line;
        std::getline(v2aFile,line,'\n');
        stringstream lineSS(line);
        string vID;
        string vName;
        
        std::getline(lineSS,vID,',');
        std::getline(lineSS,vName,',');

        while(lineSS.good())
        {
            string actionID;
            getline(lineSS,actionID,',');
            //hacky fix for a row which has lesser number of columns than max number of columns
            if(actionID.empty())
                continue;
            cout << "vID: " << vID << " actionID: " << actionID << std::endl;
            AddVul2ActionMapping(vID,actionID);
        }
    }
    
    //Reading D2V Map
    std::ifstream d2vFile(m_d2vFileName);
    if(!d2vFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening devices to vulnerabilities file" << endl;
    }
    
    std::getline(d2vFile,headerID,',');
    std::getline(d2vFile,headerName,'\n');
    
    
    while(d2vFile.good())
    {
        string line;
        std::getline(d2vFile,line,'\n');
        std::getline(d2vFile,line,'\n');
        stringstream lineSS(line);
        string dID;
        string dName;
        
        std::getline(lineSS,dID,',');
        std::getline(lineSS,dName,',');
        
        while(lineSS.good())
        {
            string vulID;
            getline(lineSS,vulID,',');
            //hacky fix for a row which has lesser number of columns than max number of columns
            if(vulID.empty())
                continue;
            AddDevice2VulnerabilityMapping(dID, vulID);
        }
    }
    //Updating vulnerability weights, based on device weights
    if(m_useDeviceWeights)
    {
        UpdateVulnerabilityDeviceWeights();
    }
    //reading A2A map
    std::ifstream a2aFile(m_a2aFileName);
    if(!a2aFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening actions to assets file" << endl;
    }

    std::getline(a2aFile,headerID,',');
    std::getline(a2aFile,headerName,'\n');

    while(a2aFile.good())
    {
        string line;
        getline(a2aFile,line,'\n');
        cout << "Line read: " << line << std::endl;
        stringstream lineSS(line);
        string aID;
        string aName;
        
        
        std::getline(lineSS,aID,',');
        std::getline(lineSS,aName,',');
        
        while(lineSS)
        {
            string assetID;
            if(!getline(lineSS,assetID,',')){
                break;
            }
            //hacky fix for a row which has lesser number of columns than max number of columns
            if(assetID.empty()) {
                continue;
            }

            AddAction2AssetMapping(aID,assetID);
        }
    }
    
    //reading v2p map
    std::ifstream v2pFile(m_v2pFileName);
    if(!v2pFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening vulnerabilities to properties file" << endl;
    }

    std::getline(v2pFile,headerID,',');
    std::getline(v2pFile,headerName,'\n');

    while(v2pFile.good())
    {
        string line;
        getline(v2pFile,line,'\n');
        stringstream lineSS(line);
        string vID;
        string vName;
        
        std::getline(lineSS,vID,',');
        std::getline(lineSS,vName,',');
        while(lineSS.good())
        {
            string propertyID;
            getline(lineSS,propertyID,',');
            //hacky fix for a row which has lesser number of columns than max number of columns
            if(propertyID.empty())
                continue;
            AddVul2PropertyMapping(vID,propertyID);
        }
    }
    
    //reading risk to vulnerability map
    std::ifstream r2vFile(m_r2vFileName);
    if(!r2vFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening risks to vulnerabilities file" << endl;
    }

    std::getline(r2vFile,headerID,',');
    std::getline(r2vFile,headerName,'\n');

    while(r2vFile.good())
    {
        string line;
        getline(r2vFile,line,'\n');
        
        
        stringstream lineSS(line);
        string rID;
        string rName;
        std::getline(lineSS,rID,',');
        std::getline(lineSS,rName,',');
        while(lineSS.good())
        {
            string vulnerabilityID;
            getline(lineSS,vulnerabilityID,',');
            if(vulnerabilityID.length()==0)
                continue;
            AddRisk2VulMapping(rID,vulnerabilityID);
        }
    }
    
    //reading risk to control map
    std::ifstream r2cFile(m_r2cFileName);
    if(!r2cFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening risks to controls file" << endl;
    }

    std::getline(r2cFile,headerID,',');
    std::getline(r2cFile,headerName,'\n');

    while(r2cFile.good())
    {
        string line;
        getline(r2cFile,line,'\n');
        stringstream lineSS(line);
        string rID;
        string rName;
        std::getline(lineSS,rID,',');
        std::getline(lineSS,rName,',');
        while(lineSS.good())
        {
            string controlID;
            getline(lineSS,controlID,',');
            if(controlID.length()==0)
                continue;
            AddRisk2ControlMapping(rID,controlID);
        }
    }
    
    //reading control to vulnerability map
    std::ifstream c2vFile(m_c2vFileName);
    if(!c2vFile.is_open())
    {
        //TODO: should throw an exception here!
        cout << "Error opening controls to vulnerabilities file" << endl;
    }

    std::getline(c2vFile,headerID,',');
    std::getline(c2vFile,headerName,'\n');

    while(c2vFile.good())
    {
        string line;
        getline(c2vFile,line,'\n');
        stringstream lineSS(line);
        string controlID;
        string controlName;
        std::getline(lineSS,controlID,',');
        std::getline(lineSS,controlName,',');
        while(lineSS.good())
        {
            string vulID;
            getline(lineSS,vulID,',');
            if(vulID.length()==0)
                continue;
            AddControl2VulnerabilityMapping(controlID,vulID);
        }
    }
}

//Calculate the union of asset likelihoods for every action along with the union of action likelihoods associated with each vulnerability. Similarly, calculate the sum of property weights (impact score) for each vulnerability
void FrameworkModel::CalculateCumulativeWeights()
{
    ListVulnerabilities();
    CalculateActionAssetWeights();
    CalculateVulnerabilityLikelihood();
    CalculateVulnerabilityImpact();
}

//This function finds the union of likelihoods for each possible asset vector
double FrameworkModel::CalculateActionWeightFromLinkedAssets(int k,std::unordered_map<std::string,vector<std::string>> assetCategory2Asset)
{
    std::unordered_map<std::string,vector<std::string>>::iterator mapIt = assetCategory2Asset.begin();
    vector<double> groupAssetVector;
    double unionGroupAssetLikelihood;
    double vectorWeight = long(1.0);
    while(mapIt != assetCategory2Asset.end())
    {
        vector<std::string> groupAssets = mapIt->second;
        for(int i=0;i<groupAssets.size();i++)
        {
            groupAssetVector.push_back(m_assets[groupAssets[i]].GetWeight(k));
        }
        unionGroupAssetLikelihood = UnionLikelihood(groupAssetVector);
        vectorWeight += long(unionGroupAssetLikelihood);
        groupAssetVector.clear();
        mapIt++;
    }
    
    return vectorWeight; //exp(vectorWeight);
}

void FrameworkModel::CalculateActionAssetWeights()
{
    //Much easier way to do this: https://cs.stackexchange.com/questions/90368/algorithm-for-this-problem-on-generating-all-permutations?noredirect=1#comment195377_90368
    std::unordered_map<std::string,vector<std::string>>::iterator a2aIt = m_action2Asset.begin();
    
    while(a2aIt!=m_action2Asset.end())
    {
        std::unordered_map<std::string,vector<std::string>> assetCategory2Asset;
    
        vector<string> linkedAssets = a2aIt->second;
        vector<string>::iterator assetIt = linkedAssets.begin();
        
        while(assetIt!=linkedAssets.end())
        {
            cout << "assetIt: " << *assetIt << std::endl;
            Asset currentAsset = m_assets[*assetIt];
            
            if ( assetCategory2Asset.find(currentAsset.GetCategory()) == assetCategory2Asset.end() )
            {
                vector<string> assetsList;
                assetsList.push_back(*assetIt);
                assetCategory2Asset.insert(std::pair<std::string,vector<std::string>>(currentAsset.GetCategory(),assetsList));
            }
            else
            {
                assetCategory2Asset[currentAsset.GetCategory()].push_back(*assetIt);
            }
            assetIt++;
        }
        
        for(int i=0;i<m_numOfThreatActors;i++)
        {
            double ActionWeight = CalculateActionWeightFromLinkedAssets(i,assetCategory2Asset);
        
            m_actions[a2aIt->first].SetAssetWeight(i,ActionWeight);
        }
        a2aIt ++;
    }
    
  cout << "Action/asset likelihoods calculated" << endl;
}

void FrameworkModel::CalculateVulnerabilityLikelihood()
{
    std::unordered_map<std::string,vector<std::string>>::iterator v2aIt = m_vulnerability2Action.begin();
    vector<double> assetActionWeightVector;
    double unionAssetActionLikelihood;
    double unionThreatActorLikelihood;
    vector<double> threatActorVulnerabilityWeights;
    
    while(v2aIt!=m_vulnerability2Action.end())
    {
        vector<string> linkedActions = v2aIt->second;
        
        for(int i=0;i<m_numOfThreatActors;i++)
        {
            vector<string>::iterator actionIt = linkedActions.begin();
            
            cout << "Calculating likelihood for vulnerability: " << v2aIt->first << endl;
            while(actionIt!=linkedActions.end())
            {

                assetActionWeightVector.push_back(m_actions[*actionIt].GetWeight(i)*m_actions[*actionIt].GetAssetWeight(i));
                actionIt++;
            }
            unionAssetActionLikelihood = UnionLikelihood(assetActionWeightVector);
            threatActorVulnerabilityWeights.push_back(unionAssetActionLikelihood);
            assetActionWeightVector.clear();
        }
        unionThreatActorLikelihood = UnionLikelihood(threatActorVulnerabilityWeights);
        assert(m_vulnerabilities.find(v2aIt->first)!=m_vulnerabilities.end());
        m_vulnerabilities[v2aIt->first].SetLikelihood(unionThreatActorLikelihood);
        threatActorVulnerabilityWeights.clear();
        v2aIt++;
    }
    
    cout << "Vulnerability likelihoods calculated" << endl;
}

// Compute the union probability of likelihoods given in the vector
double FrameworkModel::UnionLikelihood(vector<double> weights)
{
    if(weights.size() > 1)
    {
        int i;
        int j;
        vector<double> leftWeights;
        vector<double> rightWeights;
        for(i=0;i<weights.size()/2;i++)
        {
            leftWeights.push_back(weights[i]);
        }
        for(j=i;j<weights.size();j++)
        {
            rightWeights.push_back(weights[j]);
        }
        double leftUnion = UnionLikelihood(leftWeights);
        double rightUnion = UnionLikelihood(rightWeights);
        return leftUnion+rightUnion-(leftUnion*rightUnion);
    }
    else
    {
        return weights[0];
    }
}

void FrameworkModel::CalculateVulnerabilityImpact()
{
    std::unordered_map<std::string,vector<std::string>>::iterator v2pIt = m_vulnerability2Property.begin();
    
    while(v2pIt!=m_vulnerability2Property.end())
    {
        vector<string> linkedProperties = v2pIt->second;
        
        vector<string>::iterator propertyIt = linkedProperties.begin();
        double cumulativeWeight = 0;
        double cumulativeMaxWeight = 0;
        while(propertyIt!=linkedProperties.end())
        {
            cumulativeWeight += m_properties[*propertyIt].GetWeight();
            cumulativeMaxWeight += m_properties[*propertyIt].GetMaxWeight();
            propertyIt++;
        }
        assert(m_vulnerabilities.find(v2pIt->first)!=m_vulnerabilities.end());

        m_vulnerabilities[v2pIt->first].SetImpact(cumulativeWeight);
        m_vulnerabilities[v2pIt->first].SetMaxImpact(cumulativeMaxWeight);
        v2pIt++;
    }
    cout << "Vulnerability impacts calculated" << endl;
}

void FrameworkModel::CalculateImpactsLikelihoodsAndRisks()
{

    CalculateControlScores();
    std::unordered_map<std::string,vector<std::string>>::iterator r2vIt = m_risk2Vulnerability.begin();

    ListVulnerabilities();
    cout << "********************";
    while(r2vIt!=m_risk2Vulnerability.end())
    {
        vector<string> linkedVulnerabilities = r2vIt->second;
        
        vector<string>::iterator vulnerabilityIt = linkedVulnerabilities.begin();
        double cumulativeLikelihood = 0;
        double cumulativeImpact = 0;
        double cumulativeInherentRisk=0;
        double cumulativeResidualRisk=0;
        int numApplicableVulnerabilities = 0;


        while(vulnerabilityIt!=linkedVulnerabilities.end())
        {
            assert(m_vulnerabilities.find(*vulnerabilityIt)!=m_vulnerabilities.end());
            if(m_vulnerabilities[*vulnerabilityIt].GetWeight()!=0)
            {
                numApplicableVulnerabilities++;
            }
            cumulativeLikelihood += m_vulnerabilities[*vulnerabilityIt].GetWeight()*m_vulnerabilities[*vulnerabilityIt].GetLikelihood();
            cumulativeImpact += m_vulnerabilities[*vulnerabilityIt].GetWeight()*m_vulnerabilities[*vulnerabilityIt].GetImpact();
            cumulativeInherentRisk += m_vulnerabilities[*vulnerabilityIt].GetWeight()*m_vulnerabilities[*vulnerabilityIt].GetInherentRisk();
            cumulativeResidualRisk += m_vulnerabilities[*vulnerabilityIt].GetWeight()*m_vulnerabilities[*vulnerabilityIt].GetResidualRisk();
            
            vulnerabilityIt++;
        }
        assert(m_risk.find(r2vIt->first)!=m_risk.end());
        m_risk[r2vIt->first].Setlikelihood(cumulativeLikelihood);
        m_risk[r2vIt->first].SetImpact(cumulativeImpact);
        m_risk[r2vIt->first].SetNumberOfApplicableVulnerabilities(numApplicableVulnerabilities);
        m_risk[r2vIt->first].SetInherentRisk(cumulativeInherentRisk);
        m_risk[r2vIt->first].SetResidualRisk(cumulativeResidualRisk);
        cout << "setting residual risk for : " <<  m_risk[r2vIt->first].GetName() << " as " << m_risk[r2vIt->first].GetResidualRisk();
        double totalInherentRisk = CalculateFrameworkMaxInherentRisk();
        m_risk[r2vIt->first].SetRiskTotal(totalInherentRisk);
        
        r2vIt++;
    }
    cout << "Risk likelihoods, impacts, and number of applicable vulnerabilities calculated" << endl;
}

void FrameworkModel::CalculateVulnerabilityControlScores()
{
    //Go through all the vulnerabilities associated with each control. If any vulnerability has non-zero weight, the control is applicable
    //Also, update vulnerability control scores
    
    std::unordered_map<std::string,vector<std::string>>::iterator c2vIt = m_control2Vulnerability.begin();
    
    while(c2vIt!=m_control2Vulnerability.end())
    {
        vector<string> linkedVulnerabilities = c2vIt->second;
        
        vector<string>::iterator vulnerabilityIt = linkedVulnerabilities.begin();
        
        
        while(vulnerabilityIt!=linkedVulnerabilities.end())
        {
            assert(m_vulnerabilities.find(*vulnerabilityIt)!=m_vulnerabilities.end());
            m_vulnerabilities[*vulnerabilityIt].AddControlWeight(m_controls[c2vIt->first].GetEffectiveness()*m_controls[c2vIt->first].GetWeight());
            
            if (m_vulnerabilities[*vulnerabilityIt].GetWeight() != 0)
            {
                assert(m_controls.find(c2vIt->first)!=m_controls.end());
                m_controls[c2vIt->first].SetApplicability(true);
            }
            vulnerabilityIt++;
        }
        c2vIt++;
    }
    cout << "Risk mitigation score for each control calculated" << endl;
}

void FrameworkModel::CalculateControlScores()
{
    CalculateVulnerabilityControlScores();
}

void FrameworkModel::ListImpactsAndLikelihoods()
{
    cout << "Listing all actions in the framework along with their calculated likelihood" << endl;
    // ListActions();
    cout << "Listing all vulnerabilities in the framework along with their calculated likelihood and impact" << endl;
    // ListVulnerabilities();
    cout << "Displaying the current likelihood and impact of each risk in the framework" << endl;
    std::unordered_map<std::string,Risk>::iterator riskIterator = m_risk.begin();
    
    std::ofstream csFile("../Results/CalculatedRisksPerDomain.csv");
    std::ofstream csFrameworkFile("../Results/CalculatedRisksFullFramework.csv");
    std::ofstream vulnerabilityFile("../Results/VulnerabilitiesLikelihoodImpact.csv");
    
    csFile << "Risk Domain,Inherent Risk,Residual Risk" << endl;
    while(riskIterator != m_risk.end())
    {
        Risk currRisk = riskIterator->second;
        cout << "\n\n ************ RESULT *************** \n\n";
        cout << "Risk: " << currRisk.GetName() << " | Inherent Risk: " << currRisk.GetNormalisedInherentRisk() << " | Residual Risk: " << currRisk.GetNormalisedResidualRisk() << endl;
        cout << "\n\n ************ RESULT *************** \n\n";
        
        csFile << currRisk.GetName() << "," << currRisk.GetNormalisedInherentRisk() << "," << currRisk.GetNormalisedResidualRisk() << endl;
        riskIterator ++;
    }
    
    double overallResidualRisk = CalculateFrameworkResidualRisk();
    double overallInherentRisk = CalculateFrameworkInherentRisk();

    csFrameworkFile << "Inherent Risk" << "," << overallInherentRisk << endl;
    csFrameworkFile << "Residual Risk" << "," << overallResidualRisk << endl;

    unordered_map<string,Vulnerability>::iterator it = m_vulnerabilities.begin();
    vulnerabilityFile << "Vulnerability,Likelihood,Impact" << endl;
    while(it!=m_vulnerabilities.end())
    {
        if(it->second.GetWeight()!=0)
        {
            vulnerabilityFile << it->second.GetName() << "," << it->second.GetLikelihood() << "," << it->second.GetImpact()/m_properties.size() << endl;
        }
        it++;
    }
}

void FrameworkModel::CalculateResidualRisks()
{
    std::unordered_map<std::string,Risk>::iterator riskIterator = m_risk.begin();
    
    while(riskIterator != m_risk.end())
    {
        Risk currRisk = riskIterator->second;
        double residualRisk = currRisk.GetControlScore()*currRisk.GetInherentRisk();
        assert(m_risk.find(riskIterator->first)!=m_risk.end());
        cout << "Setting residual risk for : " << m_risk[riskIterator->first].GetName() << " as: " << residualRisk << endl;
        m_risk[riskIterator->first].SetResidualRisk(residualRisk);
        riskIterator++;
    }
}

double FrameworkModel::CalculateFrameworkResidualRisk()
{
    //this is for senstivity analysis. Here we do not care about the risk to vulnerability mapping and only want to find out the weighted sum of the risks for all applicable vulnerabilities
    
    std::unordered_map<std::string,Vulnerability>::iterator vulnerabilityIt = m_vulnerabilities.begin();
    double cumulativeResidualRisk=0;

    while(vulnerabilityIt!=m_vulnerabilities.end())
    {
        assert(m_vulnerabilities.find(vulnerabilityIt->first)!=m_vulnerabilities.end());
        cumulativeResidualRisk += m_vulnerabilities[vulnerabilityIt->first].GetWeight()*m_vulnerabilities[vulnerabilityIt->first].GetResidualRisk();
        vulnerabilityIt++;
    }
    Risk rCumulativeResidual("000","CumulativeResidualRisk",m_riskMinScore,m_riskMaxScore);
    rCumulativeResidual.SetResidualRisk(cumulativeResidualRisk);
    double cumulativeMaxInherentRisk = CalculateFrameworkMaxInherentRisk();
    rCumulativeResidual.SetRiskTotal(cumulativeMaxInherentRisk);
    return rCumulativeResidual.GetNormalisedResidualRisk();
}

double FrameworkModel::CalculateFrameworkInherentRisk()
{
    //Here we do not care about the risk to vulnerability mapping and only want to find out the weighted sum of the inherent risks for all applicable vulnerabilities
    
    std::unordered_map<std::string,Vulnerability>::iterator vulnerabilityIt = m_vulnerabilities.begin();
    double cumulativeInherentRisk=0;
    
    while(vulnerabilityIt!=m_vulnerabilities.end())
    {
        assert(m_vulnerabilities.find(vulnerabilityIt->first)!=m_vulnerabilities.end());
        cumulativeInherentRisk += m_vulnerabilities[vulnerabilityIt->first].GetWeight()*m_vulnerabilities[vulnerabilityIt->first].GetInherentRisk();
        vulnerabilityIt++;
    }
    Risk rCumulativeInherent("00","CumulativeInherentRisk",m_riskMinScore,m_riskMaxScore);
    rCumulativeInherent.SetInherentRisk(cumulativeInherentRisk);
    double cumulativeMaxInherentRisk = CalculateFrameworkMaxInherentRisk();
    rCumulativeInherent.SetRiskTotal(cumulativeMaxInherentRisk);
    return rCumulativeInherent.GetNormalisedInherentRisk();
}

double FrameworkModel::CalculateFrameworkMaxInherentRisk()
{
    std::unordered_map<std::string,Vulnerability>::iterator vulnerabilityIt = m_vulnerabilities.begin();
    double cumulativeMaxInherentRisk=0;
    while(vulnerabilityIt!=m_vulnerabilities.end())
    {
        assert(m_vulnerabilities.find(vulnerabilityIt->first)!=m_vulnerabilities.end());
        cumulativeMaxInherentRisk += m_vulnerabilities[vulnerabilityIt->first].GetWeight()*m_vulnerabilities[vulnerabilityIt->first].GetMaxInherentRisk();
        vulnerabilityIt++;
    }
    return cumulativeMaxInherentRisk;
}

void FrameworkModel::DoSensitivityAnalysis()
{
    DoOneVsAllSenstivityAnalysis();
    ListControlsBySensitivityOrder();
    
}

void FrameworkModel::DoOneVsAllSenstivityAnalysis()
{
    //we will change each control score by a small delta, see the difference in framework risk due to that change and store all controls based on this
    
    cout << "Doing one vs all sensitivity analysis" << endl;
    std::unordered_map<std::string,Control>::iterator controlStartIt = m_controls.begin();
    std::unordered_map<std::string,Control>::iterator controlEndIt = m_controls.end();
    
    double frameworkResidualRisk = CalculateFrameworkResidualRisk();
    
    double baselineResidualRisk = frameworkResidualRisk;
    while(controlStartIt != controlEndIt)
    {
        double currentWeight = controlStartIt->second.GetWeight();
        currentWeight += m_controlDelta;
        controlStartIt->second.SetWeight(currentWeight);
        //clear vulnerability control weights
        unordered_map<string,Vulnerability>::iterator it = m_vulnerabilities.begin();
        while(it!=m_vulnerabilities.end())
        {
            it->second.ClearControlWeights();
            it++;
        }
        CalculateVulnerabilityControlScores();
        
        frameworkResidualRisk = CalculateFrameworkResidualRisk();
        double changeInResidualRisk = baselineResidualRisk - frameworkResidualRisk;
        double controlSensitivity = changeInResidualRisk;
        controlStartIt->second.SetSensitivity(controlSensitivity);
        currentWeight -= m_controlDelta;
        controlStartIt->second.SetWeight(currentWeight);
        controlStartIt++;
    }
}

struct greater_than_sensitivity
{
    inline bool operator() (Control& ctrl1, Control& ctrl2)
    {
        return (ctrl1.GetSensitivity() > ctrl2.GetSensitivity());
    }
};

void FrameworkModel::ListControlsBySensitivityOrder()
{
    //First listing/writing control sensitivites for the entire framework

    vector<Control> sortedControls;

    for(auto kv : m_controls) {
        sortedControls.push_back(kv.second);  
    }

    std::sort(sortedControls.begin(),sortedControls.end(),greater_than_sensitivity());

    std::ofstream csFile("../Results/ControlSensitivities.csv");


    csFile << "Control,Residual Risk Reduction,Control Implementation Score,Control Effectiveness Score" << endl;
    for(auto ctrl : sortedControls)
    {
        cout << "Control: " << ctrl.GetName() << " Residual risk reduction: " << ctrl.GetSensitivity() << endl;
        csFile << ctrl.GetName() << "," << ctrl.GetSensitivity() << "," << ctrl.GetOriginalWeight() << "," << ctrl.GetOriginalEffectiveness() << endl;
    }

    //Now we are writing sensitivities associated with each risk domain separately

    std::unordered_map<std::string,vector<std::string>>::iterator r2cIt = m_risk2Control.begin();
    
    for(auto risk : m_risk2Control)
    {
        vector<string> linkedControlIDs = risk.second;
        vector<Control> linkedControls;
        for(auto ctrl : linkedControlIDs)
        {
            linkedControls.push_back(m_controls[ctrl]);
        }
        
        std::sort(linkedControls.begin(),linkedControls.end(),greater_than_sensitivity());
        
        std::ofstream csFile("../Results/"+m_risk[risk.first].GetName()+" Control Sensitivities.csv");


        csFile << "Control,Residual Risk Reduction,Control Implementation Score,Control Effectiveness Score" << endl;
        for(auto ctrl : linkedControls)
        {
            cout << "Control: " << ctrl.GetName() << " Residual risk reduction: " << ctrl.GetSensitivity() << endl;
            csFile << ctrl.GetName() << "," << ctrl.GetSensitivity() << "," << ctrl.GetOriginalWeight() << "," << ctrl.GetOriginalEffectiveness() << endl;
        }
    }
}
