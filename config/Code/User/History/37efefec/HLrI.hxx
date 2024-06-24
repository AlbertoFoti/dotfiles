/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#ifndef GE_COMCONTROL_HXX
#define GE_COMCONTROL_HXX
//#include "E2E_inpout.hxx"
#include "GE_DxOnLV01.hxx"
#include "GE_CoMPars01.hxx"
#include "GE_CL_Dr_S01.hxx"
#include "GE_CL_Dr_H01.hxx"
#include "GE_EM_Dr_H01.hxx"
#include "GE_EM_Dr_S01.hxx"
#include "GE_CL_Cr01.hxx"

class GE_CoMControl_class
{

 private:
   GE_DxOnLV01_class GE_DxOnLV01;
   GE_CoMPars01_class GE_CoMPars01;
   GE_CL_Dr_S01_class GE_CL_Dr_S01;
   GE_CL_Dr_H01_class GE_CL_Dr_H01;
   GE_EM_Dr_H01_class GE_EM_Dr_H01;
   GE_EM_Dr_S01_class GE_EM_Dr_S01;
   GE_CL_Cr01_class GE_CL_Cr01;

   struct CCN_type
   {

      double DxDrSest_prev[2];  
      double xDDrSest_prev[2];
      double DxDrHest_prev[2];
      double xDDrHest_prev[2];

      double P_BUGMAX;
      double P_GHVMAX;
      double P_tBrmGui[8];
      int P_dirBrmGui[8];
      double P_KyGui[8];
      double P_KheadGui[8];

      uint8_t BrmStatus_prev;

      double O_tbr;
      int O_dir_Br;

   } CCN;

 public:
   void GE_CCN_Read(void);
   void GE_CCN_Init();

   void GE_CCN_Exec(double xCoMGui[6], double xCoMNav[3], 
                    uint8_t BrmStatus, double xMuGui[2],
                    double DragLift[2], double RhoHatm[2],
                    double const gNED[3], 
                    double &dug, double &tBrm, int &dirBrm);

   void GE_CCN_Exit(void);
   void GE_CCN_WriteDebugFile(E2E_PrintOutput *outfile);
};

#endif 


// GE_COMCONTROL_HXX
/* ME2E CVS footer

Full file history:

$Log: $


*/

