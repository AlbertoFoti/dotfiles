#include "GE_Path_Planning.hxx"
#include "Utils.hxx"
#include "DataReaderWriter.hxx"
#include "CoM3DOF/CoM3DOF.hxx"
#include "Grav/GE_Grav01.hxx"
#include <iostream>
#include <algorithm>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <thread>


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

void GEPathPlanning::randomizeAndInitialize() {
    Log::info("PP", "Randomize and Initialize step...");

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
    Log::err("AT", "EMCD43 database not connected.");

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

        // Save results
        // xCoMNom, muNom, tSimNom

        // Post processing

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

    Log::done("PP", "Nominal mission trajectory built.");
    return brms;
}

void GEPathPlanning::buildGuidanceTrajectory() {
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
    auto temp = find_vectorial(tu, tbr);

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
    auto ixBr = find_vectorial<double>(brFlag, 0.5);

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
    auto dixBr = diff(ixBr);
    std::vector<uint32_t> ixDiffBr = find_vectorial<uint32_t>(dixBr, 1);
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
        double rho = 1;
        
        double mu = this->getMuNomAtTime(t_count);

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
        xCoMdotNom.push_back(simOut.xDotOut);
        machNom.push_back(mach);
        gNEDNom.push_back(gNED);

        for(unsigned int i=0; i<6; i++) {
            xCoM.at(i) = xCoM.at(i) + dTsim * simOut.xDotOut.at(i);
        }
        xCoMNom.push_back(xCoM);

        t_count += dTsim;
        k++;

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if(k % ((uint32_t)Tsim / 50) == 0) { 
            std::cout << "#";
            std::cout.flush(); 
        }
    }
    std::cout << "]\n";

    // Collecting results...
    //Log::info("GE", "Collecting results of simCom3DOF detailed...");
    std::array<double, 6> xCoMPDP = xCoMNom.back();
    double machNomPDP = machNom.back();

    // Nominal PDP State
    std::cout << "-------------------------------------\n";
    std::cout << "Nominal PDP State\n";
    std::cout << "  tPDP    : " << ms->NominalMissionNSF.tPDPNom << " s\n";
    std::cout << "  Alt     : [-needs ATM_EMCD435-]" << " km\n";
    std::cout << "  Lon     : " << xCoMPDP.at(1)*RAD2DEG << " deg\n";
    std::cout << "  Lat     : " << xCoMPDP.at(2)*RAD2DEG << " deg\n"; 
    std::cout << "  vAbs    : " << xCoMPDP.at(3) << " m/s\n";
    std::cout << "  FPA     : " << xCoMPDP.at(4)*RAD2DEG << " deg\n";
    std::cout << "  Heading : " << xCoMPDP.at(5)*RAD2DEG << " deg\n";
    std::cout << "  Mach    : " << machNomPDP << "\n"; 
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
    return;
}

double GEPathPlanning::getMuNomAtTime(double t) {
    double res = 0;

    double num_threshold = 0.000001;
    bool found = false;
    for(unsigned int i=0; i<nominal_traj.mu.size() && !found; i++) {
        if((t > nominal_traj.mu.at(i).t - num_threshold) && (t < nominal_traj.mu.at(i).t + num_threshold)) {
            res = nominal_traj.mu.at(i).value;
            found = true;
        }
    }

    return res;
}