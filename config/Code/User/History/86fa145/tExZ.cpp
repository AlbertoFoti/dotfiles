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
    this->target.site_name = jsonData["Landing Site"]["name"];
    this->target.location = {
        jsonData["Landing Site"]["R"],
        jsonData["Landing Site"]["Lon"],
        jsonData["Landing Site"]["Lat"]
    };

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

    // >> Control Pars ==================================== 
    
    // Load 'CoMControlParsNSF'
    if(!loadConfigFile(scenario_name + "/Control", "CoMControlParsNSF", [&](const nlohmann::json& jsonData) {
        this->CoMControlParsNSF.BUGMAX = jsonData["BUGMAX"]["Value"];
        this->CoMControlParsNSF.GHVMAX = jsonData["GHVMAX"]["Value"];
        this->CoMControlParsNSF.ObsDs = jsonData["ObsDs"]["Value"];
        this->CoMControlParsNSF.ObsDv = jsonData["ObsDv"]["Value"];
        this->CoMControlParsNSF.ObsDh = jsonData["ObsDh"]["Value"];
        this->CoMControlParsNSF.ObsDfpa = jsonData["ObsDfpa"]["Value"];
        this->CoMControlParsNSF.StFdbkH = jsonData["StFdbkH"]["Value"];
        this->CoMControlParsNSF.StFdbkS1 = jsonData["StFdbkS1"]["Value"];
        this->CoMControlParsNSF.StFdbkS2 = jsonData["StFdbkS2"]["Value"];
        this->CoMControlParsNSF.STPDWNDUR = jsonData["STPDWNDUR"]["Value"];
        this->CoMControlParsNSF.TSTPDWN = jsonData["TSTPDWN"]["Value"];
        this->CoMControlParsNSF.ugMax = jsonData["ugMax"]["Value"];
        this->CoMControlParsNSF.ugMin = jsonData["ugMin"]["Value"];
        this->CoMControlParsNSF.DistF_H = jsonData["DistF_H"]["Value"];
        this->CoMControlParsNSF.DistF_S = jsonData["DistF_S"]["Value"];
        this->CoMControlParsNSF.StateFF_H = jsonData["StateFF_H"]["Value"];
        this->CoMControlParsNSF.StateFF_S = jsonData["StateFF_S"]["Value"];
        this->CoMControlParsNSF.DrObsFlagH = jsonData["DrObsFlagH"]["Value"];
        this->CoMControlParsNSF.DrObsFlagS = jsonData["DrObsFlagS"]["Value"];
        this->CoMControlParsNSF.CrClFlag = jsonData["CrClFlag"]["Value"];
        this->CoMControlParsNSF.GuiFlag = jsonData["GuiFlag"]["Value"];
    })) {
        return false;
    };

    // Load 'InputVariablesControlNSF'
    if(!loadConfigFile(scenario_name + "/Control", "InputVariablesControlNSF", [&](const nlohmann::json& jsonData) {
        this->InputVariablesControlNSF.Jl = jsonData["Jl"]["Value"];
        this->InputVariablesControlNSF.Jm = jsonData["Jm"]["Value"];
        this->InputVariablesControlNSF.Jn = jsonData["Jn"]["Value"];
        this->InputVariablesControlNSF.yaCoM = jsonData["yaCoM"]["Value"];
        this->InputVariablesControlNSF.xaCoM = jsonData["xaCoM"]["Value"];
        this->InputVariablesControlNSF.FmaxTh = jsonData["FmaxTh"]["Value"];
        this->InputVariablesControlNSF.FminTh = jsonData["FminTh"]["Value"];
        this->InputVariablesControlNSF.FmaxSat = jsonData["FmaxSat"]["Value"];
        this->InputVariablesControlNSF.FminSat = jsonData["FminSat"]["Value"];
        this->InputVariablesControlNSF.xIMUb = jsonData["xIMUb"]["Value"];
        this->InputVariablesControlNSF.yIMUb = jsonData["yIMUb"]["Value"];
        this->InputVariablesControlNSF.zIMUb = jsonData["zIMUb"]["Value"];
    })) {
        return false;
    };

    // --------------END CONTROL PARS LOADING--------------

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

    // >> SimEDL ==========================================

    // SimEDL Pars
    if(!loadConfigFileNSF(scenario_name + "/SimEDL", "SimEDLParsNSF",
        this->edl.SimEDLParsNSF,
        { "xaCoM", "yaCoM", "zaCoM", "xIMUbSim", "yIMUbSim", "zIMUbSim",
            "mass", "Jxx", "Jyy", "Jzz", "Jxy", "Jxz", "Jyz" 
        }
    )) { return false; };

    // SimEDL X0
    if(!loadConfigFileNSF(scenario_name + "/SimEDL", "SimEDLX0NSF",
        this->edl.SimEDLX0NSF,
        { "r0Sim", "lon0Sim", "lat0Sim", "vAbs0Sim", "fpa0Sim", "head0Sim",
            "eta0Sim", "aoa0Sim", "mu0Sim", "omgl0Sim", "omgm0Sim", "omgn0Sim" 
        }
    )) { return false; };

    // SimEDL ThrusterAllocParsSimNSF
    if(!loadConfigFileNSF(scenario_name + "/SimEDL", "ThrusterAllocParsSimNSF",
        this->edl.SimEDLX0NSF,
        { "FSatMaxSim", "FSatMinSim", "thxSim0", "thxSim1", "thxSim2", "thxSim3",
            "thySim0", "thySim1", "thySim2", "thySim3", "xThSim0", "xThSim1",
            "xThSim2", "xThSim3", "yThSim0", "yThSim1", "yThSim2", "yThSim3",
            "zThSim0", "zThSim1", "zThSim2", "zThSim3", "thrNoiseStd"
        }
    )) { return false; };

    // SimEDL ThrusterAllocParsSimNSF
    if(!loadConfigFileNSF(scenario_name + "/Navigation", "AttNavX0NSF",
        this->edl.SimEDLX0NSF,
        { "omgl0Nav", "omgm0Nav", "omgn0Nav" }
    )) { return false; };

    // Load env data
    Log::warn("MS", "Loading Sim EDL pars: EnvDataNSF...");

    // Load aero data
    Log::warn("MS", "Loading Sim EDL pars: AeroDataNSF...");

    // ==============END EDL SIM LOADING==============

    // >> NAV ==========================================

    // Load att nav x0 data
    Log::warn("MS", "Loading Att NAV X0: AttNavX0NSF...");

    // ==============END NAV Params and X0 LOADING==============

    // >> Load Gravitational data of the planet (celestial body)
    if(!loadConfigFile(scenario_name, "PlanetGrav", [&](const nlohmann::json& jsonData) {
        this->PlanetGrav.SimT = jsonData["SimT"]["Value"];
        this->PlanetGrav.GRAVID = jsonData["GRAVID"]["Value"];
        this->PlanetGrav.MU = jsonData["MU"]["Value"];
        this->PlanetGrav.J2 = jsonData["J2"]["Value"];
        this->PlanetGrav.J3 = jsonData["J3"]["Value"];
        this->PlanetGrav.J4 = jsonData["J4"]["Value"];
        this->PlanetGrav.REQ = jsonData["REQ"]["Value"];
    })) { return false; };


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

bool MissionScenario::loadConfigFileNSF(const std::string& scenario_name, const std::string& str_name, NSFStr& out, std::vector<std::string> ids) {
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

    out.ids = ids;

    out.values.clear();
    out.unctype.clear();
    out.uncminv.clear();
    out.uncmaxv.clear();
    for(unsigned int i=0; i < ids.size(); i++) {
        out.values.push_back(jsonData[ids.at(i)]["Value"]);
        out.unctype.push_back(jsonData[ids.at(i)]["Uncertainty Type"]);
        out.uncminv.push_back(jsonData[ids.at(i)]["Std / Min val"]);
        out.uncmaxv.push_back(jsonData[ids.at(i)]["Max val"]);
    }

    Log::done("MS", "%s Loading Completed successfully.", str_name.c_str());
    return true;
}

LookUpTable MissionScenario::loadLookUpTable(const std::string& filename, const std::string& input_value, std::vector<std::string> datapoints) {
    // Load from LookUpTables folder
    std::string fn = "./Config/" + scenario_name + "/LookUpTables/" + filename + ".json";
    std::ifstream file(fn);
    if (!file.is_open()) {
        Log::err("MS", "Loading LookUpTable Error. Failed to open file %s", filename.c_str());
        return LookUpTable();
    }

    json jsonData;
    try {
        file >> jsonData;
    } catch (json::parse_error& e) {
        Log::err("MS", "Loading LookUpTable Error. Failed to parse json structure.");
        return LookUpTable();
    }

    if (jsonData.empty()) {
        Log::err("MS", "Loading LookUpTable Error. Empty json data.");
        return LookUpTable();
    } 

    // Access JSON values
    jsonData = jsonData[input_value];

    std::vector<double> in_data = jsonData["InputValues"];
    std::vector<std::pair<std::string, std::vector<double>>> datapoints_data;

    for(unsigned int i=0; i<datapoints.size(); i++) {
        std::pair<std::string, std::vector<double>> entry {};
    
        entry.first = datapoints.at(i);

        for (const auto& element : jsonData[datapoints.at(i)]) {
            if (!element.is_number()) {
                throw std::runtime_error("Array elements must be numbers");
            }
            
            entry.second.push_back(element);
        }

        datapoints_data.push_back(entry);
    }

    LookUpTable res(
        in_data,
        datapoints_data
    );

    Log::info("MS", "Loading LookUpTable %s Completed successfully.", input_value.c_str());
    return res;
};

void MissionScenario::printScenario() {
    std::cout << "----------------------------------------------\n";
    std::cout << "Scenario Name: " << scenario_name << std::endl;
    
    MCSimParsNSF.print();
    NominalMissionNSF.print();
    TimeStepsNSF.print();
    CoMControlParsNSF.print();
    InputVariablesControlNSF.print();
    DRAppParsNSF.print();
    CoMNomX0NSF.print();
    PlanetGrav.print();
    edl.print();
    nav.print();

    std::cout << "----------------------------------------------\n";
}