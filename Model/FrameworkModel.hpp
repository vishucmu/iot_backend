//
//  FrameworkModel.hpp
//  IOTRiskAssessment
//
//  Created by Siddhant Jain on 3/11/18.
//  Updated by Paul Griffioen on 6/26/18.
//  Copyright © 2018 Siddhant Jain. All rights reserved.
//

#ifndef FrameworkModel_hpp
#define FrameworkModel_hpp

#include "../Common/CommonIncludes.h"
#include "Vulnerability.hpp"
#include "Action.hpp"
#include "Asset.hpp"
#include "Property.hpp"
#include "Risk.hpp"
#include "Control.hpp"
#include "Device.hpp"

class FrameworkModel
{
private:
    std::unordered_map<std::string,Device> m_devices;
    std::unordered_map<std::string,Vulnerability> m_vulnerabilities;
    std::unordered_map<std::string,Action> m_actions;
    std::unordered_map<std::string,Asset> m_assets;
    std::unordered_map<std::string,Property> m_properties;
    std::unordered_map<std::string,Risk> m_risk;
    std::unordered_map<std::string,Control> m_controls;
    
    std::unordered_map<std::string,vector<std::string>> m_vulnerability2Action;
    std::unordered_map<std::string,vector<std::string>> m_action2Asset;
    std::unordered_map<std::string,vector<std::string>> m_vulnerability2Property;
    std::unordered_map<std::string,vector<std::string>> m_risk2Vulnerability;
    std::unordered_map<std::string,vector<std::string>> m_risk2Control;
    std::unordered_map<std::string,vector<std::string>> m_control2Vulnerability;
    std::unordered_map<std::string,vector<std::string>> m_device2Vulnerability;
    
    std::string m_parameterFileName;
    std::string m_deviceFileName;
    std::string m_vulnerabilityFileName;
    std::string m_actionFileName;
    std::string m_propertyFileName;
    std::string m_assetFileName;
    std::string m_riskFileName;
    std::string m_controlFileName;
    
    std::string m_d2vFileName;
    std::string m_v2aFileName;
    std::string m_v2pFileName;
    std::string m_a2aFileName;
    std::string m_r2vFileName;
    std::string m_r2cFileName;
    std::string m_c2vFileName;
    
    bool m_useDeviceWeights;
    double m_controlDelta;
    double m_assetMinScore;
    double m_assetMaxScore;
    double m_actionMinScore;
    double m_actionMaxScore;
    double m_vulnerabilityMinScore;
    double m_vulnerabilityMaxScore;
    double m_impactMinScore;
    double m_impactMaxScore;
    double m_deviceMinScore;
    double m_deviceMaxScore;
    double m_controlMinScore;
    double m_controlMaxScore;
    double m_controlEMinScore;
    double m_controlEMaxScore;
    double m_riskMinScore;
    double m_riskMaxScore;
    double m_modelResidualRisk;
    int m_numOfThreatActors;
    void CalculateActionAssetWeights();
    void CalculateVulnerabilityLikelihood();
    double UnionLikelihood(vector<double> weights);
    void CalculateVulnerabilityImpact();
    void CalculateVulnerabilityControlScores();
    double CalculateActionWeightFromLinkedAssets(int k,std::unordered_map<std::string,vector<std::string>> assetCategory2Asset);
    void DoOneVsAllSenstivityAnalysis();
    void ListControlsBySensitivityOrder();
    double CalculateFrameworkResidualRisk();
    double CalculateFrameworkInherentRisk();
    double CalculateFrameworkMaxInherentRisk();
    
    double normalizeRisk(float min, float max, float sum);
public:
    FrameworkModel();
    ~FrameworkModel();
    void PopulateModel();
    void PopulateDevices();
    void GetParameters();
    void PopulateVulnerabilities();
    void GetNumberOfThreatActors();
    void PopulateActions();
    void PopulateAssets();
    void PopulateProperties();
    void PopulateRisks();
    void PopulateControls();
    
    void UpdateVulnerabilityDeviceWeights();
    
    void ListVulnerabilities();
    void ListActions();
    std::unordered_map<std::string,Vulnerability>& GetVulnerabilities();
    void AddVul2ActionMapping(string vulID, string actionID);
    void AddAction2AssetMapping(string actionID, string assetID);
    void AddVul2PropertyMapping(string vulID, string propertyID);
    void AddRisk2VulMapping(string rID, string vulID);
    void AddRisk2ControlMapping(string rID, string controlID);
    void AddControl2VulnerabilityMapping(string cID, string vulID);
    void AddDevice2VulnerabilityMapping(string dID,string vulID);
    
    void WriteMapsToFile();
    void ReadMapsFromFile();
    void CalculateCumulativeWeights();
    void CalculateImpactsLikelihoodsAndRisks();
    void CalculateControlScores();
    void CalculateResidualRisks();
    void ListImpactsAndLikelihoods();
    void DoSensitivityAnalysis();
};

#endif /* FrameworkModel_hpp */
