/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
/***************************** STATES*******************************/ 

#define ETA			     0 
#define AOA 			 1 
#define MU               2 



#include "GE_GNC.hxx"
#include "GE_AttNav02.hxx"

using namespace  GE_GNC_utils;

void GE_AttNav02_class::GE_AttNav_Read(E2E_ReadFile *file)
{
  
    /*  (4.1) Navigation sampling Time                               [s] */
    file->readReal(&AttNav.P_TNav);      
    
}


void GE_AttNav02_class::GE_AttNav_Init(){
}

void GE_AttNav02_class::GE_AttNav_Exec(double const yOmgIMU[3], double const xCoMNav[6], double const angder[5],  double const xAttNav_prev[6],
				       double xAttNav[6], double aAngDer[3])
        
{

   double xP[3];
   double T_xP[3];
   double xAtt_prev[3];
   double xAtt[3];
   double CPDERCOMP[3];

   for (int i=0;i<3;i++){
      xAtt_prev[i] = xAttNav_prev[i];
   }

   /*Compute the translational state derivatives*/
   FofX2(yOmgIMU, xCoMNav, angder, xAtt_prev, xP, CPDERCOMP);
   
   for (int i=0;i<3;i++){
       aAngDer[i] = CPDERCOMP[i];
   }
 
   /*Update the translational state using Euler 1st order approximation*/
   /* Derivatives multiplied by sampling time give the increments*/
   MultVByScl(xP,AttNav.P_TNav,T_xP,3);
   
   
   /* Increments are summed to the previous sample states */
   AddV(xAtt_prev, T_xP, xAtt, 3);


   /* Build xAttNav vector */
   for (int i=0;i<3;i++){
     xAttNav[i] = xAtt[i];
     xAttNav[i+3] = yOmgIMU[i];
   }

}

void GE_AttNav02_class::GE_AttNav_WriteDebugFile(E2E_PrintOutput *outfile)
{
        outfile->E2E_writeVar(AttNav.O_dEta);
        outfile->E2E_writeVar(AttNav.O_dAoA);
        outfile->E2E_writeVar(AttNav.O_dMu);
}

void GE_AttNav02_class::FofX2(double const yOmgIMU[3],double const xCoMNav[6], double const angder[5], double const x[3], double xP[3], double CPDERCOMP[3])
{
	double dEta;
	double dAoA;
	double dMu;

    int    k;
    
    double wl;
    double wm;
    double wn;
    
    double eta;
    double aoa;
    double mu;
    
    double lat;
    double fpa;
    double head;
    
    double  fpaP;
    double  headP;
    double  latP;
    double  lonP;
    double  thMP;
    
	/*angular rate*/
	wl		= yOmgIMU[0];
	wm		= yOmgIMU[1];
	wn		= yOmgIMU[2];

	/*navigated aerodynamic angles*/
	eta		= x[ETA];
	aoa 	= x[AOA];
	mu		= x[MU];

	/*navigated translational state*/
	lat		= xCoMNav[2];
	fpa		= xCoMNav[4];
	head	= xCoMNav[5];

	/*time derivative of the translational state components*/
	fpaP		= angder[0];
	headP		= angder[1];
	latP		= angder[2];
	lonP		= angder[3];
	thMP		= angder[4];  /* Angular rate of Mars */

	/* Eq 5.45, 5.46, 5.47, pag 43 of GERD TN 3 */
	/* components caused by the translational state derivative */
	
    dEta		= -((cos(lat)*sin(head)*sin(mu)+(cos(lat)*cos(head)*sin(fpa)-sin(lat)*cos(fpa))*cos(mu))*thMP+(cos(lat)*sin(head)*sin(mu)+(cos(lat)*cos(head)*sin(fpa)-sin(lat)*cos(fpa))*cos(mu))*lonP+(cos(head)*sin(mu)-sin(head)*sin(fpa)*cos(mu))*latP-sin(mu)*fpaP+cos(fpa)*cos(mu)*headP)/(sin(aoa));
	    
    dAoA		= ((cos(lat)*cos(head)*sin(fpa)-sin(lat)*cos(fpa))*sin(mu)-cos(lat)*sin(head)*cos(mu))*thMP+((cos(lat)*cos(head)*sin(fpa)-sin(lat)*cos(fpa))*sin(mu)-cos(lat)*sin(head)*cos(mu))*lonP+(-sin(head)*sin(fpa)*sin(mu)-cos(head)*cos(mu))*latP+cos(mu)*fpaP+cos(fpa)*sin(mu)*headP;

    dMu			= (((sin(lat)*sin(fpa)+cos(lat)*cos(head)*cos(fpa))*sin(aoa)+(cos(lat)*sin(head)*sin(mu)+(cos(lat)*cos(head)*sin(fpa)-sin(lat)*cos(fpa))*cos(mu))*cos(aoa))*thMP+
                  ((sin(lat)*sin(fpa)+cos(lat)*cos(head)*cos(fpa))*sin(aoa)+(cos(lat)*sin(head)*sin(mu)+(cos(lat)*cos(head)*sin(fpa)-sin(lat)*cos(fpa))*cos(mu))*cos(aoa))*lonP+
                  ((cos(head)*sin(mu)-sin(head)*sin(fpa)*cos(mu))*cos(aoa)-sin(head)*cos(fpa)*sin(aoa))*latP-sin(mu)*cos(aoa)*fpaP+(cos(fpa)*cos(mu)*cos(aoa)-sin(fpa)*sin(aoa))*headP)/sin(aoa);
    
    
    CPDERCOMP[0]	= dEta;
	CPDERCOMP[1]	= dAoA;
	CPDERCOMP[2]	= dMu;
    
       
	/* Eq 5.44, pag 43 of GERD TN 3.  Pay attention! Sign in technical note is wrong */
	/* Att kynematic derivatives */
	xP[ETA]		= wl	- sin(eta)*cos(aoa)/sin(aoa)*wm	- cos(eta)*cos(aoa)/sin(aoa)*wn	- dEta;
	xP[AOA]		= 0		+ cos(eta)*wm					- sin(eta)*wn					- dAoA;
	xP[MU]		= 0		+ sin(eta)/sin(aoa)*wm			+ cos(eta)/sin(aoa)*wn			- dMu;

	
	AttNav.O_dEta	= dEta;
	AttNav.O_dAoA	= dAoA;
	AttNav.O_dMu	= dMu;
    
};

/* ME2E CVS footer

Full file history:

$Log: $


*/
