/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#include "../GE_GNC.hxx"
#include "GE_AttControl.hxx"

double xAttEst[6];
double xAttRef[6];

double Fout[4];

double xDistEst[3];
double AttPars[3];
double uAttRef[3];
double Tout[3];

double xMuRef[2];

double uMuRef; 

uint8_t SatFlag[4];

// uint8_t THREN; 

void GE_AttControl_class::GE_ACN_Read(void)
{
  {
   E2E_ReadFile file("GEattcontrol", "DHS");

   GE_AttPars01.GE_AttPars_Read(&file);
   GE_InnerRefGen01.GE_InnerRefGen_Read(&file);
   GE_AttRefGen01.GE_AttRefGen_Read(&file);
   GE_CL_Mu01.GE_CL_Mu_Read(&file);
   GE_Dispatch01.GE_Dispatch_Read(&file);
   GE_GenTsw01.GE_GenTsw_Read(&file);
   GE_EM_Mu01.GE_EM_Mu_Read(&file);   
  }
  {
   E2E_ReadFile file("GEattcontrolInit", "DHS");
   
/*  (1.1) Initial values of the attitude navigation states */
    file.readReal(ACN.P_xAttNav0, 6);  
  }
}
        
void GE_AttControl_class::GE_ACN_Init(double xMuGui[2], double uMuGui, uint8_t &BrmStatus)
{
    GE_InnerRefGen01.GE_InnerRefGen_Init(xMuGui, uMuGui, BrmStatus);
    GE_AttRefGen01.GE_AttRefGen_Init();
    
   /* Initialization of attitude control and predicted attitude disturbance vectors*/
   for (int i = 0; i < 6; i++){
      ACN.xAttEst_prev[i] = ACN.P_xAttNav0[i];
      ACN.xAttRef_prev[i] = 0;
   }
   ACN.xAttRef_prev[2] = xMuGui[0];
   
   for (int i = 0; i < 3; i++){
      ACN.xDistEst_prev[i] = 0;
   }
   
   GE_CL_Mu01.GE_CL_Mu_Init();
   GE_EM_Mu01.GE_EM_Mu_Init();
    
}

void GE_AttControl_class::GE_ACN_Exec(double dug, double tBrm, int dirBrm, double uMuGui, double xMuGui[2], 
                                      double xAttNav[6], double xCoMNav[6], double aAngDer[3], double cNtauN[2], double RhoHatm[2], 
				      uint8_t &BrmStatus, double *Tout, double *ton, uint8_t &THREN, double *ThrActivation)				        
{


   GE_AttPars01.GE_AttPars_Exec(xCoMNav, xAttNav, cNtauN, RhoHatm, AttPars);
   GE_InnerRefGen01.GE_InnerRefGen_Exec(xMuGui, dug, uMuGui, tBrm, dirBrm, xMuRef, &uMuRef, BrmStatus); 
   GE_AttRefGen01.GE_AttRefGen_Exec(ACN.xAttRef_prev,xMuRef, &uMuRef, xAttNav, xAttRef, uAttRef);
   GE_CL_Mu01.GE_CL_Mu_Exec(ACN.xAttEst_prev, xAttRef, ACN.xDistEst_prev, uAttRef, xAttNav, xCoMNav, aAngDer, AttPars, Tout, &THREN);
   GE_Dispatch01.GE_Dispatch_Exec(Tout, Fout, SatFlag, ThrActivation);
   GE_GenTsw01.GE_GenTsw_Exec(Fout, ton);
   GE_EM_Mu01.GE_EM_Mu_Exec(Fout, &THREN, xAttNav, AttPars, xCoMNav, aAngDer, ACN.xAttEst_prev, ACN.xDistEst_prev, xAttEst, xDistEst);  



   // Save prev values
   for (int i = 0; i < 6; i++){
      ACN.xAttRef_prev[i] = xAttRef[i];
      ACN.xAttEst_prev[i] = xAttEst[i];
   }
   
   for (int i = 0; i < 3; i++){
      ACN.xDistEst_prev[i] = xDistEst[i];
   }


   /* Store main outputs of Att_Control block to output file  */
   for (int i = 0; i < 4; i++){
      ACN.O_ton[i] = ton[i];
   }

}

void GE_AttControl_class::GE_ACN_Exit(void)
{
}

void GE_AttControl_class::GE_ACN_WriteDebugFile(E2E_PrintOutput *outfile)
{

   GE_AttPars01.GE_AttPars_WriteDebugFile(outfile); 
   GE_InnerRefGen01.GE_InnerRefGen_WriteDebugFile(outfile); 
   GE_AttRefGen01.GE_AttRefGen_WriteDebugFile(outfile); 
   GE_CL_Mu01.GE_CL_Mu_WriteDebugFile(outfile); ;
   GE_Dispatch01.GE_Dispatch_WriteDebugFile(outfile); 
   GE_GenTsw01.GE_GenTsw_WriteDebugFile(outfile); 
   GE_EM_Mu01.GE_EM_Mu_WriteDebugFile(outfile); 

   outfile->E2E_writeVar(ACN.O_ton,4,"-");


}



/* ME2E CVS footer

Full file history:

$Log: $


*/

