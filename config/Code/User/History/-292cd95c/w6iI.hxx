/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#ifndef GE_GUIDANCE_HXX
#define GE_GUIDANCE_HXX
//#include "E2E_inpout.hxx"
#include <cstdint>

class GE_Guidance_class
{
 private:

   struct GUI_type
   { 
     
     double P_TCon;
     double P_LUT_Dim[2];
 
     static int const dim1 = 50;
     static int const dim2 = 1000;
     static int const dim3 = 4000;

     double P_machInLkUp[dim1];
     double P_cDtrimLkUp[dim1];
     double P_cLtrimLkUp[dim1];
     double P_cNtrimLkUp[dim1];
     double P_tauNtrimLkUp[dim1];
  
     double P_RinLkUp[dim2];
     double P_cSndLkUp[dim2];
     double P_rhoNomLkUp[dim2];
     double P_HatmLkUpFilt[dim2];

     double P_muGui0;
     double P_omgMuGui0;

     double P_MuDim;
     double P_uMuGuiRs[dim3];
     double P_MuGuiRs[dim3];
     double P_xCoMGuiRs[dim3][6];
     double P_gNEDGuiRs[dim3][3];

     uint32_t D_CS;
     double D_xMuGui_prev[2];

     double O_muGuiOut;
     double O_xCoMGui[6];

     double O_xMuGui[2];
     double O_umuGuiOut;
     double O_cNtauN[2];
     double O_RhoHatm[2];
     double O_CDCL[2];
     double O_cSound;
     double O_Mach;

   } GUI;

 public:
   void GE_GUI_Read(void);
   void GE_GUI_Init(double *xMuGui);

   void GE_GUI_Exec(double xCoMNav[6], double *xCoMGui, double *DragLift, double *RhoHatm, double *cNtauN, double *gNED, double *xMuGui, double *uMuGui);             
                                          
   void GE_GUI_Exit(void);
   void GE_GUI_WriteDebugFile(E2E_PrintOutput *outfile);
};

#endif // GE_GUIDANCE_HXX
/* ME2E CVS footer

Full file history:

$Log: $


*/

