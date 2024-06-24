/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#ifndef GE_ATTCONTROL_HXX
#define GE_ATTCONTROL_HXX
//#include "E2E_inpout.hxx"
#include "GE_AttPars01.hxx"
#include "GE_InnerRefGen01.hxx"
#include "GE_AttRefGen01.hxx"
#include "GE_CL_Mu01.hxx"
#include "GE_Dispatch01.hxx"
#include "GE_GenTsw01.hxx"
#include "GE_EM_Mu01.hxx"

class GE_AttControl_class
{

 private:
   GE_AttPars01_class GE_AttPars01;
   GE_InnerRefGen01_class GE_InnerRefGen01;
   GE_AttRefGen01_class GE_AttRefGen01;
   GE_CL_Mu01_class GE_CL_Mu01;
   GE_Dispatch01_class GE_Dispatch01;
   GE_GenTsw01_class GE_GenTsw01;
   GE_EM_Mu01_class GE_EM_Mu01;

   struct ACN_type
   {
      double O_ton[4];
      double xAttRef_prev[6];
      double xAttEst_prev[6];
      double xDistEst_prev[3];

      double P_xAttNav0[6];
   } ACN;

 public:
   void GE_ACN_Read(void);

   void GE_ACN_Init(double xMuGui[2], double uMuGui, uint8_t &BrmStatus);

   void GE_ACN_Exec(double dug, double tBrm, int dirBrm, double uMuGui, double xMuGui[2], 
                    double xAttNav[6], double xCoMNav[6], double aAngDer[3], double cNtauN[2], double RhoHatm[2], 
		    uint8_t &BrmStatus, double *Tout, double *ton, uint8_t &THREN, double *ThrActivation);

   void GE_ACN_Exit(void);

   void GE_ACN_WriteDebugFile(E2E_PrintOutput *outfile);
};

#endif // GE_ATTCONTROL_HXX
/* ME2E CVS footer

Full file history:

$Log: $


*/

