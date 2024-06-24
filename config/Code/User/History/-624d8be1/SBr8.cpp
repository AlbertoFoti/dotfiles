#include "GE_Path_Planning.hxx"
#include "DataReaderWriter.hxx"
#include "CoM3DOF/CoM3DOF.hxx"
#include "CoM2DOF/CoM2DOF.hxx"
#include "Grav/GE_Grav01.hxx"
#include <iostream>
#include <algorithm>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <random>
#include "Utils.hxx"
#include "LinSysSolve/LSsolve.hxx"
#include "MathConstants.hxx"


GEPathPlanning::GEPathPlanning(std::shared_ptr<MissionScenario> ms) 
    : ms { ms }
{
    return;
}

GEPathPlanning::~GEPathPlanning() {
    clean();
}

void GEPathPlanning::init() {
    return;
}

void GEPathPlanning::initializeSeeds() {
    Log::info("PP", "Initializing seeds...");

    std::random_device rd; // Get random seed from system
    ms->rg.rand_gen = std::mt19937(rd()); // Seed the engine

    ms->rg.seedV = randi(ms->rg, std::pow(2, 32)-1, ms->MCSimParsNSF.NmonOrg, 1);
    ms->rg.seedVemcd = randi(ms->rg, std::pow(2, 32)-1, ms->MCSimParsNSF.NmonOrg, 1);

    Log::done("PP", "Successfully initialized seeds.");
    return;
}

void GEPathPlanning::initializeSeeds(uint32_t seed) {
    Log::info("PP", "Initializing seeds...");

    ms->rg.rand_gen = std::mt19937(seed); // Seed the engine

    ms->rg.seedV = randi(ms->rg, std::pow(2, 32)-1, ms->MCSimParsNSF.NmonOrg, 1);
    ms->rg.seedVemcd = randi(ms->rg, std::pow(2, 32)-1, ms->MCSimParsNSF.NmonOrg, 1);
    ms->rg.dis = std::normal_distribution<double>(0, 1);

    Log::done("PP", "Successfully initialized seeds.");
    return;
}

void GEPathPlanning::randomizeAndInitialize(uint32_t kMon) {
    Log::info("PP", "Randomize and Initialize step...");

    //int x = ms->rg.rand_gen();

    double seedIn = ms->rg.seedV.at(kMon).at(0);
    double seedEMCD = ms->rg.seedVemcd.at(kMon).at(0);

    // Randomize
    randomizeNSFstr(ms->edl.SimEDLParsNSF);
    randomizeNSFstr(ms->edl.SimEDLX0NSF);
    randomizeNSFstr(ms->nav.AttNavX0NSF);
    randomizeNSFstr(ms->edl.ThrusterAllocParsSimNSF);

    this->CoMNav01 = {
        ms->edl.SimEDLX0NSF.getR("r0Sim"),
        ms->edl.SimEDLX0NSF.getR("lon0Sim"),
        ms->edl.SimEDLX0NSF.getR("lat0Sim"),
        ms->edl.SimEDLX0NSF.getR("vAbs0Sim"),
        ms->edl.SimEDLX0NSF.getR("fpa0Sim"),
        ms->edl.SimEDLX0NSF.getR("head0Sim"),
    };

    this->AttNav02 = {
        ms->edl.SimEDLX0NSF.getR("eta0Sim"),
        ms->edl.SimEDLX0NSF.getR("aoa0Sim"),
        ms->edl.SimEDLX0NSF.getR("mu0Sim"),
        ms->edl.SimEDLX0NSF.getR("mu0Sim"),
        ms->edl.SimEDLX0NSF.getR("omgl0Sim"),
        ms->edl.SimEDLX0NSF.getR("omgm0Sim"),
        ms->edl.SimEDLX0NSF.getR("omgn0Sim"),
    };

    for(unsigned int i=0; i<6; i++) {
        xCoMNavEIP.at(i) = this->CoMNav01.at(i);
    }

    MatrixT xCoMNomEIP_m;
    std::vector<double> xCoMNomEIP_v {};
    for(unsigned int i=0; i<6; i++) {
        xCoMNomEIP_v.push_back(ms->CoMNomX0NSF.xCoMNomEIP.at(i));
    }
    xCoMNomEIP_m.insertRow(xCoMNomEIP_v, 0);

    MatrixT xCoMNavEIP_m;
    std::vector<double> xCoMNavEIP_v {};
    for(unsigned int i=0; i<6; i++) {
        xCoMNavEIP_v.push_back(xCoMNavEIP.at(i));
    }
    xCoMNavEIP_m.insertRow(xCoMNavEIP_v, 0);

    this->GetErrSYH(xCoMNomEIP_m, xCoMNavEIP_m);
    

    Log::warn("PP", "Randomize and Initialize step completed successfully.");
    return;
}

void GEPathPlanning::loadSfStructures() {
    Log::info("PP", "Loading Sf Structures...");

    Log::warn("PP", "Sf Structures loaded successfully.");
    return;
}

void GEPathPlanning::buildLookUpTables() {
    Log::info("PP", "Building LookUpTables...");

    // ------------------------------------------------
    // Data is feched from EMCD calls
    // ATM_EMCD435(...)
    // Calculations are performed and written to DHS files
    // GEaoa.DHS, GEguidance.DHS
    //
    // The following 7 lookup tables are written:
    // 1. Density as a function of the radial position
    // 2. Mach Number as a function of the radial position
    // 3. Atmospheric density fitted spatial constant as a function of the radial position
    // 4. Drag coefficient as a function of Mach
    // 5. Lift coefficient as a function of Mach
    // 6. Moment coefficient at the trim angle as a function of Mach
    // 7. Moment coeffiicent sensitivity on the angle of attack at the trim angle
    //    as a function of Mach
    // ------------------------------------------------

    // ------------------------------------------------
    // AT_EMCD435
    // Testing connection with atmospheric database
    // EMCD Parameters
    // Initialized EMCD call using MY24 unperturbed scenario, simulation date
    // and EIP latitude and longitude.
    // ------------------------------------------------
    Log::err("AT", "Atmospheric model ATM_EMCD435 is needed.");

    // ------------------------------------------------
    // Write to file the computed lookuptables
    // ------------------------------------------------
    Log::info("PP", "Writing to file the computed lookUpTables...");
    Log::warn("PP", "LookUpTables were not computed.");


    Log::warn("PP", "LookUpTables built successfully.");
    return;
}

void GEPathPlanning::loadLookUpTables() {
    Log::info("PP", "Loading lookUpTables...");
    bool error = false;

    std::vector<std::string> lookup_mach_datapoints = {
        "cDtrimLkUp",
        "cLtrimLkUp",
        "cNtrimLkUp",
        "tauNtrimLkUp",
    };

    std::vector<std::string> lookup_radius_datapoints = {
        "cSndLkUp",
        "rhoNomLkUp",
        "HatmLkUpFilt"
    };

    // loading LKUP tables --------------------------------------------

    // >> Mach LookUpTables
    this->ms->machLookUpTable = this->ms->loadLookUpTable("GEguidance", "Mach", lookup_mach_datapoints);
    if(this->ms->machLookUpTable.isEmpty()) {
        Log::err("MS", "Error loading Mach LookUpTable.");
        error = true;
    }

    // >> Radius LookUpTables
    this->ms->radiusLookUpTable = this->ms->loadLookUpTable("GEguidance", "Radius", lookup_radius_datapoints);
    if(this->ms->radiusLookUpTable.isEmpty()) {
        Log::err("MS", "Error loading Radius LookUpTable.");
        error = true;
    }

    // -----------------------------------------------------------------
    // Other data
    // Polynomial fit of Hatm as a function of the radial position
    this->ms->OrderHatm = 4;
    double minR = *std::min_element(
        ms->radiusLookUpTable.input_data.begin(),
        ms->radiusLookUpTable.input_data.end()
    );
    double maxR = *std::max_element(
        ms->radiusLookUpTable.input_data.begin(),
        ms->radiusLookUpTable.input_data.end()
    );
    this->ms->R0 = minR + (maxR - minR)/2;
    this->ms->cHatm           = 0;//polyfit((RinLkUp-R0)/R0,HatmLkUp,OrderHatm);

    if(error) {
        Log::spacing();
        exit(1);
    } else {
        Log::done("PP", "LookUpTables loaded successfully.");
    }

    return;
}

void GEPathPlanning::buildMissionTrajectory() {
    this->nominal_traj = this->buildNominalMissionTrajectory();

    Log::info("PP", "Running nominal simulation...");

    // ---------- Run Nominal Simulation -----------------
    bool stop = false;
    bool first = true;
    uint32_t idx = 1;
    
    while (stop == false) {
        auto x0 = ms->CoMNomX0NSF.xCoMNomEIP;
        auto t1 = ms->NominalMissionNSF.tPDPNom;
        auto Tsim = ms->TimeStepsNSF.Tgui;

        auto muSim = nominal_traj.mu;
        auto tSim  = nominal_traj.tSim;

        // 3dof detailed simulation
        Log::info("PP", "Running 3dof detailed simulation... [Iter:  %d]", idx);
        this->simCoM3dof();

        //Log::info("GE", "Collecting results of simCom3DOF detailed...");
        this->nominal_traj.xCoM = ms->sim3dof_out.xCoM;
        this->nominal_traj.cDNomProf = ms->sim3dof_out.cDProf;
        this->nominal_traj.cLNomProf = ms->sim3dof_out.cLProf;
        this->nominal_traj.rhoNomProf = ms->sim3dof_out.rhoProf;
        this->nominal_traj.FDNom = ms->sim3dof_out.FD;
        this->nominal_traj.FLNom = ms->sim3dof_out.FL;
        //this->nominal_traj.FaWASNom = ms->sim3dof_out.FaWAS;
        this->nominal_traj.xCoMDotNom = ms->sim3dof_out.xCoMDot;
        this->nominal_traj.machNom = ms->sim3dof_out.mach;
        this->nominal_traj.gNEDNom = ms->sim3dof_out.gNED;

        std::vector<double> xCoMPDP = nominal_traj.xCoM.getLastRow();
        double machNomPDP = nominal_traj.machNom.back();

        // Nominal PDP State
        std::cout << "-------------------------------------\n";
        std::cout << "> Nominal EIP State\n";
        std::cout << "    Lon    : " << ms->CoMNomX0NSF.lon0Nom*RAD2DEG << " deg\n";
        std::cout << "    Lat     : " << ms->CoMNomX0NSF.lat0Nom*RAD2DEG << " deg\n";
        std::cout << "? Nominal PDP State\n";
        std::cout << "    tPDP    : " << ms->NominalMissionNSF.tPDPNom << " s\n";
        std::cout << "    Alt     : [-needs ATM_EMCD435-]" << " km\n";
        std::cout << "    Lon     : " << xCoMPDP.at(1)*RAD2DEG << " deg\n";
        std::cout << "    Lat     : " << xCoMPDP.at(2)*RAD2DEG << " deg\n"; 
        std::cout << "    vAbs    : " << xCoMPDP.at(3) << " m/s\n";
        std::cout << "    FPA     : " << xCoMPDP.at(4)*RAD2DEG << " deg\n";
        std::cout << "    Heading : " << xCoMPDP.at(5)*RAD2DEG << " deg\n";
        std::cout << "    Mach    : " << machNomPDP << "\n"; 
        std::cout << "-------------------------------------\n";

        // Compute distance from landing site (LS)
        double deg2km = (2*pi*ms->NominalMissionNSF.rCelBodyNom/1000.00)/360.00;
        double err_max = 10; // in km (Along track and Cross track error AT,CT)

        //double err_AT = (targetLS.lon - PDP.lon)*deg2km;
        //double err_CT = (targetLS.lat - PDP.lat)*deg2km; 

        std::cout << "  Error along track (AT) [km] = 0.00\n"; //<< err_AT;
        std::cout << "  Error cross track (CT) [km] = 0.00\n"; //<< err_CT;
        std::cout << "  Distance from LS [km]       = 0.00\n"; //<< norm(err_AT, err_CT);
        std::cout << "-------------------------------------\n";

        // Post processing
        Log::err("AT", "Atmospheric model ATM_EMCD435 is needed for post-processing.");

        // Error lon-lat between target and computed pdp
        // -> Error along track (AT) [Km]
        // -> Error cross track (CT) [Km]
        // -> Distance from Landing Site (LS)
        // -> plot LS and nominal CoM during trajectory until PDP (2D plot)

        // Stop condition
        // PDP-LS error must be less than err_max (AT, CT) and
        // the PDP altitude must be in range [MinAltPDP-MaxAltPDP] Km
        if (true) {
            stop = true;            
        } else {

        }

        idx++;
    }

    // ----------------------------------------------------

    Log::warn("PP", "Nominal simulation ended successfully.");
    return;
}

BRMsData GEPathPlanning::buildNominalMissionTrajectory() {
    Log::info("PP", "Building nominal mission trajectory...");
    ms->NominalMissionNSF.TNom = 1;

    double TNom  = ms->NominalMissionNSF.TNom;
    double tPDPNom = ms->NominalMissionNSF.tPDPNom;
    double ugNom   = ms->NominalMissionNSF.ugNom;
    std::vector<double> uNom;

    // N_Nom and uNom
    uint32_t N_Nom = tPDPNom / TNom + 1;
    
    for(unsigned int i=0; i<N_Nom; i++) {
        uNom.push_back(ugNom);
    }

    // Build Nominal bank angle profile
    std::vector<double> tSimNom = linspace(0.00, tPDPNom, N_Nom);
    std::vector<double> muNomNBR = acos_vectorial(uNom);

    BRMsData brms = addMultipleBankReversals(
        tSimNom, 
        muNomNBR, 
        ms->NominalMissionNSF.tBrVNom,
        ms->NominalMissionNSF.aMax
    );

    // Write nominal trajectory and plot
    writeTo("Data/mu_nominal_profile.txt", brms.collectMu());
    system("cd Data && python3 plot_mu_profile.py &");
    //system("cd Data && python3 plot_trajectory.py &");

    Log::done("PP", "Nominal mission trajectory built.");
    return brms;
}

void GEPathPlanning::buildGuidanceTrajectory() {
    Log::info("PP", "Building guidance trajectory...");

    double Raeroid {};

    DRAppParsNSFStr drApp = ms->DRAppParsNSF;
    double massDR = ms->NominalMissionNSF.massNom;
    double rCelBodyDR = Raeroid;
    double SrefDR = ms->NominalMissionNSF.SrefNom;
    double omgCelBodyDR = ms->NominalMissionNSF.omgCelBodyNom;
    double headDR = ms->CoMNomX0NSF.xCoMNomEIP.at(5);
    double latDR = ms->CoMNomX0NSF.xCoMNomEIP.at(2);

    ms->parDR = {
        drApp,
        massDR,
        rCelBodyDR,
        SrefDR,
        omgCelBodyDR,
        headDR,
        latDR
    };

    ms->parDRCell = {
        drApp.gravDR,
        massDR,
        SrefDR,
        Raeroid,
        ms->R0,
        ms->cHatm
    };

    // QCROrg
    auto QCROrg = MatrixT::eye(8);

    MatrixT NitMat = MatrixT(std::vector<std::array<double,6>>({
        {3, 3, 2, 1, 1, 1},
        {3, 3, 2, 1, 1, 1}
    }));

    // TODO : REMOVE
    ms->CoMControlParsNSF.GuiFlag = false;

    // end if path planning flag is false: trajectory is the nominal traj
    if(ms->CoMControlParsNSF.GuiFlag == false) {
        // If the path-planning algorithm in not computed, the output profile is the nominal profile
        ms->gui_profile_out.tSim = nominal_traj.tSim;
        ms->gui_profile_out.mu = nominal_traj.collectMu();
        // muNomNBR
        //ms->gui_profile_out.tBrV = nominal_traj.tBrV;
        ms->gui_profile_out.dirBr = nominal_traj.dirBr;
        ms->gui_profile_out.xSim = nominal_traj.xCoM;

        ms->gui_profile_out.cDProf = nominal_traj.cDNomProf;
        ms->gui_profile_out.cLProf = nominal_traj.cLNomProf;
        ms->gui_profile_out.rhoProf = nominal_traj.rhoNomProf;
        ms->gui_profile_out.FD = nominal_traj.FDNom;
        ms->gui_profile_out.FL = nominal_traj.FLNom;
        //ms->gui_profile_out.FaWAS
        ms->gui_profile_out.xCoMDot = nominal_traj.xCoMDotNom;
        ms->gui_profile_out.mach = nominal_traj.machNom;
        ms->gui_profile_out.gNED = nominal_traj.gNEDNom;

        ms->gui_profile_out.tPDPGui = ms->NominalMissionNSF.tPDPNom;

        MatrixT vgh;
        vgh.insertCol(nominal_traj.xCoM.getCol(3), 0);
        vgh.insertCol(nominal_traj.xCoM.getCol(4), 1);
        vgh.insertCol(vectorScalarSub(nominal_traj.xCoM.getCol(0), Raeroid), 2);
    } else {

        auto sz = NitMat.size();
        uint32_t NitRefGen = sz.at(1);

        auto dxMat = zeros(6, NitRefGen);
        auto QCR = MatrixT::slice(QCROrg, 
            {0, ms->NominalMissionNSF.NbrNom},
            {0, ms->NominalMissionNSF.NbrNom}
        );
        auto invQCR = MatrixT::inverse(QCR);
        auto Nbr = ms->NominalMissionNSF.tBrVNom;

        // ***
        auto optimal_time_data = this->findOptimalTime();
        auto tSim = optimal_time_data.tSim;
        //auto muOptNBR = optimal_time_data...;

        // ***
        //auto res = this->addMultipleBankReversals(tSim, muOptNBR, tBrVNom2, ms->NominalMissionNSF.aMax);
        // tBrInitLast
        // tBrEndLast

        //auto x0 = ms->
        // muSim

        // ***
        // this->sim3dofDetailed(...)

        // tSim01
        // muSim01
        // xSim01

        // tNC
        // muNC
        // xNC

        // ***
        // this->getErrSYH(...)

        // dxCRPDP
        // tBrVLast
        // muLast
        // muLastNBR
        // brFlagLast

        // vgh profile built
        // vgh = ...

        // Run iteratively
        // This loop solves a predefined number of times the lateral path-planning
        // and the longitudinal path planning
        for(unsigned int k=0; k<NitRefGen; k++) {
            for(unsigned int i=0; i<NitMat.at(0).at(k); i++) {
                // The lateral controllability matrix gives the PDP lateral deviations as 
                // a function of a lateral command u_Chi
                // ***
                // ContMat = BuildCRContMat_02(vgh, Tgui);

                // Based on the controllability matrix, the sensitivity of the
                // PDP lateral state to time variations of each bank manouver is computed
                // ***
                // K = DeltatGains(...);
                // KCrLast = K;

                
            }
        }
    
    }

    auto tGuiRs = linspace(0, ms->gui_profile_out.tPDPGui, ms->gui_profile_out.tPDPGui/ms->TimeStepsNSF.TCoM + 1);
    this->ms->gui_profile_out.tRs = tGuiRs;
    auto Np = tGuiRs.size();
    
    // gvhMaxGui
    // bugMaxGui

    // KCrGui
    // tBrVGui
    // dirBrVGui
    
    this->ms->gui_profile_out.muRs    = interp1(
        this->ms->gui_profile_out.tSim,
        this->ms->gui_profile_out.mu,
        this->ms->gui_profile_out.tRs,
        "spline"
    );

    this->ms->gui_profile_out.muNBRRs = interp1(
        this->ms->gui_profile_out.tSim,
        this->ms->gui_profile_out.muNBR,
        this->ms->gui_profile_out.tRs,
        "spline"
    );

    this->ms->gui_profile_out.xCoMRs = interp1_matrix(
        this->ms->gui_profile_out.tSim,
        this->ms->gui_profile_out.xCoM,
        this->ms->gui_profile_out.tRs,
        "spline"
    );

    // gNEDGuiRs
    
    ms->gui_profile_out.uMuRs = zeros(Np);
    for(unsigned int i=2; i<Np; i++) {
        ms->gui_profile_out.uMuRs.at(i-1) = ms->gui_profile_out.uMuRs.at(i) - 2*ms->gui_profile_out.uMuRs.at(i-1) + ms->gui_profile_out.uMuRs.at(i-2);
    }

    // Guidance Profiles
    std::cout << "-------------------------------------\n";
    std::cout << "> Longitudinal Guidance Profiles\n";
    std::cout << "    Bank angle second derivative (uMuGuiRs)  : -\n";
    std::cout << "    Bank angle profile           (muGuiRs)   : -\n";
    std::cout << "    Center of Mass               (xCoMGuiRs) : -\n";
    std::cout << "    Gravity [in NED]             (gNEDGuiRs) : -\n";
    std::cout << "-------------------------------------\n";
    std::cout << "    Bank Reversal Maneuvers Time (tBrmGui)   : -\n";
    std::cout << "    Bank Reversal Maneuvers Dir (dirBrmGui)  : -\n";
    std::cout << "-------------------------------------\n";

    // write to file
    writeGuidanceData("Data/GEpathplanner", ms->gui_profile_out);

    Log::warn("PP", "Guidance trajectory built successfully.");
    return;
}

void GEPathPlanning::clean() {
    return;
}

BRMsData GEPathPlanning::addMultipleBankReversals(std::vector<double>& tu, std::vector<double>& mu, std::vector<double>& tbrV, double aMax) {
    uint32_t Nbr = tbrV.size();
    auto brFlag = zeros(tu.size());
    auto tBrInitV = zeros(Nbr);
    auto tBrEndV = zeros(Nbr);
    auto dirBrV = zeros(Nbr);
    std::vector<double> mu_computed = mu;

    // The direction of the bank reversals is switched arbitrarly.
    for(unsigned int i=0; i<Nbr; i++) {
        if(i % 2 == 0) {
            dirBrV.at(i) = +1;
        } else {
            dirBrV.at(i) = -1;
        }
    }

    // Each bank reversal is added by this function
    for (int i = 0; i < Nbr; ++i) {
        BRMsData result = AddBankReversalKeep(tu, mu_computed, tbrV.at(i), aMax, dirBrV.at(i)); // Call the function with element-wise access

        mu_computed.clear();
        for(unsigned int j=0; j<tu.size(); j++) {
            mu_computed.push_back(result.mu.at(j).value);
        }

        sum(brFlag, result.brFlag); // Update brFlag using the fourth element (brFlagNew)
        tBrInitV.at(i) = result.tBrInit.at(0); // Store tBrInit (second element)
        tBrEndV.at(i)  = result.tBrEnd.at(0);  // Store tBrEnd (third element)
    }

    // The profile is cleaned to avoid jumps caused by numerical and
    // approximation errors made by the 'AddBankReversalKeep' function
    auto brms_cleaned = FixBankReversalProfKeep_02(tu,mu_computed,tBrInitV,tBrEndV,brFlag,aMax);
    
    // add left out data and return
    brms_cleaned.tSim = tu;
    brms_cleaned.dirBr = dirBrV;
    return brms_cleaned;
}

BRMsData GEPathPlanning::AddBankReversalKeep(
    std::vector<double>& tu, 
    std::vector<double>& mu, 
    double tbr, 
    double aMax, 
    double dirBr
) {
    auto res = BRMsData();

    uint32_t N = tu.size();
    auto temp = find(vectorGreater(tu, (double)tbr));

    if(temp.size() == 0) {
        for(unsigned int i=0; i<tu.size(); i++) {
            res.mu.push_back({
                tu.at(i),
                mu.at(i)
            });
        }
        res.tBrInit.push_back(0);
        res.tBrEnd.push_back(0);
        res.dirBr.push_back(0);
        res.brFlag = zeros(N);
    } else {
        // Staring index of BRM
        uint32_t ixBr = temp.at(0);
        
        // Initial bank angle
        double mu0 = mu.at(ixBr);
        
        // Initial bank angle derivative
        double muP0 = (mu.at(ixBr) - mu.at(ixBr-1)) / (tu.at(ixBr) - tu.at(ixBr-1));

        // This function computes the two adjacent bank angles that hold the
        // same cosine and their derivative such that the derivative of
        // their cosine is equal to the original derivative
        std::pair<double, double> mu10, muP10, m;
        GetReversedLeftAndRigthBankSt(mu0, muP0, mu10, muP10, m);

        double tbrRel, tswRel, s0, muFeff;
        // Used to store the final m
        double m_final {};

        if(dirBr == -1) {
            // left manoeuvre
            
            double mL = m.first;
            double mu10L = mu10.first;
            double muP10L = muP10.second; // TODO: CHECH THIS SECTION
            
            // initial and final states of the band band manoeuver
            double x0 = mu0;
            double v0 = muP0;
            double x10 = mu10L;
            double v10 = muP10L;

            // The next segment to which the bank angle will belong (safety)
            double nextML = floor(abs(x10)/pi);

            // BR direction
            double s0L = sign(x10 - x0);
            s0 = s0L;

            // Two solutions of the second order polinomial giving the manoeuver time
            double tbrRelA =  (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*aMax);
            double tbrRelB = -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)-v10+v0)/(s0*aMax);
            double t2 {};
            if(tbrRelA > 0) { // positive solution is chosen
                t2 = tbrRelA;
            } else {
                t2 = tbrRelB;
            }

            // the switching time is chosen
            tbrRel = t2;
            tswRel = (s0*t2*aMax+v10-v0)/(2*s0*aMax);
            
            // the effective final bank angle is computed
            muFeff = x10 + v10*t2;
            double satmuF = 0;

            // the valid values for final bank angle, where the current
            // segment is not left, are computed
            double muFMin, muFMax;
            if(x10 > 0) {
                muFMin = nextML*pi;
                muFMax = (nextML+1)*pi;
            } else {
                muFMin = -1*(nextML+1)*pi;
                muFMax = -1*nextML*pi;
            }

            // if the future bank angle leaves the segment, its value is adjusted...    
            double muFeffL {};
            if(muFeff > muFMax) {
                satmuF  = 1;
                muFeffL = muFMax;
            } else if(muFeff < muFMin) {
                satmuF  = -1;
                muFeffL = muFMin;
            }

            // ... and the manoeuver is recalculated for safety reasons
            if(abs(satmuF) > 0.5) {
                x0      = mu0;
                v0      = muP0;
                x10     = muFeffL;
                v10     = 0;

                s0      = sign(x10-x0);

                tbrRelA	=  (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*aMax);
                tbrRelB	= -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)-v10+v0)/(s0*aMax);


                if(tbrRelA > 0) {
                    t2      = tbrRelA;
                } else {
                    t2      = tbrRelB;
                }

                tbrRel  = t2;
                tswRel	= (s0*t2*aMax+v10-v0)/(2*s0*aMax);
            }
        
            s0 = s0L;
            m_final  = mL;
        
        } else if(dirBr == 1) {
            // Right maneouver
            double mR = m.second;
            double mu10R = mu10.second;
            double muP10R = muP10.second;
            
            // initial and final states of the band band manoeuver
            double x0 = mu0;
            double v0 = muP0;
            double x10 = mu10R;
            double v10 = muP10R;

            // The next segment to which the bank angle will belong (safety)
            double nextMR = floor(abs(x10)/pi);

            // BR direction
            double s0R = sign(x10 - x0);
            s0 = s0R;

            // Two solutions of the second order polinomial giving the manoeuver time
            double tbrRelA =  (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*aMax);
            double tbrRelB = -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)-v10+v0)/(s0*aMax);
            double t2 {};
            if(tbrRelA > 0) { // positive solution is chosen
                t2 = tbrRelA;
            } else {
                t2 = tbrRelB;
            }

            // the switching time is chosen
            tbrRel = t2;
            tswRel = (s0*t2*aMax+v10-v0)/(2*s0*aMax);
            
            // the effective final bank angle is computed
            muFeff = x10 + v10*t2;
            double satmuF = 0;

            // the valid values for final bank angle, where the current
            // segment is not left, are computed
            double muFMin, muFMax;
            if(x10 > 0) {
                muFMin = nextMR*pi;
                muFMax = (nextMR+1)*pi;
            } else {
                muFMin = -1*(nextMR+1)*pi;
                muFMax = -1*nextMR*pi;
            }

            // if the future bank angle leaves the segment, its value is adjusted...    
            double muFeffR {};
            if(muFeff > muFMax) {
                satmuF  = 1;
                muFeffR = muFMax;
            } else if(muFeff < muFMin) {
                satmuF  = -1;
                muFeffR = muFMin;
            }

            // ... and the manoeuver is recalculated for safety reasons
            if(abs(satmuF) > 0.5) {
                x0      = mu0;
                v0      = muP0;
                x10     = muFeffR;
                v10     = 0;

                s0      = sign(x10-x0);

                tbrRelA	=  (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*aMax);
                tbrRelB	= -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)-v10+v0)/(s0*aMax);


                if(tbrRelA > 0) {
                    t2      = tbrRelA;
                } else {
                    t2      = tbrRelB;
                }

                tbrRel  = t2;
                tswRel	= (s0*t2*aMax+v10-v0)/(2*s0*aMax);
            }
        
            s0 = s0R;
            m_final  = mR;

        } else {
            Log::err("GE", "Wrong Bank reversal direction.");
        }

        res.tBrInit.push_back(tbr);
        res.tBrEnd.push_back(tbr+tbrRel);
        for(unsigned int i=0; i<tu.size(); i++) {
            res.mu.push_back({
                tu.at(i),
                0
            });
        }


        // Adjust the bank profile
        // Once the time instants, duration and commmand switching times are
        // available, the bank angle profile is built using the closed form
        // solutions of the bank angle during the bank reversal.
        res.brFlag = zeros(N);

        for (unsigned int i=0; i<N; i++) {
            if (tu.at(i) > tbr) {
                if (tu.at(i) < (tbr + tswRel)) {
                    res.mu.at(i).value = mu0 + muP0*(tu.at(i)-tbr) + s0*0.5*aMax*std::pow(tu.at(i)-tbr, 2);
                    res.brFlag.at(i) = 1;
                } else if (tu.at(i) < (tbr + tbrRel)) {
                    res.mu.at(i).value = mu0 + muP0*tswRel + s0*0.5*aMax*std::pow(tswRel, 2) + (muP0 + s0*aMax*tswRel)*(tu.at(i)-(tbr + tswRel)) - s0*0.5*aMax*std::pow(tu.at(i)-(tbr + tswRel), 2);
                    res.brFlag.at(i) = 1;
                } else {
                    // This function allows to set the values after the bank
                    // reversal as thir adjusted segment. 
                    res.mu.at(i).value = UnNBR(acos(cos(mu.at(i))), m_final, sign(muFeff));
                }
            } else {
                res.mu.at(i).value = mu.at(i);
            }
        }
    }
    
    return res;
}

BRMsData GEPathPlanning::FixBankReversalProfKeep_02(
    std::vector<double>& tu, 
    std::vector<double>& mu, 
    std::vector<double>& tBrInitV,
    std::vector<double>& tBrEndV,
    std::vector<double>& brFlag,
    double aMax
) {
    auto res = BRMsData();

    int N = tu.size();
    double T = tu.at(1) - tu.at(0);

    // Find indices of bank reversals (brFlag == 1)
    auto ixBr = find(brFlag);

    if (ixBr.size() == 0) {
        for(unsigned int i=0; i<tu.size(); i++) {
            res.mu.push_back({
                tu.at(i),
                mu.at(i)
            });
        }
        res.tBrInit.push_back(0);
        res.tBrEnd.push_back(0);
        res.brFlag = zeros(N);
        return res;
    } 

    // Using the BRFlag which is one on the elements of 'tu' where a
    // bank reversal is being performed, the initial and ending indexes
    // of each bank reversal are computed
    std::vector<double> dixBr = diff(ixBr);
    std::vector<uint32_t> ixDiffBr = find(vectorGreater(dixBr, 1.0));
    std::vector<uint32_t> ixBrEnd, ixBrInit;
    ixBrInit.push_back(ixBr.at(0));
    for(unsigned int i=0; i<ixDiffBr.size(); i++) {
        ixBrEnd.push_back(ixBr.at(ixDiffBr.at(i)));
        ixBrInit.push_back(ixBr.at(ixDiffBr.at(i)+1));
    }
    ixBrEnd.push_back(ixBr.back());

    uint32_t Nbr = ixBrEnd.size();
    auto brFlagOut = zeros(N);
    res.brFlag = brFlagOut;
    for(unsigned int i=0; i<tu.size(); i++) {
        res.mu.push_back({
            tu.at(i),
            mu.at(i)
        });
    }

    for(unsigned int i=0; i<Nbr; i++) {
        // For each bank reversal the bank angle profile is adjusted
        // Initial states
        double mu0 = res.mu.at(ixBrInit.at(i) - 1).value;
        double muP0 = (res.mu.at(ixBrInit.at(i) - 1).value - res.mu.at(ixBrInit.at(i) - 2).value) / T;

        // Local bank reversal indices
        std::vector<uint32_t> ixBrlocal;
        uint32_t ix = ixBrInit.at(i);
        ixBrlocal.push_back(ix);
        while(ix < ixBrEnd.at(i)) {
            ix++;
            ixBrlocal.push_back(ix);
        }

        // Number of elements in the local segment
        uint32_t NixBR = ixBrlocal.size();

        // Original maneuver time (assuming T is the sampling time)
        double TbrOrg = T * (NixBR + 1);

        double muEndTemp = mu.at(ixBrEnd.at(i) + 1);
        double muPEndTemp = (mu.at(ixBrEnd.at(i) + 2) - mu.at(ixBrEnd.at(i) + 1)) / T;

        double mu10 = muEndTemp - muPEndTemp * TbrOrg;
        double muP10 = muPEndTemp;

        // Initial conditions for maneuver calculation
        double x0 = mu0;
        double v0 = muP0;
        double x10 = mu10;
        double v10 = muP10;

        // The next segment to which the bank angle will belong (safety reasons)
        double nextMR = floor(abs(x10)/pi);

        // Sign of the initial error
        double s0R = std::signbit(x10 - x0);
        double s0 = s0R;

        // The two solutions of the second order polinominal giving the
        // manoeuver time
        double tbrRelA = (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*aMax);
        double tbrRelB = -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)-v10+v0)/(s0*aMax);
    
        double t2 {};
        if(tbrRelA > 0) {
            t2 = tbrRelA;
        } else {
            t2 = tbrRelB;
        }

        // the switching time is chosen
        double tbrRel = t2;
        double tswRel = (s0*t2*aMax+v10-v0)/(2*s0*aMax);

        // the effective final bank angle is computed
        double muFeff = x10 + v10*t2;
        double satmuF = 0;

        // the valid values for final bank angle, where the current
        // segment is not left, are computed
        double muFMin, muFMax;
        if(x10 > 0) {
            muFMin = nextMR*pi;
            muFMax = (nextMR + 1)*pi;
        } else {
            muFMin = -1*(nextMR + 1)*pi;
            muFMax = -1*nextMR*pi;
        }

        // if the future bank angle leaves the segment, its value is
        // adjusted...
        double muFeffR {};    
        if (muFeff > muFMax) {
            satmuF  = 1;
            muFeffR = muFMax;
        }

        if(muFeff < muFMin) {
            satmuF  = -1;
            muFeffR = muFMin;
        }

        // ... and the manoeuver is recalculated for safety reasons
        if (abs(satmuF) > 0.5) {
            x0   = mu0;
            v0   = muP0;
            x10  = muFeffR;
            v10  = 0;

            s0   = sign(x10-x0);

            tbrRelA	=  (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*aMax);
            tbrRelB	= -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*aMax+v10*v10-2*v0*v10+v0*v0)-v10+v0)/(s0*aMax);

            if(tbrRelA > 0) {
                t2 = tbrRelA;
            } else {
                t2 = tbrRelB;
            }

            tbrRel  = t2;
            tswRel	= (s0*t2*aMax+v10-v0)/(2*s0*aMax);
        }

        bool BeforeNxtBrF {false};

        // for (unsigned int j=0; j<N; j++) {
        //     if (i < Nbr) {
        //         if(tu.at(j) <= tBrInitV.at(i+1)) {
        //                 BeforeNxtBrF = 1;
        //         } else {
        //                 BeforeNxtBrF = 0;
        //         }
        //     } else {
        //         BeforeNxtBrF = 1;
        //     }

        // Adjust the bank profile
        // Once the time instants, duration and commmand switching times are
        // available, the bank angle profile is built using the closed form
        // solutions of the bank angle during the bank reversal.
        //res.brFlag = zeros(N);
        res.brFlag = brFlag;

        for (unsigned int j=0; j<N; j++) {
            // if

            if (tu.at(j) > tBrInitV.at(i) && (BeforeNxtBrF==true)) {
                if (tu.at(j) <= (tBrInitV.at(i) + tswRel)) {
                    res.mu.at(j).value = mu0 + muP0*(tu.at(j)- tBrInitV.at(i)) + s0*0.5*aMax*std::pow(tu.at(j)-tBrInitV.at(i), 2);
                    res.brFlag.at(j) = 1;
                } else if (tu.at(j) < (tBrInitV.at(i) + tbrRel)) {
                    res.mu.at(j).value = mu0 + muP0*tswRel + s0*0.5*aMax*std::pow(tswRel, 2) + (muP0 + s0*aMax*tswRel)*(tu.at(j)-(tBrInitV.at(i) + tswRel)) - s0*0.5*aMax*std::pow(tu.at(j)-(tBrInitV.at(i) + tswRel), 2);
                    res.brFlag.at(j) = 1;
                } else {
                    if (tu.at(j) < tu.at(ixBrEnd.at(i) + 1)) {
                        // Incomplete, I dont remeber why this is not
                        // the same as the one on 'AddBankReversalKeep'
                        // function   // TODO : CHECH SECTION
                        res.mu.at(j).value = mu.at(ixBrEnd.at(i) + 1) - muPEndTemp*(tu.at(ixBrEnd.at(i)+1) - tu.at(j));
                    } else {
                        res.mu.at(j).value = mu.at(j);
                    }
                }
            } else {
                res.mu.at(j).value = mu.at(j);
            }
        }
    }

    res.tBrInit = tBrInitV;
    res.tBrEnd = tBrEndV;

    return res;
}

void GEPathPlanning::GetReversedLeftAndRigthBankSt(
    double mu0, double muP0, 
    std::pair<double, double>& mu10, std::pair<double, double>& muP10, std::pair<double, double>& m
) {
    double mO = floor(abs(mu0)/pi) + 1;
    double mu10O = sign(mu0)*2*pi*mO - mu0;
    double muP10O = -muP0;

    double mI = floor(abs(mu0)/pi);
    double mu10I = sign(mu0)*2*pi*mI - mu0;
    double muP10I = -muP0;

    mI = mI - 1;
    if (mI < 0) mI = 0;

    // Swap mu10 and muP10 conditionally based on mu10O and mu0
    if (mu10O < mu0) {
        mu10.first = mu10O;
        mu10.second = mu10I;
        muP10.first = muP10O;
        muP10.second = muP10I;
        m.first = mO;
        m.second = mI;
    } else {
        mu10.second = mu10O;
        mu10.first = mu10I;
        muP10.second = muP10O;
        muP10.first = muP10I;
        m.first = mI;
        m.second = mO;
    }
}

double GEPathPlanning::UnNBR(double muNBR, int mCurr, double sign) {
  double muConv = muNBR;
  bool togg = true;

  for (int i = 0; i < mCurr; i++) {
    if (togg) {
      muConv += 2.0 * (pi - muNBR);
      togg = false;
    } else {
      muConv += 2.0 * muNBR;
      togg = true;
    }
  }

  muConv *= sign;
  return muConv;
}

void GEPathPlanning::simCoM2dof() {
    double dTsim = ms->sim_2dof_input.Tgui;
    double Tsim = ms->sim_2dof_input.t1;

    ms->sim_2dof_output.clear();

    std::array<double, 4> xDR = ms->sim_2dof_input.x0DR;
    std::vector<std::array<double, 4>> xDROut;

    double t_count = 0;
    uint32_t k = 0;
    std::cout << "    [";
    while(t_count < Tsim) {

        // cSndLkUp(R) -> tmp
        //double cSnd = this->ms->radiusLookUpTable.matchAgainst("cSndLkUp", R);
        //double mach = Vw / cSnd;

        double mu = getMuAtTime(ms->sim_2dof_input.uSim, t_count);
        double Vw = xDR.at(2);
        double h  = xDR.at(1);

        // cSndLkUp(h) -> tmp
        double cSnd = this->ms->radiusLookUpTable.matchAgainst("cSndLkUp", h);
        double mach = Vw / cSnd;

        // cDtrimLkUp(mach) -> cD
        double cD = this->ms->machLookUpTable.matchAgainst("cDtrimLkUp", mach);
        // cLtrimLkUp(mach) -> cL
        double cL = this->ms->machLookUpTable.matchAgainst("cLtrimLkUp", mach);
        // rhoNomLkUp(h)
        double rho = this->ms->radiusLookUpTable.matchAgainst("rhoNomLkUp", h);

        // RUNNING COM 3]2DOF Detailed Simulation
        auto simOut = CoM2DOF(
            xDR,
            mu,
            {cD, cL},
            rho
        );

        for(unsigned int i=0; i<4; i++) {
            xDR.at(i) = xDR.at(i) + dTsim * simOut.xDotOut.at(i);
        }

        // Collecting partial results...
        ms->sim_2dof_output.uOut.push_back(mu);
        xDROut.push_back(xDR);

        t_count += dTsim;
        k++;

        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        if(k % ((uint32_t)Tsim / 50) == 0) { 
            std::cout << "#";
            std::cout.flush(); 
        }
    }
    std::cout << "]\n";

    // Collecting results...
    //Log::info("GE", "Collecting results of simCom2DOF detailed...");
    ms->sim_2dof_output.xDROut = MatrixT(xDROut);
    // 
    std::cout << "-------------------------------------\n";
}

void GEPathPlanning::simCoM3dof() {
    double dTsim = ms->TimeStepsNSF.Tgui;
    double Tsim  = ms->NominalMissionNSF.tPDPNom;

    // Initialize CoM x0
    std::array<double, 6> xCoM = ms->CoMNomX0NSF.xCoMNomEIP;

    // Prepare output
    std::vector<std::array<double, 6>> xCoMNom;
    std::vector<double> cDNomProf;
    std::vector<double> cLNomProf;
    std::vector<double> rhoNomProf;
    std::vector<double> FDNom;
    std::vector<double> FLNom;
    std::vector<std::array<double, 6>> xCoMdotNom;
    std::vector<double> machNom;
    std::vector<std::array<double, 3>> gNEDNom;

    double t_count = 0;
    uint32_t k = 0;
    std::cout << "    [";
    while(t_count < Tsim) {
        // Grav(R) -> gNED
        std::array<double, 3> gNED = GEGrav::GE_Grav_Exec(ms->PlanetGrav, xCoM);
        double Vw = xCoM.at(3);
        double R  = xCoM.at(0);

        // cSndLkUp(R) -> tmp
        double cSnd = this->ms->radiusLookUpTable.matchAgainst("cSndLkUp", R);
        double mach = Vw / cSnd;

        // cDtrimLkUp(mach) -> cD
        double cD = this->ms->machLookUpTable.matchAgainst("cDtrimLkUp", mach);
        // cLtrimLkUp(mach) -> cL
        double cL = this->ms->machLookUpTable.matchAgainst("cLtrimLkUp", mach);
        // rhoNomLkUp(R)
        double rho = this->ms->radiusLookUpTable.matchAgainst("rhoNomLkUp", R);
        
        double mu = this->getMuAtTime(nominal_traj.mu, t_count);

        // RUNNING COM 3DOF Detailed Simulation
        auto simOut = CoM3DOF(
            xCoM,
            gNED,
            {cD, cL},
            rho,
            mu
        );

        // Collecting partial results...
        cDNomProf.push_back(cD);
        cLNomProf.push_back(cL);
        rhoNomProf.push_back(simOut.rho);
        FDNom.push_back(simOut.FD);
        FLNom.push_back(simOut.FL);
        // FaWASNom
        xCoMdotNom.push_back(simOut.xDotOut);
        machNom.push_back(mach);
        gNEDNom.push_back(gNED);

        for(unsigned int i=0; i<6; i++) {
            xCoM.at(i) = xCoM.at(i) + dTsim * simOut.xDotOut.at(i);
        }
        xCoMNom.push_back(xCoM);

        t_count += dTsim;
        k++;

        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        if(k % ((uint32_t)Tsim / 50) == 0) { 
            std::cout << "#";
            std::cout.flush(); 
        }
    }
    std::cout << "]\n";

    // Collecting results...
    //Log::info("GE", "Collecting results of simCom3DOF detailed...");
    ms->sim3dof_out.xCoM = MatrixT(xCoMNom);
    ms->sim3dof_out.cDProf = cDNomProf;
    ms->sim3dof_out.cLProf = cLNomProf;
    ms->sim3dof_out.rhoProf = rhoNomProf;
    ms->sim3dof_out.FD = FDNom;
    ms->sim3dof_out.FL = FLNom;
    //ms->sim3dof_out.FaWASNom = FaWASNom;
    ms->sim3dof_out.xCoMDot = MatrixT(xCoMdotNom);
    ms->sim3dof_out.mach = machNom;
    ms->sim3dof_out.gNED = gNEDNom;

    std::array<double, 6> xCoMPDP = xCoMNom.back();
    double machNomPDP = machNom.back();
    return;
}

double GEPathPlanning::getMuAtTime(std::vector<TimeSeriesItem> uSim, double t) {
    double res = 0.00;

    double num_threshold = 0.000001;
    bool found = false;
    for(unsigned int i=0; i<uSim.size() && !found; i++) {
        if((t > uSim.at(i).t - num_threshold) && (t < uSim.at(i).t + num_threshold)) {
            res = uSim.at(i).value;
            found = true;
        }
    }

    return res;
}

void GEPathPlanning::randomizeNSFstr(NSFStr& inputStr) {
    for(unsigned int i=0; i<inputStr.ids.size(); i++) {
            if(inputStr.unctype.at(i) == 0) {
                // no randomization
                inputStr.valuesR.push_back(inputStr.values.at(i));
            } else if (inputStr.unctype.at(i) == 1) {
                // gaussian distribution
                inputStr.valuesR.push_back(
                    inputStr.values.at(i) + abs(inputStr.uncminv.at(i)/3)*randn()*ms->first
                ); 
            } else if (inputStr.unctype.at(i) == 2) {
                // uniform distribution
                inputStr.valuesR.push_back(0.00);
            } else if (inputStr.unctype.at(i) == 3) {
                // gaussian saturated 3 sigma
                inputStr.valuesR.push_back(0.00);
            } else {
                Log::err("PP", "Error while randomizing data. Invalid uncertainty type.");
            }
    }
}

OptimalTimeResultStr GEPathPlanning::findOptimalTime() {
    Log::warn("PP", "finding optimal time...");

    double TGui = ms->TimeStepsNSF.Tgui;

    // input
    double Raeroid {};

    uint32_t Nit = 4;
    std::array<double, 4> xDR0m = {
        0, // downrange
        ms->CoMNomX0NSF.r0Nom - Raeroid,
        ms->CoMNomX0NSF.vAbs0Nom,
        ms->CoMNomX0NSF.fpa0Nom
    };

    std::array<double, 4> dxDR0 = {
        1, // dRYHEIP(1)
        1, // dSYHEIP(3)
        1, // dVGCEIP(1)
        1  // dVGCEIP(2)
    };

    double TDR = ms->TimeStepsNSF.Tgui;
    auto x0DR = xDR0m;

    ms->sim_2dof_input.Tgui = TDR;
    ms->sim_2dof_input.t1 = ms->NominalMissionNSF.tPDPNom + 20;
    ms->sim_2dof_input.tSim = this->nominal_traj.tSim;
    ms->sim_2dof_input.uSim = this->nominal_traj.mu;
    ms->sim_2dof_input.x0DR = x0DR;

    this->simCoM2dof();

    auto xOut = ms->sim_2dof_output.xDROut;
    auto uOut = ms->sim_2dof_output.uOut;

    std::vector<uint32_t> ixHigher = vectorGreater(xOut.getCol(1), this->nominal_traj.xCoM.getLastRow().at(0) - Raeroid);
    std::vector<uint32_t> ixTemp = find(ixHigher);
    uint32_t ixPDPDR = ixTemp.back();
    double tPDPDR = ms->sim_2dof_input.tSim.at(ixPDPDR);

    // Saving down range data
    std::vector<double> tSimDRNom = vectorSlice(ms->sim_2dof_input.tSim, {0, ixPDPDR});
    std::vector<double> uDRNom    = vectorSlice(uOut, {0, ixPDPDR});
    MatrixT xDRNom = MatrixT::sliceRows(xDRNom, {0, ixPDPDR});

    std::vector<double> xPDPDR_vec = xDRNom.backRow();
    std::array<double, 6> xPDPDR {
        xPDPDR_vec.at(0),
        xPDPDR_vec.at(1),
        xPDPDR_vec.at(2),
        xPDPDR_vec.at(3),
        xPDPDR_vec.at(4),
        xPDPDR_vec.at(5),
    };

    // GE Solution 0
    x0DR = array4Sum(xDR0m, dxDR0);
    auto Ndisc = tPDPDR/TDR + 1;

    ms->sim_lin_sol_input.t1 = tPDPDR;
    ms->sim_lin_sol_input.tSim = linspace(0, tPDPDR, Ndisc);
    ms->sim_lin_sol_input.uSim = vectorSlice(this->nominal_traj.collectMu(), {0, ixPDPDR});

    this->simLinSolDR(ms->CoMNomX0NSF.xCoMNomEIP, xPDPDR, TGui, Nit);

    auto tSim0 = ms->sim_lin_sol_output.tSim;
    auto uOut0 = ms->sim_lin_sol_output.uOut;
    auto xOut0 = ms->sim_lin_sol_output.xOut;

    // GE Solution 1a
    auto tSimSol = tSim0;
    auto uOutSol = uOut0;

    x0DR = array4Sum(xDR0m, dxDR0);

    ms->sim_lin_sol_input.t1 = tPDPDR;
    Ndisc = ms->sim_lin_sol_input.t1/TGui + 1;
    ms->sim_lin_sol_input.tSim = linspace(0, ms->sim_lin_sol_input.t1, Ndisc);
    //ms->sim_lin_sol_input.uSim = ScaleSignal(tSimSol,uOutSol,ms->sim_lin_sol_input.tSim);
    
    this->simLinSolDR(ms->CoMNomX0NSF.xCoMNomEIP, xPDPDR, TGui, Nit);
    
    auto tSim1a = ms->sim_lin_sol_output.tSim;
    auto uOut1a = ms->sim_lin_sol_output.uOut;
    auto xOut1a = ms->sim_lin_sol_output.xOut;

    // GE Solution 1b
    // tSimSol     = tSim0;
    // uOutSol     = uOut0;

    auto dt = TGui;
    x0DR = array4Sum(xDR0m, dxDR0);

    ms->sim_lin_sol_input.t1 = tPDPDR + dt;
    Ndisc       = ms->sim_lin_sol_input.t1/TGui + 1;
    ms->sim_lin_sol_input.tSim = linspace(0, ms->sim_lin_sol_input.t1, Ndisc);
    // uSim        = ScaleSignal(tSimSol,uOutSol,tSim);

    this->simLinSolDR(ms->CoMNomX0NSF.xCoMNomEIP, xPDPDR, TGui, Nit);

    auto tSim1b = ms->sim_lin_sol_output.tSim;
    auto uOut1b = ms->sim_lin_sol_output.uOut;
    auto xOut1b = ms->sim_lin_sol_output.xOut;

    // Initial Gradient
    auto ug0 = ms->NominalMissionNSF.ugNom;
    auto tmp = vectorAbs(vectorScalarSub(uOut1a, ug0));
    auto hInf1a = *std::max_element(tmp.begin(), tmp.end());
    tmp = vectorAbs(vectorScalarSub(uOut1b, ug0));
    auto hInf1b = *std::max_element(tmp.begin(), tmp.end());
    tmp = vectorAbs(uOut1a);
    auto hInfTot1a = *std::max_element(tmp.begin(), tmp.end());
    tmp = vectorAbs(uOut1b);
    auto hInfTot1b = *std::max_element(tmp.begin(), tmp.end());
    auto h11a = sumVectorElements(vectorAbs(vectorScalarSub(uOut1a, ug0)));
    auto h11b = sumVectorElements(vectorAbs(vectorScalarSub(uOut1b, ug0)));
    tmp = vectorScalarSub(uOut1a, ug0);
    auto h21a = vectorScalarProd(tmp, tmp);
    tmp = vectorScalarSub(uOut1b, ug0);
    auto h21b = vectorScalarProd(tmp, tmp);

    std::vector<double> dtV = { 0, dt };
    std::vector<double> hInfTotV = { hInfTot1a, hInfTot1b };
    std::vector<double> hInfV = { hInf1a, hInf1b };
    std::vector<double> h1V = { h11a, h11b };
    std::vector<double> h2V = { h21a, h21b };

    double dudt = (hInf1b - hInf1a)/dt;
    auto s0 = sign(dudt);

    auto tSimLast = tSim1b;
    auto uOutLast = uOut1b;
    auto xOutLast = xOut1b;
    auto hInfLast = hInf1b;
    auto k = 2;

    if(s0 == -1) {
        tSimLast = tSim1a;
        uOutLast = uOut1a;
        xOutLast = xOut1a;
        hInfLast = hInf1a;
        k = 1;
    }

    tmp = xOutLast.getLastRow();
    std::array<double, 6> ePDPLast;
    for(unsigned int i=0; i<tmp.size(); i++) {
        ePDPLast.at(i) = tmp.at(i) - xPDPDR.at(i);
    }

    std::vector<double> tSimNew {};
    auto s0New = s0;

    while(s0New == s0) {
        //for(unsigned int m=0; m<Nit; m++) {
        // GE Solution k-th
        tSimSol = tSimLast;
        uOutSol = uOutLast;

        dt = -s0*TGui*k;
        x0DR = array4Sum(xDR0m, dxDR0);
        
        ms->sim_lin_sol_input.t1 = tPDPDR + dt;
        Ndisc       = ms->sim_lin_sol_input.t1/TGui + 1;
        ms->sim_lin_sol_input.tSim = linspace(0, ms->sim_lin_sol_input.t1, Ndisc);
        // uSim        = ScaleSignal(tSimSol,uOutSol,tSim);

        this->simLinSolDR(ms->CoMNomX0NSF.xCoMNomEIP, xPDPDR, TGui, Nit);

        tSimNew = ms->sim_lin_sol_output.tSim;
        auto uOutNew = ms->sim_lin_sol_output.uOut;
        auto xOutNew = ms->sim_lin_sol_output.xOut;
        std::array<double, 6> ePDPNew;
        tmp = ms->sim_lin_sol_output.xOut.getLastRow();
        for(unsigned int i=0; i<tmp.size(); i++) {
            ePDPNew.at(i) = tmp.at(i) - xPDPDR.at(i);
        }

        auto hInfTotNew = *std::max_element(uOutNew.begin(), uOutNew.end());
        tmp = vectorAbs(vectorScalarSub(uOutNew, ug0));
        auto hInfNew = *std::max_element(tmp.begin(), tmp.end());
        auto h1New = sumVectorElements(vectorAbs(vectorScalarSub(uOutNew, ug0)));
        tmp = vectorScalarSub(uOutNew, ug0);
        auto h2New = vectorScalarProd(tmp, tmp);

        dtV.push_back(dt);
        hInfTotV.push_back(hInfTotNew);
        hInfV.push_back(hInfNew);
        h1V.push_back(h1New);
        h2V.push_back(h2New);

        dudt        = (hInfNew - hInfLast)/dt;
        s0New       = sign(dudt); 

        hInfLast    = hInfNew;
        tSimLast    = tSimNew;
        uOutLast    = uOutNew;

        k = k+1;
    }

    auto tPDPDRSol = tSimNew.back();
    auto dtPDP = tPDPDRSol - tPDPDR;
    auto tPDPGui = ms->NominalMissionNSF.tPDPNom + dtPDP;
    Ndisc = tPDPGui/TDR + 1;
    auto tSimDRSol = linspace(0,tPDPGui,Ndisc);
    auto N = tSimNew.size();
    // uOptNBR = ScaleSignal(tSim,uOutNew,tSimDRSol);
    auto tBrVNom2 = vectorScalarMul(1/ms->NominalMissionNSF.tPDPNom, vectorScalarMul(tPDPGui, ms->NominalMissionNSF.tBrVNom));  
    auto t1 = tPDPGui;
    // uOptNBRunSat    = ScaleSignal(tSim,uOutNew,tSimDRSol);
    // uOptNBR         = Sat(uOptNBRunSat,-1,1);

    // Results
    OptimalTimeResultStr res = {
        tSimNew,
        tPDPDRSol,
        dtPDP,
        tPDPGui,
        Ndisc,
        tSimDRSol,
        N,
        tBrVNom2,
        t1,
        // uOptNBRunSat,
        // uOptNBR
    };

    return res;
}

void GEPathPlanning::simLinSolDR(std::array<double, 6> x0, std::array<double, 6> xPDP, double TDR, uint32_t Nit) {
    std::vector<double> xPDP_vec = {
        xPDP.at(0),
        xPDP.at(1),
        xPDP.at(2),
        xPDP.at(3),
        xPDP.at(4),
        xPDP.at(5),
    };

    auto Ndisc = ms->sim_lin_sol_input.tSim.size();
    
    this->ms->sim_lin_sol_output.tSim = ms->sim_lin_sol_output.tSim;
    this->ms->sim_lin_sol_output.uOut = ms->sim_lin_sol_output.uOut;

    // Sim2DOF simulation
    this->simCoM2dof();

    auto xOut = ms->sim_2dof_output.xDROut;
    MatrixT vgh = MatrixT({
        xOut.getCol(2),
        xOut.getCol(3),
        xOut.getCol(1)
    });

    auto A = zeros(4, 4, Ndisc);
    auto B = zeros(4, 1, Ndisc);

    auto itFlag = 1;
    auto duOut = zeros(Ndisc);

    for(unsigned int i=0; i<Nit; i++) {
        auto dxPDP = vectorSub(xOut.backRow(), xPDP_vec); 

        auto out = this->BuildDRContMat_02(vgh, ms->sim_lin_sol_input.uSim, TDR);
        auto ContMat = out.ContMat;
        auto gProf = out.gProf;

        auto invQ = MatrixT::diag(vectorAbs(gProf));
        // Nsz     = length(ContMat');    
        // invQ    = eye(length(gProf));

        auto dxm = vectorScalarMul(-1, dxPDP);
        auto tmp1 = MatrixT::matrixMul(invQ, MatrixT::transpose(ContMat));
        auto tmp2 = MatrixT::matrixMul(ContMat, MatrixT::matrixMul(invQ, MatrixT::transpose(ContMat)));
        auto tmp3 = MatrixT::matrixMul(tmp1, tmp2);
        auto dug = LSsolve(tmp3, dxm, tmp1.size().at(0), tmp1.size().at(1));

        auto exPol = dug.back() + (dug.back() - dug.at(dug.size()-2));
        dug.push_back(exPol);
        duOut = dug;

        this->ms->sim_lin_sol_output.uOut = 
            vectorSum(this->ms->sim_lin_sol_output.uOut, duOut);

        ms->sim_2dof_input.tSim = this->ms->sim_lin_sol_output.tSim;

        std::vector<TimeSeriesItem> uSim {};
        for(unsigned int k=0; k<ms->sim_lin_sol_output.tSim.size(); k++) {
            uSim.push_back({
                ms->sim_lin_sol_output.tSim.at(k),
                ms->sim_lin_sol_output.uOut.at(k)
            });
        }
        ms->sim_2dof_input.uSim = uSim;

        this->simCoM2dof();

        xOut = ms->sim_2dof_output.xDROut;
        auto uOut = ms->sim_2dof_output.uOut;

        vgh = MatrixT({
            xOut.getCol(2),
            xOut.getCol(3),
            xOut.getCol(1)
        });
    }

    this->ms->sim_lin_sol_output.duOut = duOut;
    //this->ms->sim
}

DRContMatOut GEPathPlanning::BuildDRContMat_02(MatrixT vgh, std::vector<double> uOut, double TDR) {
    double T = TDR;
    double g = ms->parDRCell.gravDR;
    double m = ms->parDRCell.massDR;
    double Sref = ms->parDRCell.SrefDR;
    double Raeroid = ms->parDRCell.Raeroid;
    double R0 = ms->parDRCell.R0;
    double cHatm = ms->parDRCell.cHatm;

    auto N = vgh.size().at(1);
    auto vAbs = vgh.getCol(0);
    auto fpa = vgh.getCol(1);
    auto h = vgh.getCol(2);

    auto A = zeros(4, 4, N-1);
    //auto B = zeros(4, 1, N-1);
    auto gProf = zeros(N-1);

    MatrixT ContMat = zeros(4, N-1);
    auto R = h.at(N-1) + Raeroid;

    auto rho = ms->radiusLookUpTable.matchAgainst("rhoNomLkUp", R);
    auto cSnd = ms->radiusLookUpTable.matchAgainst("cSndLkUp", R);
    auto mach = vAbs.at(N-1)/cSnd;
    auto cD = ms->machLookUpTable.matchAgainst("cDtrimLkUp", mach);
    auto cL = ms->machLookUpTable.matchAgainst("cLtrimLkUp", mach);
    
    // auto Hatm = 
    double Hatm {};
    
    auto bmg = 1/(2*m)*rho*vAbs.at(N-1)*cL*Sref;
    std::vector<double> B = {
        0, 0, 0, bmg
    };

    auto BdEnd = vectorScalarMul(T, B);

    ContMat = MatrixT::fillBackCol(ContMat, BdEnd);
    auto An = MatrixT::eye(4);

    uint32_t k = 0;
    while(k<N-2) {
        R = h.at(N-k) + Raeroid;

        rho = ms->radiusLookUpTable.matchAgainst("rhoNomLkUp", R);
        cSnd = ms->radiusLookUpTable.matchAgainst("cSndLkUp", R);
        mach = vAbs.at(N-1)/cSnd;
        cD = ms->machLookUpTable.matchAgainst("cDtrimLkUp", mach);
        cL = ms->machLookUpTable.matchAgainst("cLtrimLkUp", mach);

        Hatm = 1; // TODO

        double gvv = -vAbs.at(N-k)/m*rho*cD*Sref;
        double ghv = 1/(2*m*Hatm)*rho*std::pow(vAbs.at(N-k),2)*cD*Sref;
        double ggv = -g*cos(fpa.at(N-k));

        double gvg = 1/(2*m)*rho*cL*Sref*uOut.at(N-k) + 1/std::pow(vAbs.at(N-k),2)*g*cos(fpa.at(N-k)) + 1/R*cos(fpa.at(N-k));
        double ghg = -1/(2*m*Hatm)*rho*vAbs.at(N-k)*cL*Sref*uOut.at(N-k);
        double ggg = -(vAbs.at(N-k)/R - g/vAbs.at(N-k))*sin(fpa.at(N-k));

        double gvs = cos(fpa.at(N-k));
        double ggs = -vAbs.at(N-k)*sin(fpa.at(N-k));
        double gvh = sin(fpa.at(N-k));
        double ggh = vAbs.at(N-k)*cos(fpa.at(N-k));

        std::vector<std::vector<double>> data = {
            { 0.0, 0.0, gvs, ggs },
            { 0.0, 0.0, gvh, ggh },
            { 0.0, ghv, gvv, ggv },
            { 0.0, ghg, gvg, ggg }
        };
        auto Anm1 = MatrixT(data);

        bmg = 1/(2*m)*rho*vAbs.at(N-k)*cL*Sref;
        
        std::vector<double> Bnm2 = {
            0, 0, 0, bmg
        };

        auto Anm1d = MatrixT::matrixSum(MatrixT::eye(4), MatrixT::scalarMul(T, Anm1));
        auto Bnm2d = vectorScalarMul(T, Bnm2);

        An = MatrixT::matrixMul(An, Anm1d);

        ContMat.fillCol(N-k, MatrixT::matrixMul(An, Bnm2d));
        gProf.at(N-k) = bmg*ggh;
        //gProf.at(N-k) = bmg;

        k++;
    }
    
    return {
        ContMat,
        A,
        B,
        gProf
    };
}

double GEPathPlanning::randn() {
    return ms->rg.dis(ms->rg.rand_gen);
}

void GEPathPlanning::GetErrSYH(MatrixT xNom0, MatrixT x) {
    auto xRMNom0 = RmCoord(xNom0.getCol(0), xNom0.getCol(1), xNom0.getCol(2));
    auto xRM = RmCoord(x.getCol(0), x.getCol(1), x.getCol(2));
    auto dxRM =  MatrixT::matrixSub(xRM, xRMNom0);
    auto dLV = NED2LVFunc(xNom0.getCol(5), MARS2NEDFunc(xNom0.getCol(1),xNom0.getCol(2),dxRM));
    
    dSYH.insertCol(dLV.getCol(0), 0);
    dSYH.insertCol(vectorScalarMul(-1, dLV.getCol(1)), 1);
    dSYH.insertCol(vectorScalarMul(-1, dLV.getCol(2)), 2);

    dVGC.insertCol(vectorSub(x.getCol(3), xNom0.getCol(3)), 0);
    dVGC.insertCol(vectorSub(x.getCol(4), xNom0.getCol(4)), 1);
    dVGC.insertCol(vectorSub(x.getCol(5), xNom0.getCol(5)), 2);
}

MatrixT GEPathPlanning::RmCoord(std::vector<double> r, std::vector<double> lon, std::vector<double> lat) {
    MatrixT res;

    res.insertCol(vectorMul(vectorMul(r, vectorCos(lon)), vectorCos(lat)), 0);
    res.insertCol(vectorMul(vectorMul(r, vectorSin(lon)), vectorCos(lat)), 1);
    res.insertCol(vectorMul(r, vectorSin(lat)), 2);

    return res;
}

MatrixT GEPathPlanning::MARS2NEDFunc(std::vector<double> lon, std::vector<double> lat, MatrixT x) {
    auto sz = x.size();
    auto Np = sz.at(0);

    MatrixT res = MatrixT(Np, 3);

    for(unsigned int i=0; i<Np; i++) {
        MatrixT T;
        T.data = {
            { sin(lat.at(i))*cos(lon.at(i)),  -sin(lat.at(i))*sin(lon.at(i)),  cos(lat.at(i)) },
            {                sin(lon.at(i)),                  cos(lon.at(i)),               0 },
            { cos(lat.at(i))*cos(lon.at(i)),  -cos(lat.at(i))*sin(lon.at(i)), -sin(lat.at(i)) }
        };

        std::vector<double> tmp = MatrixT::matrixMul(T, x.getRow(i));
        res.fillRow(i, tmp);
    }

    return res;
}

MatrixT GEPathPlanning::NED2LVFunc(std::vector<double> c, MatrixT x) {
    auto sz = x.size();
    auto Np = sz.at(0);

    MatrixT y = MatrixT(Np, 3);
    auto cc = vectorCos(c);
    auto sc = vectorSin(c);

    for(unsigned int i=0; i<Np; i++) {
        MatrixT T;
        T.data = {
            {  cc.at(i), sc.at(i),   0 },
            { -sc.at(i), cc.at(i),   0 },
            {         0,        0,   1 }
        };

        y.fillRow(i, MatrixT::matrixMul(T, x.getRow(i)));
    }

    return y;
}

bool GEPathPlanning::writeGuidanceData(const std::string& filename, GuidanceProfileOutStr gui_profile) {
    // Open the file for output in text mode
    // std::ofstream outfile(filename);

    // // Check if the file was opened successfully
    // if (outfile.is_open()) {
    //     // Loop through each element in the data vector
    //     for (const T& element : data) {
    //         // Write the element to the file, followed by a newline character
    //         outfile << element << "\n";
    //     }
    //     outfile.close();

    //     Log::info("RW", "Nominal trajectory written to file: %s", filename.c_str());
    // } else {
    //     Log::err("RW", "Error opening file: %s", filename.c_str());
    //     return false;
    // }

    auto fp1 = fopen((filename + "Long.DHS").c_str(),"w");

    fprintf(fp1,"/* File1 automatically generated by BuildGuidanceTrajectory.m */\n");
    fprintf(fp1,"/* 1 - Dimension of planned bank angle */\n");
    fprintf(fp1,"%.6g\n", (double) ms->gui_profile_out.uMuRs.size());
    fprintf(fp1,"/* 2 - uMuGuiRs*/\n");
    for(unsigned int i=0; i<ms->gui_profile_out.uMuRs.size(); i++) {
        fprintf(fp1,"%.6g\n", ms->gui_profile_out.uMuRs.at(i));
    }
    fprintf(fp1,"/* 3 - muGuiRs*/\n");
    for(unsigned int i=0; i<ms->gui_profile_out.muRs.size(); i++) {
        fprintf(fp1,"%.6g\n", ms->gui_profile_out.muRs.at(i));
    }
    fprintf(fp1,"/* 4 - xCoMGuiRs*/\n");
    for(unsigned int i=0; i<ms->gui_profile_out.xCoMRs.size().at(0); i++) {
        for(unsigned int j=0; j<5; j++) {
            fprintf(fp1,"%.6g ", ms->gui_profile_out.xCoMRs.get(i, j));
        }
        fprintf(fp1,"%.6g\n", ms->gui_profile_out.xCoMRs.data.at(i).back());
    }
    fprintf(fp1,"/* 5 - gNEDGuiRs*/\n");
    for(unsigned int i=0; i<ms->gui_profile_out.gNED.size(); i++) {
        for(unsigned int j=0; j<2; j++) {
            fprintf(fp1,"%.6g ", ms->gui_profile_out.gNED.at(i).at(j));
        }
        fprintf(fp1,"%.6g\n", ms->gui_profile_out.gNED.at(i).back());
    }

    fclose(fp1);


    fp1 = fopen((filename + "Tran.DHS").c_str(),"w");

    fprintf(fp1,"/* File2 automatically generated by path planner */\n");
    fprintf(fp1,"/* 1 - tBrmGui*/\n");
    for(unsigned int i=0; i<ms->gui_profile_out.tBrV.size(); i++) {
        fprintf(fp1,"%.6g\n", ms->gui_profile_out.tBrV.at(i));
    }
    fprintf(fp1,"/* 2 - dirBrmGui*/\n");
    for(unsigned int i=0; i<ms->gui_profile_out.dirBr.size(); i++) {
        fprintf(fp1,"%.6g\n", ms->gui_profile_out.dirBr.at(i));
    }

    fclose(fp1);

    return true;
};