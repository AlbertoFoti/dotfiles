/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/


#include "../GE_GNC.hxx"
#include "GE_AttRefGen01.hxx"

using namespace  GE_GNC_utils;

void GE_AttRefGen01_class::GE_AttRefGen_Read(E2E_ReadFile *file)
{  

/*  (3.1) Simulation time [s] */
    file->readReal(&AttRefGen01.P_T);  

/*  (3.2) Discrete pole for bank angle algoritmic feedback reference generator [-] */
    file->readReal(&AttRefGen01.P_p0mu);  

/*  (3.3) Discrete pole for bank angle algoritmic feedback reference generator [-] */
    file->readReal(&AttRefGen01.P_p1mu);  

/*  (3.4) Discrete pole for aerodynamic roll reference stabilization 	   [-] */
    file->readReal(&AttRefGen01.P_p0L);  
          
}


void GE_AttRefGen01_class::GE_AttRefGen_Init(void){

	double *cVect;
        double **GPMAT = dmatrix(2, 2, 0.);
	
	/*Matrix with poles place*/
	GPMAT[0][0] = AttRefGen01.P_p0mu; 
	GPMAT[1][0] = AttRefGen01.P_p1mu;

	/*coefficient computation*/
	cVect	= polcar(GPMAT,2);

	AttRefGen01.COEFF[0] = cVect[0];
	AttRefGen01.COEFF[1] = cVect[1];

}

void GE_AttRefGen01_class::GE_AttRefGen_Exec(double xAttRef_prev[6], double xMuRef[2], double *uMuRef, double xAttNav[6], 
					     double *xAttRef, double *uAttRef)
{
  
	double ul,unt;
	double aoa;
	double muRef2,omgmu;
	double kMu,kOmgMu;
	double dunCl,dulCl;
        int i;

	/*navigated AoA*/
	aoa	= xAttNav[1];

	/*Inner reference bank angle and bank angle rate*/
	muRef2	= xMuRef[0];
	omgmu	= xMuRef[1];

	/*feedback constants to fit the closed loop pole*/
	kMu	= AttRefGen01.COEFF[0]*sin(aoa)/(AttRefGen01.P_T*AttRefGen01.P_T);
	kOmgMu	= AttRefGen01.COEFF[1]/AttRefGen01.P_T;

	/*Components to stabilize the trajectory of the reference generator around the trajectory of the inner reference generator*/
	/*Computation of the yaw command in closed loop */
	dunCl	= kOmgMu*(sin(aoa)*omgmu/AttRefGen01.P_T - xAttRef_prev[5]) + kMu*(muRef2 - xAttRef_prev[2]);

	/* Computation of the roll command in closed loop */
	dulCl	= (1-AttRefGen01.P_p0L)/AttRefGen01.P_T*(cos(aoa)*omgmu/AttRefGen01.P_T  - xAttRef_prev[3]);

	/*Dynamic dispatching and stabilization components*/
	unt 	= sin(aoa)*(*uMuRef/(AttRefGen01.P_T*AttRefGen01.P_T))+ dunCl;
	ul	= cos(aoa)/sin(aoa)*unt	 + dulCl;

	uAttRef[0] = ul;
	uAttRef[1] = 0;
	uAttRef[2] = unt;

	/*Reference generator model update ---> to be checked*/
	xAttRef[2]	= xAttRef_prev[2] + AttRefGen01.P_T*1/sin(aoa)*xAttRef_prev[5] + 0.5*AttRefGen01.P_T*unt;
	xAttRef[5]	= xAttRef_prev[5] + AttRefGen01.P_T*unt;
	xAttRef[3]	= xAttRef_prev[3] + AttRefGen01.P_T*ul;

//     for (i=0; i<6; i++)
//     {    
//        AttRefGen01.D_xAttRef_prev[i] = xAttRef[i];   
//     }
    
        /* Store output data*/
        for (i = 0; i<6; i++){
          AttRefGen01.O_xAttRef[i] = xAttRef[i];
        }  
        for (i = 0; i<3; i++){
          AttRefGen01.O_uAttRef[i] = uAttRef[i];
        }

}

void GE_AttRefGen01_class::GE_AttRefGen_WriteDebugFile(E2E_PrintOutput *outfile)
{
	outfile->E2E_writeVar(AttRefGen01.O_xAttRef,6, "-");
	outfile->E2E_writeVar(AttRefGen01.O_uAttRef,3, "-");

}


/* ME2E CVS footer

Full file history:

$Log: $


*/
