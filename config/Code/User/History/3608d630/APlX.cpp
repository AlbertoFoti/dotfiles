#include "MissionScenario.hxx"
#include <iostream>
#include <fstream>
#include "LoadFromFile.hxx"
#include "Log.hxx"

using json = nlohmann::json;

MissionScenario::MissionScenario(const std::string& scenario_name) {
    if(this->loadScenario(scenario_name) == false) {
        Log::spacing(); Log::spacing();
        exit(1);
    }
}

MissionScenario::~MissionScenario() {}

bool MissionScenario::loadScenario(const std::string& scenario_name) {
    bool scenario_found {false};

    // Load from Config folder
    std::string filename = "./Config/" + scenario_name + "/mission.json";
    std::ifstream file(filename);
    if (!file.is_open()) {
        Log::err("MS", "Scenario Loading Error. Failed to open file %s", filename.c_str());
        return false;
    }

    json jsonData;
    try {
        file >> jsonData;
    } catch (json::parse_error& e) {
        Log::err("MS", "Scenario Loading Error. Failed to parse json structure.");
        return false;
    }

    if (jsonData.empty()) {
        Log::err("MS", "Scenario Loading Error. Empty json data.");
        return false;
    } 

    // Access JSON values
    this->scenario_name = jsonData["name"];

    // Load all other mission configs
    
    // >> Montecarlo Simulation
    if(!loadConfigFile(scenario_name, "MCSimParsNSF", [&](const nlohmann::json& jsonData) {
        this->MCSimParsNSF.kMonInit = jsonData["kMonInit"]["Value"];
        this->MCSimParsNSF.NmonOrg = jsonData["NmonOrg"]["Value"];
        this->MCSimParsNSF.decimation = jsonData["decimation"]["Value"];
        this->MCSimParsNSF.decimation_th = jsonData["decimationTh"]["Value"];
        this->MCSimParsNSF.SmartTriggF = jsonData["SmartTriggF"]["Value"];
        this->MCSimParsNSF.PulsedF = jsonData["PulsedF"]["Value"];
        this->MCSimParsNSF.MCFlag = jsonData["MCFlag"]["Value"];
    })) { return false; };

    // >> Mission
    if(!loadConfigFile(scenario_name, "NominalMissionNSF", [&](const nlohmann::json& jsonData) {
        this->NominalMissionNSF.GravIDNom     = jsonData["GravIDNom"]["Value"];
        this->NominalMissionNSF.massNom       = jsonData["massNom"]["Value"];
        this->NominalMissionNSF.rCelBodyNom   = jsonData["rCelBodyNom"]["Value"];
        this->NominalMissionNSF.SrefNom       = jsonData["SrefNom"]["Value"];
        this->NominalMissionNSF.LrefNom       = jsonData["LrefNom"]["Value"];
        this->NominalMissionNSF.omgCelBodyNom = jsonData["omgCelBodyNom"]["Value"];
        this->NominalMissionNSF.MmaxNom       = jsonData["MmaxNom"]["Value"];
        this->NominalMissionNSF.JNom          = jsonData["JNom"]["Value"];
        this->NominalMissionNSF.khfNom        = jsonData["khfNom"]["Value"];

        this->NominalMissionNSF.aMax = NominalMissionNSF.MmaxNom / NominalMissionNSF.JNom;
        this->NominalMissionNSF.parNom = {
            NominalMissionNSF.massNom,
            NominalMissionNSF.rCelBodyNom,
            NominalMissionNSF.SrefNom,
            NominalMissionNSF.omgCelBodyNom
        };

        this->NominalMissionNSF.NbrOrg        = jsonData["NbrOrg"]["Value"];
        this->NominalMissionNSF.tBrVNomOrg = {
            jsonData["tBr1Nom"]["Value"],
            jsonData["tBr2Nom"]["Value"],
            jsonData["tBr3Nom"]["Value"],
            jsonData["tBr4Nom"]["Value"],
            jsonData["tBr5Nom"]["Value"],
            jsonData["tBr6Nom"]["Value"],
            jsonData["tBr7Nom"]["Value"],
            jsonData["tBr8Nom"]["Value"]
        };

        this->NominalMissionNSF.tPDPNom = jsonData["tPDPNom"]["Value"];
        this->NominalMissionNSF.ugNom   = jsonData["ugNom"]["Value"];

        for(unsigned int i=0; i<this->NominalMissionNSF.NbrOrg; i++) {
            if(this->NominalMissionNSF.tBrVNomOrg.at(i) < this->NominalMissionNSF.tPDPNom) {
                this->NominalMissionNSF.tBrVNom.push_back(this->NominalMissionNSF.tBrVNomOrg.at(i));
                this->NominalMissionNSF.NbrNom += 1;
            }
        }
    })) { return false; };

    // >> Control Time Unit
    if(!loadConfigFile(scenario_name, "TimeStepsNSF", [&](const nlohmann::json& jsonData) {
        this->TimeStepsNSF.Tgui = jsonData["Tgui"]["Value"];
        this->TimeStepsNSF.Tatt = jsonData["Tatt"]["Value"];
        this->TimeStepsNSF.Tnav = jsonData["Tnav"]["Value"];
        this->TimeStepsNSF.TCoM = jsonData["TCoM"]["Value"];
        this->TimeStepsNSF.Ts = jsonData["Ts"]["Value"];
    })) { return false; };

    // >> Guidance Pars
    if(!loadConfigFile(scenario_name, "DRAppParsNSF", [&](const nlohmann::json& jsonData) {
        this->DRAppParsNSF.gravDR = jsonData["gravDR"]["Value"];
        this->DRAppParsNSF.cDDR = jsonData["cDDR"]["Value"];
        this->DRAppParsNSF.cLDR = jsonData["cLDR"]["Value"];
        this->DRAppParsNSF.rhosDR = jsonData["rhosDR"]["Value"];
        this->DRAppParsNSF.HatmDR = jsonData["HatmDR"]["Value"];
    })) { return false; };

    // >> Nominal Mission values
    if(!loadConfigFile(scenario_name+"/InitialState", "CoMNomX0NSF", [&](const nlohmann::json& jsonData) {
        this->CoMNomX0NSF.r0Nom = jsonData["r0Nom"]["Initial value"];
        this->CoMNomX0NSF.lon0Nom = jsonData["lon0Nom"]["Initial value"];
        this->CoMNomX0NSF.lat0Nom = jsonData["lat0Nom"]["Initial value"];
        this->CoMNomX0NSF.vAbs0Nom = jsonData["vAbs0Nom"]["Initial value"];
        this->CoMNomX0NSF.fpa0Nom = jsonData["fpa0Nom"]["Initial value"];
        this->CoMNomX0NSF.head0Nom = jsonData["head0Nom"]["Initial value"];
        
        this->CoMNomX0NSF.xCoMNomEIP = {
            CoMNomX0NSF.r0Nom,
            CoMNomX0NSF.lon0Nom,
            CoMNomX0NSF.lat0Nom,
            CoMNomX0NSF.vAbs0Nom,
            CoMNomX0NSF.fpa0Nom,
            CoMNomX0NSF.head0Nom
        };
    })) { return false; };

    // >> Control Pars ==================================== 
    
    // Load 'CoMControlParsNSF'
    Log::warn("MS", "Loading Control pars: CoMControlParsNSF...");

    // Load 'InputVariablesControlNSF'
    Log::warn("MS", "Loading Control pars: InputVariablesControlNSF...");

    // --------------END CONTROL PARS LOADING--------------

    // >> SimEDL ==========================================

    // SimEDL
    if(!loadConfigFile(scenario_name + "/SimEDL", "SimEDLParsNSF", [&](const nlohmann::json& jsonData) {
        this->edl.SimEDLParsNSF.xaCoM = jsonData["xaCoM"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.yaCoM = jsonData["yaCoM"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.zaCoM = jsonData["zaCoM"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.xIMUbSim = jsonData["xIMUbSim"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.yIMUbSim = jsonData["yIMUbSim"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.zIMUbSim = jsonData["zIMUbSim"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.mass = jsonData["mass"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.Jxx = jsonData["Jxx"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.Jyy = jsonData["Jyy"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.Jzz = jsonData["Jzz"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.Jxy = jsonData["Jxy"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.Jxz = jsonData["Jxz"]["Value"].get<double>();
        this->edl.SimEDLParsNSF.Jyz = jsonData["Jyz"]["Value"].get<double>();
    })) {
        return false;
    };
    
    // Thrusters Data
    if (!loadConfigFile(scenario_name + "/SimEDL", "ThrusterAllocParsSimNSF", [&](const json& jsonData) {
        this->edl.ThrusterAllocParsSimNSF.FSatMaxSim = jsonData["FSatMaxSim"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.FSatMinSim = jsonData["FSatMinSim"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.thxSim0 = jsonData["thxSim0"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.thxSim1 = jsonData["thxSim1"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.thxSim2 = jsonData["thxSim2"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.thxSim3 = jsonData["thxSim3"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.thySim0 = jsonData["thySim0"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.thySim1 = jsonData["thySim1"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.thySim2 = jsonData["thySim2"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.thySim3 = jsonData["thySim3"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.xThSim0 = jsonData["xThSim0"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.xThSim1 = jsonData["xThSim1"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.xThSim2 = jsonData["xThSim2"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.xThSim3 = jsonData["xThSim3"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.yThSim0 = jsonData["yThSim0"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.yThSim1 = jsonData["yThSim1"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.yThSim2 = jsonData["yThSim2"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.yThSim3 = jsonData["yThSim3"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.zThSim0 = jsonData["zThSim0"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.zThSim1 = jsonData["zThSim1"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.zThSim2 = jsonData["zThSim2"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.zThSim3 = jsonData["zThSim3"]["Value"];
        this->edl.ThrusterAllocParsSimNSF.thrNoiseStd = jsonData["thrNoiseStd"]["Value"];
    })) {
        return 1; // Failed to load configuration
    }

    // Load env data
    Log::warn("MS", "Loading Sim EDL pars: EnvDataNSF...");

    // Load aero data
    Log::warn("MS", "Loading Sim EDL pars: AeroDataNSF...");

    // ==============END EDL SIM LOADING==============



    Log::done("MS", "Scenario Loading Completed successfully.");
    return true;
}

bool MissionScenario::isLoaded() {
    return this->loaded;
}


bool MissionScenario::loadConfigFile(const std::string& scenario_name, const std::string& str_name, std::function<void(const nlohmann::json&)> fnct) {
    // Load from Config folder
    std::string filename = "./Config/" + scenario_name + "/" + str_name + ".json";
    std::ifstream file(filename);
    if (!file.is_open()) {
        Log::err("MS", "%s Loading Error. Failed to open file %s", str_name.c_str(), filename.c_str());
        return false;
    }

    json jsonData;
    try {
        file >> jsonData;
    } catch (json::parse_error& e) {
        Log::err("MS", "%s Loading Error. Failed to parse json structure.", str_name.c_str());
        return false;
    }

    if (jsonData.empty()) {
        Log::err("MS", "%s Loading Error. Empty json data.", str_name.c_str());
        return false;
    } 

    // Access JSON values
    jsonData = jsonData["parameters"];

    fnct(jsonData);

    Log::done("MS", "%s Loading Completed successfully.", str_name.c_str());
    return true;
};

bool MissionScenario::loadLookUpTable(const std::string& filename, const std::string& input_value, std::vector<std::string> datapoints) {
    // Load from LookUpTables folder
    std::string filename = "./LookUpTables/" + filename + ".json";
    std::ifstream file(filename);
    if (!file.is_open()) {
        Log::err("MS", "Loading LookUpTable Error. Failed to open file %s", filename.c_str());
        return false;
    }

    json jsonData;
    try {
        file >> jsonData;
    } catch (json::parse_error& e) {
        Log::err("MS", "Loading LookUpTable Error. Failed to parse json structure.");
        return false;
    }

    if (jsonData.empty()) {
        Log::err("MS", "Loading LookUpTable Error. Empty json data.");
        return false;
    } 

    // Access JSON values
    jsonData = jsonData["input_value"];

    fnct(jsonData);

    Log::done("MS", "%s Loading Completed successfully.", str_name.c_str());
    return true;
};

void MissionScenario::printScenario() {
    std::cout << "----------------------------------------------\n";
    std::cout << "Scenario Name: " << scenario_name << std::endl;
    
    MCSimParsNSF.print();
    NominalMissionNSF.print();
    TimeStepsNSF.print();
    DRAppParsNSF.print();
    CoMNomX0NSF.print();
    edl.print();

    std::cout << "----------------------------------------------\n";
}