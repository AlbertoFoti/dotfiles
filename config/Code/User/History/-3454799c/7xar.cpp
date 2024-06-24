/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: GE_Guidance.cpp,v 1.1 2022/09/01 14:38:20 ludovico.garin Exp $

$Name:  $

$State: Exp $

*/
#include "GE_GNC.hxx"
#include "GE_Guidance.hxx"
#include "E2E_define.hxx"
using namespace GE_GNC_utils;

void GE_Guidance_class::GE_GUI_Read(void)
{
  {  
   E2E_ReadFile file("GEguidance", "DHS");
 
/*  (1.1) P_TCon Discrete Control simulation time [s] */
    file.readReal(&GUI.P_TCon);  
/*  (1.2) P_machInLkUp[37]  mach input divisions for LUTs depending on mach */
    file.readReal(GUI.P_machInLkUp, 37);
/*  (1.3) P_cDtrimLkUp[37] cD output divisions for LUT depending on mach */
    file.readReal(GUI.P_cDtrimLkUp, 37);
/*  (1.4) P_cLtrimLkUp[37] cL output divisions for LUT depending on mach */
    file.readReal(GUI.P_cLtrimLkUp, 37);
/*  (1.5) P_cNtrimLkUp[37] cN output divisions for LUT depending on mach */
    file.readReal(GUI.P_cNtrimLkUp, 37);
/*  (1.6) P_tauNtrimLkUp[37] tauN output divisions for LUT depending on mach */
    file.readReal(GUI.P_tauNtrimLkUp, 37);
/*  (1.7) P_RinLkUp[1000] Radius input divisions for LUTs depending on Radius */ 
    file.readReal(GUI.P_RinLkUp, 1000);
/*  (1.8) P_cSndLkUp[1000] Sound output divisions for LUT depending on Radius */
    file.readReal(GUI.P_cSndLkUp, 1000);
/*  (1.9) P_rhoNomLkUp[1000] rho output divisions for LUT depending on Radius */
    file.readReal(GUI.P_rhoNomLkUp, 1000);
/*  (1.10) P_HatmLkUpFilt[1000] Hatm output divisions for LUT depending on Radius */
    file.readReal(GUI.P_HatmLkUpFilt, 1000);
  }
  {   
   E2E_ReadFile file("GEguidanceInit", "DHS");
     
/*  (1.1) Initial value of the estimated bank angle [rad] */
    file.readReal(&GUI.P_muGui0);  
/*  (1.2) Initial value of the estimated bank angular rate [rad/s] */
    file.readReal(&GUI.P_omgMuGui0);
  }  
  
}

void GE_Guidance_class::GE_GUI_Init(double *xMuGui)
{     
   GUI.D_CS  = 0; /* Current Step Nav Con loop*/
// GUI.D_CS2 = 0; /* Current monitoring step */
// GUI.D_SavedCS = 0; /* Saved Counter to determines cycles of 10 Nav/Con steps */
   xMuGui[0]=GUI.P_muGui0;    /* Initial Bank Angle */
   xMuGui[1]=GUI.P_omgMuGui0; /* Initial Bank Omega */

   // ----- Path Planning Phase --------
   //
   GE_GUI_PathPlanning();

   // ----------------------------------

   // Collecting results from the Path Planning phase
  {
   E2E_ReadFile file("Path_Planner/GEpathplannerINPUTFILES/GEpathplannerLong", "DHS");
 
/*  (1.1) Planned command of the bank angle */
    file.readReal(GUI.P_uMuGuiRs, 2411);  
/*  (1.2) Planned bank angle */
    file.readReal(GUI.P_MuGuiRs, 2411);
/*  (1.3) Planned CoM state vector */
    file.readReal(GUI.P_xCoMGuiRs, 2411, 6);
/*  (1.4) Planned gravity vector */
    file.readReal(GUI.P_gNEDGuiRs, 2411, 3);
  }

}

void GE_Guidance_class::GE_GUI_Exec(double *xCoMGui, double *DragLift, double *RhoHatm, double *cNtauN, double *gNED, double *xMuGui, double *uMuGui)                                
        
{

int i,j;
double Vw, Radius, vSound, machNav;
    
 for (i=0; i<6; i++)
 {  
     xCoMGui[i] = GUI.P_xCoMGuiRs[GUI.D_CS][i];   /* Output 1 of the Simulink schematic */
 }
 *uMuGui = GUI.P_uMuGuiRs[GUI.D_CS];         /* Output 2 of the Simulink schematic */
 
 xMuGui[0]=xMuGui[0] + GUI.P_TCon*xMuGui[1] + 0.5*GUI.P_TCon*GUI.P_TCon**uMuGui;  /* Output 3 of the Simulink schematic */
 xMuGui[1]=                   xMuGui[1] +     GUI.P_TCon**uMuGui;  /* Output 3 of the Simulink schematic */ 
                                   
 Vw = GUI.P_xCoMGuiRs[GUI.D_CS][3];
 Radius = GUI.P_xCoMGuiRs[GUI.D_CS][0];
 
 vSound = lookup(GUI.P_RinLkUp, GUI.P_cSndLkUp, Radius, 1000);
 machNav=Vw/vSound;
 DragLift[0] = lookup(GUI.P_machInLkUp, GUI.P_cDtrimLkUp, machNav, 37); /* Output 4 of the Simulink schematic */
 DragLift[1] = lookup(GUI.P_machInLkUp, GUI.P_cLtrimLkUp, machNav, 37); /* Output 4 of the Simulink schematic */ 
 RhoHatm[0] = lookup(GUI.P_RinLkUp, GUI.P_rhoNomLkUp, Radius, 1000); /* Output 5 of the Simulink schematic */
 RhoHatm[1] = lookup(GUI.P_RinLkUp, GUI.P_HatmLkUpFilt, Radius, 1000); /* Output 5 of the Simulink schematic */
 cNtauN[0] = lookup(GUI.P_machInLkUp, GUI.P_cNtrimLkUp, machNav, 37);  /* Output 6 of the Simulink schematic */      
 cNtauN[1] = lookup(GUI.P_machInLkUp, GUI.P_tauNtrimLkUp, machNav, 37); /* Output 6 of the Simulink schematic */

 
 for (i=0; i<3; i++)
 {
     gNED[i] = GUI.P_gNEDGuiRs[GUI.D_CS][i]; /* Output 7 of the Simulink schematic */
 }
 
 GUI.O_muGuiOut = GUI.P_MuGuiRs[GUI.D_CS];
 
 GUI.D_CS = GUI.D_CS + 1;
 
//  if ((GUI.D_CS-GUI.D_SavedCS) > 9)
//  {
//      GUI.D_SavedCS = GUI.D_CS;
//      for (j=0; j<6; j++)
//      {
//          GUI.O_CoMNomOut[j] = xCoMNom[GUI.D_CS2][j];
//      }
//      GUI.O_muSimNomOut  = muSimNom[GUI.D_CS2][0];
//      
//      GUI.D_CS2 = GUI.D_CS2 + 1;
//  }

   
}

void GE_Guidance_class::GE_GUI_Exit(void)
{
}

void GE_Guidance_class::GE_GUI_PathPlanning() {
	PPN.P_massNom = 1990.00;
	PPN.P_rPlanetNom = 3400000.00;
	PPN.P_SrefNom = 11.34;
	PPN.P_LrefNom = 3.80;
	PPN.P_khfNom = 0.00019027;
	PPN.P_omgPlanetNom = 0.00007088;
	PPN.P_MmaxNom = 150.00;
	PPN.P_JNom = 2390.00;
	PPN.P_aMax = PPN.P_MmaxNom / PPN.P_JNom;
	PPN.P_ugNom = -0.500;	

	double bank_times[NBR_MAX] = {50, 100, 150, 200, 500, 500, 500, 500};
	for(uint32_t i=0; i<NBR_MAX; i++) {
		PPN.D_tBrVNom[i] = bank_times[i];
		PPN.D_tBrInitNom[i] = 0.0;
		PPN.D_tBrEndNom[i] = 0.0;
		PPN.D_dirBrNom[i] = 0;
		PPN.D_brFlagNom[i] = 0;
	}
	
	// Build Nominal Mission Trajectory
	buildNominalMissionTrajectory();

	// Build Mission Trajectory (with 3DOF EDL simulation)
	buildMissionTrajectory();

	// Build Guidance Trajectory
	buildGuidanceTrajectory();

	//GUI.P_uMuGuiRs[2411]
	//GUI.P_MuGuiRs[2411]
	//GUI.P_xCoMGuiRs[2411][6]
	//GUI.P_gNEDGuiRs[2411][3]

}

void GE_Guidance_class::buildNominalMissionTrajectory() {
	
	PPN.D_NbrNom = 0;
	for(uint32_t i=0; i<NBR_MAX; i++) {
		if(PPN.D_tBrVNom[i] < T_PDP_NOM) {
			PPN.D_NbrNom++;
		}
	}

	double t = 0.00;
	double dt = 1.00;
	for(unsigned int i=0; i<VSIZE; i++) {
		PPN.D_tSimNom[i] = t;
		PPN.D_muNomNBR[i] = PPN.P_ugNom;
		t += dt;	
	}

	addMultipleBankReversals();
}

void GE_Guidance_class::buildMissionTrajectory() {

	PPN.D_xCoMNomEIP[0] = 3516200.0;  // Radial Position (r)
	PPN.D_xCoMNomEIP[1] = -0.6614798; // Longitude (Lon, Lambda)
	PPN.D_xCoMNomEIP[2] = 0.3708825;  // Latitude (Lat, lambda)
	PPN.D_xCoMNomEIP[3] = 5315.4;     // Velocity Modulus (v)
	PPN.D_xCoMNomEIP[4] = -0.2268928; // Flight Path Angle (FPA, gamma)
	PPN.D_xCoMNomEIP[5] = 1.7597;     // Heading (Head, chi)

	PGrav.P_GRAVID = 2;
	PGrav.P_MU = 48.83e+12;	
	PGrav.P_J2 = 0.0019;
	PGrav.P_J3 = 0.00;
	PGrav.P_J4 = 0.00;
	PGrav.REQ = 3.40e+06;

	bool stop = false;
	bool first = true;
	uint32_t idx = 1;

	while(stop == false) {
		printf("\nNominal EIP Coordinates\n----------\n");
		printf("Lon : %lf\n", PPN.D_xCoMNomEIP[1]);
		printf("Lat : %lf\n", PPN.D_xCoMNomEIP[2]);

		// SIM 3 degrees of freedom (3DOF) Detailed
		sim3dofDetailed();

		// PDP Result collection
		PDP.t = T_PDP_NOM;
		for(uint32_t i=0; i<6; i++) {
			PDP.xCoM[i] = PPN.D_xCoMNom[VSIZE-1][i];
		}
		FILE* fp = fopen("testPDP.txt", "w");
		for(uint32_t i=0; i<VSIZE; i++) {
			fprintf(fp, "%lf %lf %lf %lf %lf %lf\n", PDP.xCoM[0], PDP.xCoM[1], PDP.xCoM[2], PDP.xCoM[3], PDP.xCoM[4], PDP.xCoM[5]);
		}
		fclose(fp);
		PDP.mach = PPN.D_machNom[VSIZE-1];

		// Nominal PDP results
		printf("\nNominal PDP Coordinates\n----------\n");
		printf("R    : %lf km\n", PDP.xCoM[0]/1000.0);
		printf("ALT  : %lf\n", PDP.hAeroid/1000.0);
		printf("Lon  : %lf rad\n", PDP.xCoM[1]);
		printf("Lat  : %lf rad\n", PDP.xCoM[2]);
		printf("Vabs : %lf m/s\n", PDP.xCoM[3]);
		printf("FPA  : %lf rad\n", PDP.xCoM[4]);
		printf("Head : %lf rad\n", PDP.xCoM[5]);
		

		// Stop condition
		stop = true;	
	}
}

void GE_Guidance_class::sim3dofDetailed() {
	double t_count = 0;
	uint32_t k = 0;

	double xCoM[6];
	for(uint32_t i=0; i<6; i++) {
		xCoM[i] = PPN.D_xCoMNomEIP[i];
	}

	while(t_count < T_SIM) {
		double gNED[3];
		grav_Exec(gNED);
		double Vw = xCoM[3];
		double R = xCoM[0];

		double cSnd = lookup(GUI.P_RinLkUp, GUI.P_cSndLkUp, R, 1000);
		double mach = Vw / cSnd;

		double cD = lookup(GUI.P_machInLkUp, GUI.P_cDtrimLkUp, mach, 37);
		double cL = lookup(GUI.P_machInLkUp, GUI.P_cLtrimLkUp, mach, 37);
		double rho = lookup(GUI.P_RinLkUp, GUI.P_rhoNomLkUp, R, 1000);

		// mu at current time
		double mu = getMuAtTime(t_count);

		// SIM 3DOF
		double q = 0.5*rho*pow(Vw, 2);
		double FD = q*PPN.P_SrefNom*cD;	
		double FL = q*PPN.P_SrefNom*cL;	

		double lat = xCoM[2];
		double fpa = xCoM[4];
		double head = xCoM[5];

		double gN = gNED[0];
		double gD = gNED[2]; 

		double m = PPN.P_massNom;

		double centr[3] = {
			0, 
			Vw*cos(fpa)/R, 
			Vw*cos(fpa)*sin(head)*tan(lat)/R
		};

		double force[3] = {
			-FD/m,
			(1/m)*(1/Vw)*(FL*cos(mu)),
			(1/m)*(1/(Vw*cos(fpa)))*(FL*sin(mu))
		};
	       	
		double grav[3] = {
			cos(head)*cos(fpa)*gN-sin(fpa)*gD,
			-(cos(head)*sin(fpa)*gN+cos(fpa)*gD)/Vw,
			-(sin(head)*gN)/(cos(fpa)*Vw)
		};

		double corioli[3] = {
			0,
			2*PPN.P_omgPlanetNom*sin(head)*cos(lat),
			2*PPN.P_omgPlanetNom*(sin(lat)-cos(head)*cos(lat)*tan(fpa))
		};

		double rotPlanet[3] = {
			R*pow(PPN.P_omgPlanetNom,2)*cos(lat)*(sin(fpa)*cos(lat)-sin(lat)*cos(head)*cos(fpa)),
			R*pow(PPN.P_omgPlanetNom,2)*(1/Vw)*(cos(lat)*(cos(fpa)*cos(lat)+sin(lat)*cos(head)*sin(fpa))),
			R*pow(PPN.P_omgPlanetNom,2)*(1/Vw)*cos(fpa)*sin(head)*cos(lat)*sin(lat)
		};

		double vVectDot[3] = {0, 0, 0};
		for(uint32_t i=0; i<3; i++) {
			vVectDot[i] = centr[i]+force[i]+grav[i]+corioli[i]+rotPlanet[i];
		}

		double posVectDot[3] = {
			Vw*sin(fpa), 
			Vw/R*cos(lat)*cos(fpa)*sin(head), 
			Vw/R*cos(fpa)*cos(head)
		};

		printf("%lf, %lf, %lf, %lf, %lf, %lf\n", mach, rho, cD, cL, FD, FL);

		PPN.D_cDNomProf[k] = cD;
		PPN.D_cLNomProf[k] = cL;
		PPN.D_rhoNomProf[k] = rho;
		PPN.D_FDNom[k] = FD;
		PPN.D_FLNom[k] = FL;
		// Fawas
		PPN.D_machNom[k] = mach;
		
		PPN.D_gNEDNom[k][0] = gNED[0];	
		PPN.D_gNEDNom[k][1] = gNED[1];	
		PPN.D_gNEDNom[k][2] = gNED[2];	

		PPN.D_xCoMDotNom[k][0] = posVectDot[0];  
		PPN.D_xCoMDotNom[k][1] = posVectDot[1];  
		PPN.D_xCoMDotNom[k][2] = posVectDot[2];  
		PPN.D_xCoMDotNom[k][3] = vVectDot[0];  
		PPN.D_xCoMDotNom[k][4] = vVectDot[1];  
		PPN.D_xCoMDotNom[k][5] = vVectDot[2];

		for(uint32_t i=0; i<6; i++) {
			xCoM[i] = xCoM[i] + DT_SIM*PPN.D_xCoMDotNom[k][i];
			PPN.D_xCoMNom[k][i] = xCoM[i];
		}	

		t_count += DT_SIM;
		k++;
	}
}

double GE_Guidance_class::getMuAtTime(double t) {
	double res = 0.00;
	double num_threshold = 0.00001;
	bool found = false;

	for(uint32_t i=0; i<VSIZE && !found; i++) {
		if((t > PPN.D_tSimNom[i] - num_threshold) && (t < PPN.D_tSimNom[i] + num_threshold)) {
			res = PPN.D_muNomNBR[i];
			found = true;
		}
	}
}

void GE_Guidance_class::grav_Exec(double *gNED) {
	double gg, sl, cl, rre;
	double g[2];
	double P[4];
	double JP[4];
	double Q[4];
	double JQ[4];
	double R, latitude;

	

}

void GE_Guidance_class::buildGuidanceTrajectory() {

}

void GE_Guidance_class::addMultipleBankReversals() {
	for(uint32_t i=0; i<PPN.D_NbrNom; i++) {
		if(i % 2 == 1) {
			PPN.D_dirBrNom[i] = 1;
		} else {
			PPN.D_dirBrNom[i] = -1;
		}
	}

	for(uint32_t i=0; i<PPN.D_NbrNom; i++) {
		addBankReversalKeep(i);
	}

	fixBankReversalProfKeep();
}

void GE_Guidance_class::addBankReversalKeep(uint32_t idx) {
	uint32_t N = VSIZE;
	
	if(PPN.D_tBrVNom[idx] > T_PDP_NOM) { // if BRM time greater than PDP
		// don't do anything
	} else {

		uint32_t ixBr = find_index(PPN.D_tSimNom, VSIZE, PPN.D_tBrVNom[idx]);	

		// initial bank angle
		double mu0 = PPN.D_muNomNBR[ixBr];

		// initial bank angle derivative
		double muP0 = (PPN.D_muNomNBR[ixBr] - PPN.D_muNomNBR[ixBr-1]) / (PPN.D_tSimNom[ixBr] - PPN.D_tSimNom[ixBr-1]);
		
		double mu10[2], muP10[2];
		double m[2];
		getReversedLeftAndRightBankSt(mu0, muP0, mu10, muP10, m);

		double tBrRel, tswRel, s0, muFeff;
		double  m_final = 0.0;

		if(PPN.D_dirBrNom[idx] == -1) {
			// Left Manoeuvre
			double mL = m[0];
			double mu10L = mu10[0];
			double muP10L = muP10[1];

			// Initial and final states of the bang bang maneuver
			double x0 = mu0;
			double v0 = muP0;
			double x10 = mu10L;
			double v10 = muP10L;

			// The next segment to which the bank angle will belong (safety)
			double nextML = floor(fabs(x10)/PIG);

			// BR direction
			double s0L = 0.0;
			if((x10 - x0) > 0) {
				s0L = 1;
			} else {
				s0L = -1;
			}
			s0 = s0L;

			// Two solutions of the second order polynomial giving the maneuver time
			double tBrRelA = (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*PPN.P_aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*PPN.P_aMax);
			double tBrRelB = -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*PPN.P_aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*PPN.P_aMax);
				
			double t2 = 0.0;
			if(tBrRelA > 0) {
				t2 = tBrRelA;
			} else {
				t2 = tBrRelB;
			}

			// The switching time is chosen
			tBrRel = t2;
			tswRel = (s0*t2*PPN.P_aMax+v10-v0)/(2*s0*PPN.P_aMax);

			// the effective final bank angle is computed
			muFeff = x10 + v10*t2;
			double satmuF = 0.0;

			// the valid values for final bank angle, where the current segment is not left, are computed
			double muFMin, muFMax;
			if(x10 > 0) {
				muFMin = nextML*PIG;
				muFMax = (nextML+1)*PIG;
			} else {
				muFMin = -1*(nextML+1)*PIG;
				muFMax = -1*nextML*PIG;
			}

			// if the future bank angle leaves the segment, its value is adjusted
			double muFeffL = 0.0;
			if(muFeff > muFMax) {
				satmuF = 1;
				muFeffL = muFMax;
			} else if(muFeff < muFMin) {
				satmuF = -1;
				muFeffL = muFMin;
			}

			// ... and the maneuver is recalculated for safety reasons
			if(fabs(satmuF) > 0.5) {
				x0 = mu0;
				v0 = muP0;
				x10 = muFeffL;
				v10 = 0;

				if((x10-x0) > 0) {
					s0 = 1;
				} else {
					s0 = -1;
				}

				tBrRelA = (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*PPN.P_aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*PPN.P_aMax);
				tBrRelB = -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*PPN.P_aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*PPN.P_aMax);

				if(tBrRelA > 0) {
					t2 = tBrRelA;
				} else {
					t2 = tBrRelB;
				}

				tBrRel = t2;
				tswRel = (s0*t2*PPN.P_aMax+v10-v0)/(2*s0*PPN.P_aMax);
			} 

			s0 = s0L;
			m_final = mL;
		} else if(PPN.D_dirBrNom[idx] == 1) {
			// Right Manoeuvre
			double mR = m[1];
			double mu10R = mu10[1];
			double muP10R = muP10[1];

			// initial and final states of the bang bang maneuver
			double x0 = mu0;
			double v0 = muP0;
			double x10 = mu10R;
			double v10 = muP10R;

			// The next segment to which the bank angle will belong (safety)
			double nextMR = floor(fabs(x10)/PIG);

			// BR direction
			double s0R = 0.0;
			if((x10 - x0) > 0) {
				s0R = 1;
			} else {
				s0R = -1;
			}
			s0 = s0R;

			// Two solutions of the second order polynomial giving the maneuver time
			double tBrRelA = (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*PPN.P_aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*PPN.P_aMax);
			double tBrRelB = -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*PPN.P_aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*PPN.P_aMax);
				
			double t2 = 0.0;
			if(tBrRelA > 0) {
				t2 = tBrRelA;
			} else {
				t2 = tBrRelB;
			}

			// The switching time is chosen
			tBrRel = t2;
			tswRel = (s0*t2*PPN.P_aMax+v10-v0)/(2*s0*PPN.P_aMax);

			// the effective final bank angle is computed
			muFeff = x10 + v10*t2;
			double satmuF = 0.0;

			// the valid values for final bank angle, where the current segment is not left, are computed
			double muFMin, muFMax;
			if(x10 > 0) {
				muFMin = nextMR*PIG;
				muFMax = (nextMR+1)*PIG;
			} else {
				muFMin = -1*(nextMR+1)*PIG;
				muFMax = -1*nextMR*PIG;
			}

			// if the future bank angle leaves the segment, its value is adjusted
			double muFeffR = 0.0;
			if(muFeff > muFMax) {
				satmuF = 1;
				muFeffR = muFMax;
			} else if(muFeff < muFMin) {
				satmuF = -1;
				muFeffR = muFMin;
			}

			// ... and the maneuver is recalculated for safety reasons
			if(fabs(satmuF) > 0.5) {
				x0 = mu0;
				v0 = muP0;
				x10 = muFeffR;
				v10 = 0;

				if((x10-x0) > 0) {
					s0 = 1;
				} else {
					s0 = -1;
				}

				tBrRelA = (sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*PPN.P_aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*PPN.P_aMax);
				tBrRelB = -(sqrt(2)*sqrt((2*s0*x10-2*s0*x0)*PPN.P_aMax+v10*v10-2*v0*v10+v0*v0)+v10-v0)/(s0*PPN.P_aMax);

				if(tBrRelA > 0) {
					t2 = tBrRelA;
				} else {
					t2 = tBrRelB;
				}

				tBrRel = t2;
				tswRel = (s0*t2*PPN.P_aMax+v10-v0)/(2*s0*PPN.P_aMax);
			} 

			s0 = s0R;
			m_final = mR;
		} else {
			// Log Error
			printf("\nERROR: AddBankReversalKeep(). Wrong bank reversal direction\n");
		}

		// Collect results
		double tbr = PPN.D_tBrVNom[idx];
		PPN.D_tBrInitNom[idx] = tbr;
		PPN.D_tBrEndNom[idx] = tbr + tBrRel;
		
		for(uint32_t i=0; i<N; i++) {
			if(PPN.D_tSimNom[i] > tbr) {
				if(PPN.D_tSimNom[i] < (tbr +tswRel)) {
					PPN.D_muNomNBR[i] = mu0 + muP0*(PPN.D_tSimNom[i]-tbr)+s0*0.5*PPN.P_aMax*(PPN.D_tSimNom[i]-tbr)*(PPN.D_tSimNom[i]-tbr);
					PPN.D_brFlagNom[i] = 1;	
				} else if(PPN.D_tSimNom[i] < (tbr + tBrRel)) {
					PPN.D_muNomNBR[i] = mu0 + muP0*tswRel+s0*0.5*PPN.P_aMax*tswRel*tswRel + (muP0 + s0*PPN.P_aMax*tswRel)*(PPN.D_tSimNom[i]-(tbr+tswRel)) - s0*0.5*PPN.P_aMax*(PPN.D_tSimNom[i]-(tbr + tswRel))*(PPN.D_tSimNom[i]-(tbr + tswRel)); 
					PPN.D_brFlagNom[i] = 1;
				} else {
					if(muFeff > 0) {
						PPN.D_muNomNBR[i] = UnNBR(acos(cos(PPN.D_muNomNBR[i])), m_final, 1.0);
					} else {
						PPN.D_muNomNBR[i] = UnNBR(acos(cos(PPN.D_muNomNBR[i])), m_final, -1.0);
					}
				}
			}
		}

	}	
}


void GE_Guidance_class::getReversedLeftAndRightBankSt(double mu0, double muP0, double *mu10, double *muP10, double *m) {
	mu10[0] = 0; mu10[1] = 0;
	muP10[0] = 0; muP10[1] = 0;
	m[0] = 0; m[1] = 0;
	
	double mO = floor(fabs(mu0)/PIG) + 1;
	double mu10O = 0.0;
	if(mu0 > 0) {
		mu10O = 2*PIG*mO - mu0;
	} else {
		mu10O = -2*PIG*mO - mu0;
	}
	double muP10O = -muP0;

	double mI = floor(fabs(mu0)/PIG);
	double mu10I = 0.0;
	if(mu0 > 0) {
		mu10I = 2*PIG*mI - mu0;
	} else {
		mu10I = -2*PIG*mI - mu0;
	}
	double muP10I = -muP0;

	mI = mI - 1;
	if(mI < 0) {
		mI = 0.0;
	}

	if(mu10O < mu0) {
		mu10[0] = mu10O;
		mu10[1] = mu10I;

		muP10[0] = muP10O;
		muP10[1] = muP10I;

		m[0] = mO;
		m[1] = mI;
	} else {
		mu10[1] = mu10O;
		mu10[0] = mu10I;

		muP10[1] = muP10O;
		muP10[0] = muP10I;

		m[1] = mO;
		m[0] = mI;	
	}
}

void GE_Guidance_class::fixBankReversalProfKeep() { 
	FILE* fp = fopen("muProfile.txt", "w");
	for(uint32_t i=0; i<VSIZE; i++) {
		fprintf(fp, "%lf\n", PPN.D_muNomNBR[i]);
	}
	fclose(fp);
}

double GE_Guidance_class::UnNBR(double muNBR, double mCurr, double sign) {
	double muConv = muNBR;
	bool togg = true;

	for(uint32_t i=0; i<mCurr; i++) {
		if(togg) {
			muConv += 2.0 * (PIG - muNBR);
			togg = false;
		} else {
			muConv += 2.0 * muNBR;
			togg = true;
		}
	}

	muConv *= sign;
	return muConv;
}

uint32_t GE_Guidance_class::find_index(double *vector, uint32_t size, double value) {
	uint32_t res = size+1;
	
	for(uint32_t i=0; i<size; i++) {
		if(vector[i] > value) {
			res = i;
			break;
		}
	}

	return res;
}

void GE_Guidance_class::GE_GUI_WriteDebugFile(E2E_PrintOutput *outfile)
{
    outfile->E2E_writeVar(GUI.O_muGuiOut, "m/s^2");
//     outfile->E2E_writeVar(GUI.O_CoMNomOut,6, "");  
//     outfile->E2E_writeVar(GUI.O_muSimNomOut, "m/s^2");    
}
/* ME2E CVS footer

Full file history:

$Log: GE_Guidance.cpp,v $
Revision 1.1  2022/09/01 14:38:20  ludovico.garin
Added DHS_GE to repository (first commit still not working)



*/

