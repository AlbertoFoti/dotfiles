/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/

#include "../GE_GNC.hxx"
#include "GE_AttPars01.hxx"

using namespace  GE_GNC_utils;

void GE_AttPars01_class::GE_AttPars_Read(E2E_ReadFile *file)
{

/*  (1.1) P_SREF Reference surface of the AEDB  [m^2] */
     file->readReal(&AttParams.P_SREF);

/*  (1.2) P_LREF Reference length of the AEDB [m] */
     file->readReal(&AttParams.P_LREF);

/*  (1.3) P_JL First component of the matrix of inertia diagonal [kgm^2] */
     file->readReal(&AttParams.P_JL);

/*  (1.4) P_JM Second component of the matrix of inertia diagonal [kgm^2] */
     file->readReal(&AttParams.P_JM);

/*  (1.5) P_JN Third component of the matrix of inertia diagonal [kgmì2] */
     file->readReal(&AttParams.P_JN);    
     
/*  (1.6) P_YACOM Displacement of the center of mass on the y direction of DMRF [m] */
     file->readReal(&AttParams.P_YACOM);

/*  (1.7) P_XACOM Displacement of the center of mass on the x direction of DMRF [m] */
     file->readReal(&AttParams.P_XACOM);
     
}


void GE_AttPars01_class::GE_AttPars_Init(void){

}

void GE_AttPars01_class::GE_AttPars_Exec(double xCoMNav[6], double xAttNav[6], 
           double cNtauN[2], double RhoHatm[2], double *AttPars)
{
	double qref,kl,kn,km;
	double q,rho,vAbs,h;
	double aoa,cNeq,tauN1;
	double Hatm;

	/* Navigated AoA*/
	aoa	= xAttNav[1];
	
	/* Navigated vAbs*/
	vAbs	= xCoMNav[3];

	/* Current moment coefficient and its sensititivy to the AoA*/
	cNeq	= cNtauN[0];
	tauN1	= cNtauN[1];

	/* Current density and spatial constant*/
	rho 	= RhoHatm[0];
	Hatm	= RhoHatm[1];

	/*dynamic pressure*/
	q		= 0.5*rho*vAbs*vAbs;
	
	/*dynamic torque*/
	qref	= AttParams.P_SREF*AttParams.P_LREF*q; /* Mref in eq 10 pag 5 in GEAttitudeControlDraft01 */

	/*elastic constants*/
	kl		= -qref/AttParams.P_JL*AttParams.P_YACOM/AttParams.P_LREF*cNeq;
	km		= qref/AttParams.P_JM*AttParams.P_XACOM/AttParams.P_LREF*tauN1;
	kn		= qref/AttParams.P_JN*AttParams.P_XACOM/AttParams.P_LREF*cNeq;

	/*set as outputs*/
	AttPars[0]	= kl;
	AttPars[1]	= km;	
	AttPars[2]	= kn;	
    
    /* Store output data*/
    for (int i = 0; i<3; i++){
        AttParams.O_AttPars[i] = AttPars[i];
    }
}

void GE_AttPars01_class::GE_AttPars_WriteDebugFile(E2E_PrintOutput *outfile)
{
	outfile->E2E_writeVar(AttParams.O_AttPars,3, "-");
}


/* ME2E CVS footer

Full file history:

$Log: $


*/
