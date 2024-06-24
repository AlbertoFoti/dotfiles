/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/

#include "../GE_GNC.hxx"
#include "GE_CL_Mu01.hxx"


/***************************** STATES*******************************/ 

#define ULCHL 			 0 
#define ULCHM 			 1 
#define ULCHN 			 2 

/***************************** STATES*******************************/ 

using namespace  GE_GNC_utils;

void GE_CL_Mu01_class::GE_CL_Mu_Read(E2E_ReadFile *file)
{  

/* (4.1) Simulation time [s] */
    file->readReal(&CL_Mu01.P_T);  

/* (4.2) Programmed damping coefficient										[ - ]	*/
    file->readReal(&CL_Mu01.P_ZETAL);                                                                                                                  
                                                                                                                        
/* (4.3) Programmed damping coefficient										[ - ]	*/
    file->readReal(&CL_Mu01.P_ZETAM);                                                                                                                      
                                                                                                                        
/* (4.4) Closed loop constants of the bank angle feedback law							[ - ]	*/
    file->readReal(&CL_Mu01.P_P0MU);                                                                                                                          
                                                                                                                        
/* (4.5) Closed loop constants of the bank angle feedback law							[ - ]	*/
    file->readReal(&CL_Mu01.P_P1MU);                                                                                                                          
                                                                                                                        
/* (4.6) First component of the matrix of intertia diagonal							[kg/m^2]*/
    file->readReal(&CL_Mu01.P_JL);                                                                                                                         
                                                                                                                        
/* (4.7) Second component of the matrix of intertia diagonal							[kg/m^2]*/
    file->readReal(&CL_Mu01.P_JM);                                                                                                                         
                                                                                                                        
/* (4.8) Third component of the matrix of intertia diagonal							[kg/m^2]*/
    file->readReal(&CL_Mu01.P_JN);                                                                                                                         
                                                                                                                        
/* (4.9) Maximum thrust on the L channel									[Nm]	*/
    file->readReal(&CL_Mu01.P_MMAXL);                                                                                                                          
                                                                                                                        
/* (4.10)Maximum thrust on the M channel									[Nm]	*/
    file->readReal(&CL_Mu01.P_MMAXM);                                                                                                                         
                                                                                                                        
/* (4.11)Maximum thrust on the N channel									[Nm]	*/
    file->readReal(&CL_Mu01.P_MMAXN);                                                                                                                          
                                                                                                                        
/* (4.12)Minimum thrust on the L channel									[Nm]	*/
    file->readReal(&CL_Mu01.P_MMINL);                                                                                                                          
                                                                                                                        
/* (4.13)Minimum thrust on the M channel									[Nm]	*/
    file->readReal(&CL_Mu01.P_MMINM);                                                                                                                   
                                                                                                                        
/* (4.14)Minimum thrust on the N channel									[Nm]	*/
    file->readReal(&CL_Mu01.P_MMINN);                                                                                                                          
                                                                                                                        
/* (4.15)Equilibrium angle of attack in case it is requested to be regulated.					[rad]	*/
    file->readReal(&CL_Mu01.P_AOAEQ);                                                                                                                        
                                                                                                                        
/* (4.16)Equilibrium aerodynamic roll in case it is requested to be regulated.					[rad]	*/
    file->readReal(&CL_Mu01.P_ETAEQ);                                                                                                                        
                                                                                                                        
/* (4.17)Minimum angle of attack safety range									[rad]	*/
    file->readReal(&CL_Mu01.P_AOAMIN);                                                                                                                        
                                                                                                                        
/* (4.18)Maximum angle of attack safety range									[rad]	*/
    file->readReal(&CL_Mu01.P_AOAMAX);                                                                                                                   
                                                                                                                        
/* (4.19)Minimum elastic constant below which the attitude control is turned OFF				[Nm/rad]*/
    file->readReal(&CL_Mu01.P_KMMIN);                                                                                                                          
                                                                                                                        
/* (4.20)Maxmimum simulation time after which the attitude control is turned OFF				[s]	*/
    file->readReal(&CL_Mu01.P_TMAX);                                                                                                                          
                                                                                                                        
/* (4.21)Overal flag to turn OFF the attitude control								[ - ]	*/
    file->readInteger(&CL_Mu01.P_CLFLAG);                                                                                                                        
                                                                                                                        
/* (4.22)Flag to turn OFF the compensation of the aerodynamic angles kinematics caoused by FPA and HEAD dot	[ - ]	*/
    file->readInteger(&CL_Mu01.P_VANGCOMPF);                                                                                                                         
                                                                                                                        
/* (4.23)Flag to turn OFF the known disturbance rejection component						[ - ]	*/
    file->readInteger(&CL_Mu01.P_KNDJDISTF); 
                                                                                                                 
/* (4.24)Flag to turn OFF the known disturbance rejection component (transformed terms)				[ - ]	*/
    file->readInteger(&CL_Mu01.P_KNW2DISTF);                                                                                                                       
                                                                                                                        
/* (4.25)Flag to turn OFF the unknown disturbance compensation							[ - ]	*/
    file->readInteger(&CL_Mu01.P_UNKDISTF);                                                                                                                         
                                                                                                                        
/* (4.26)Flag to turn OFF the damping of the angle of attack and aerodynamic roll				[ - ]	*/
    file->readInteger(&CL_Mu01.P_DAMPAERFLAG);         
}

void GE_CL_Mu01_class::GE_CL_Mu_Init(void){

double *cVect;
    double **GPMAT = dmatrix(2, 2, 0.);
	
	/*Matrix with poles place*/
	GPMAT[0][0] = CL_Mu01.P_P0MU; 
	GPMAT[1][0] = CL_Mu01.P_P1MU;

	/*coefficient computation*/
	cVect	= polcar(GPMAT,2);

	CL_Mu01.P_COEFF[0] = cVect[0];
	CL_Mu01.P_COEFF[1] = cVect[1];

	/* TimeElapsed initilization */
	CL_Mu01.D_TimeElapsed = 0;

    /* TO BE INITIALIZED
     * xAttRef[6]
     * xAttEst[6]
       xDistEst[3]
     */
    
} 
void GE_CL_Mu01_class::GE_CL_Mu_Exec(double xAttEst[6], double xAttRef[3], double xDistEst[3], double uAttRef[3], double xAttNav[6], double xCoMNav[6], double aAngDer[3], double AttPars[3], 
				     double *Tout, uint8_t *THREN)
{
  
	double eta,aoa,mu;

	double muRef,omgnRef;
	double duMuCl,dulMuCl,dunMuCl;

	double fpaP,headP;
	double fpa;

	double dEta,dAoa,dMu;
	double dOmglRef,dOmgmRef,dOmgnRef;

	double omgl,omgmt,omgnt;
	double omgm,omgn;
	double muEst;

	double dl3Est,dm3Est,dn3Est;
	
	double ul,umt,unt;
	double um,un;
	
	double kMu;
	double klOmg,kmOmg,knOmg;
	
	double kl,km,kn;
	double omgNatl,omgNatm;

	double duntCl;
	double mukComp,omglkComp,knDl,omgmkComp,eTMu;

	int k;

	double regAoa;

    double argomgNatl;

	/*Navigated attitude state*/
	eta	= xAttNav[0];
	aoa	= xAttNav[1];
	mu	= xAttNav[2];

	omgm	= xAttNav[4];
	omgn	= xAttNav[5];

	/*component of the kinematics of the aerodynamic angles caused by trajectory deviation (FPA and HEADING dot)*/
	dEta	= aAngDer[0];
	dAoa	= aAngDer[1];
	dMu	= aAngDer[2];

	/*navigated FPA*/
	fpa	= xCoMNav[4];

	/*value of angular rates that compensate the effects of FPA and HEAD dot*/
	dOmglRef	= CL_Mu01.P_VANGCOMPF*(dEta + cos(aoa)*dMu);
	dOmgmRef	= CL_Mu01.P_VANGCOMPF*(dAoa);
	dOmgnRef	= CL_Mu01.P_VANGCOMPF*(sin(aoa)*dMu);

	/* gyroscipic torques cancellation and estimated disturbance torque cancellation*/
// 	omgl	= xAttNav[3]; 
//  omgmt	= cos(eta)*omgm	- sin(eta)*omgn;
// 	omgnt	= sin(eta)*omgm	+ cos(eta)*omgn;
    
        omgl	= xAttEst[3];
	omgmt	= xAttEst[4];
	omgnt	= xAttEst[5];
    
    
	dl3Est	= CL_Mu01.P_KNDJDISTF*(CL_Mu01.P_JM - CL_Mu01.P_JN)/CL_Mu01.P_JL*omgm*omgn + CL_Mu01.P_UNKDISTF*xDistEst[0] ; 
	dm3Est	= CL_Mu01.P_KNDJDISTF*cos(eta)*(CL_Mu01.P_JN - CL_Mu01.P_JL)/CL_Mu01.P_JM*omgl*omgn - CL_Mu01.P_KNDJDISTF*sin(eta)*
                 (CL_Mu01.P_JL-CL_Mu01.P_JM)/CL_Mu01.P_JN*omgl*omgm - CL_Mu01.P_KNW2DISTF*omgnt*(omgl - cos(aoa)/sin(aoa)*omgnt);
	dn3Est	= CL_Mu01.P_KNDJDISTF*sin(eta)*(CL_Mu01.P_JN - CL_Mu01.P_JL)/CL_Mu01.P_JM*omgl*omgn + CL_Mu01.P_KNDJDISTF*cos(eta)* 
                 (CL_Mu01.P_JL-CL_Mu01.P_JM)/CL_Mu01.P_JN*omgl*omgm + CL_Mu01.P_KNW2DISTF*omgmt*(omgl - cos(aoa)/sin(aoa)*omgnt) + CL_Mu01.P_UNKDISTF*xDistEst[2];

    
	/*elastic constants recived from AttPars*/
	kl	= AttPars[0];
	km	= AttPars[1];
	kn	= AttPars[2];

	/*natural oscillation frequency*/
        argomgNatl=kl+kn*cos(aoa)/sin(aoa);

    
    if (argomgNatl > 0)
    {   
	   omgNatl	= sqrt(argomgNatl);
    }
	else
	{
	   omgNatl	= 0;
    }
	omgNatm	= sqrt(km);

	/*dampigng constants to fix the damping coefficient*/
	klOmg	= 2*CL_Mu01.P_ZETAL*omgNatl;
	kmOmg	= 2*CL_Mu01.P_ZETAM*omgNatm;

	/* Closed loop control on bank angle */
	muEst	= xAttEst[2];

	/*closed loop gains to fix the closed loop poles*/
	kMu	= CL_Mu01.P_COEFF[0]*sin(aoa)/(CL_Mu01.P_T*CL_Mu01.P_T);
	knOmg	= CL_Mu01.P_COEFF[1]/CL_Mu01.P_T;

	/*reference values*/
	muRef	= xAttRef[2];
	omgnRef	= xAttRef[5];

	/*tracking error*/
	eTMu	= muRef - muEst;

	/*stabilizing and disturbance cancellation component*/
	mukComp		= knOmg*(omgnRef + dOmgnRef - omgnt) + kMu*eTMu;
	duntCl		= mukComp - dn3Est;

	omglkComp	= klOmg*(xAttRef[3] + dOmglRef - omgl);
	knDl		= cos(aoa)/sin(aoa)*duntCl;

	omgmkComp	= kmOmg*(xAttRef[4] + dOmgmRef - omgmt);

	/* check for safety limits on the AoA */
	regAoa		= SatF(&aoa,CL_Mu01.P_AOAMIN,CL_Mu01.P_AOAMAX); 
	
	if(regAoa == 0)
	{
		/*If the angle of attack and the aerodynamic roll are left free*/
		ul			= uAttRef[0] + CL_Mu01.P_DAMPAERFLAG*omglkComp - dl3Est + knDl;
		umt			= uAttRef[1] + CL_Mu01.P_DAMPAERFLAG*omgmkComp - dm3Est;
		unt			= uAttRef[2] + duntCl;		
	}
	else
	{
		/*If the angle of attack and the aerodynamic roll are regulated around their equilibria*/
		ul			= uAttRef[0] + CL_Mu01.P_DAMPAERFLAG*omglkComp - dl3Est + knDl + kMu*(CL_Mu01.P_ETAEQ - eta);
		umt			= uAttRef[1] + CL_Mu01.P_DAMPAERFLAG*omgmkComp - dm3Est + kMu*(CL_Mu01.P_AOAEQ - aoa);
		unt			= uAttRef[2] + duntCl;
	}
	
	/* detransformate the commanded angular acceleration to the components on the body reference frame*/
	um			= cos(eta)*umt	+ sin(eta)*unt;
	un			= -sin(eta)*umt	+ cos(eta)*unt;

	/*safety feature to turn off the control if dynamic pressure is too low, since */
	/*in that case the disturbances generated by the control are greater than what */
	/*the control is supposed to cancell*/
    
    
	if( ((Abs(km) < CL_Mu01.P_KMMIN) || (CL_Mu01.D_TimeElapsed > CL_Mu01.P_TMAX)) && regAoa == 0)
	{
		*THREN	=  (uint8_t) 0;
		/* Conversion to moments */
		Tout[ULCHL]		= 0;
		Tout[ULCHM]		= 0;
		Tout[ULCHN]		= 0;

	}
	else
	{
		*THREN	=  (uint8_t) 1;        
		/* Conversion to torques */
		Tout[ULCHL]		= Sat(CL_Mu01.P_CLFLAG*ul*CL_Mu01.P_JL,CL_Mu01.P_MMINL,CL_Mu01.P_MMAXL);
		Tout[ULCHM]		= Sat(CL_Mu01.P_CLFLAG*um*CL_Mu01.P_JM,CL_Mu01.P_MMINM,CL_Mu01.P_MMAXM);
		Tout[ULCHN]		= Sat(CL_Mu01.P_CLFLAG*un*CL_Mu01.P_JN,CL_Mu01.P_MMINN,CL_Mu01.P_MMAXN);
	}
    
	/* Update of elpased time */
	CL_Mu01.D_TimeElapsed += CL_Mu01.P_T;

    /* Store output data*/
    CL_Mu01.O_THREN = *THREN;
    
    for (int i = 0; i<3; i++){
        CL_Mu01.O_Tout[i] = Tout[i];
    }
  
}

void GE_CL_Mu01_class::GE_CL_Mu_WriteDebugFile(E2E_PrintOutput *outfile)
{
	outfile->E2E_writeVar(CL_Mu01.O_Tout,3, "Nm");
	outfile->E2E_writeVar(CL_Mu01.O_THREN,"-");
}



/* ME2E CVS footer

Full file history:

$Log: $


*/
