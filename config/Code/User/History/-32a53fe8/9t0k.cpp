/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#include <cstdint>
#include "GE_GNC.hxx"
#include "RW_DHSDM_IF.hxx"
#include "timing_E2E.hxx"

void GE_GNC_class::GE_GNC_Read(void)
{
   //GE_Gui.GE_GUI_Read();
   GE_Nav.GE_NAV_Read();
   //GE_Ccn.GE_CCN_Read();
   //GE_Acn.GE_ACN_Read();
}

    double xMuGui[2];
    double uMuGui;
    uint8_t BrmStatus;

void GE_GNC_class::GE_GNC_Init(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type *DhsOutput)
{
   //GE_Gui.GE_GUI_Init(xMuGui);
   
   GE_Nav.GE_NAV_Init(DhsInput->IMU1_CumulatedAngle, DhsInput->IMU1_GyrTimeTag, DhsInput->IMU1_CumulatedVelocity, DhsInput->IMU1_AccTimeTag);
   
   //GE_Ccn.GE_CCN_Init();
   
   //GE_Acn.GE_ACN_Init(xMuGui, uMuGui, BrmStatus);

}

void GE_GNC_class::GE_GNC_Exec(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type *DhsOutput)
{
   // Output allocation that will be filled

   bool imu_validity =
       DhsInput->IMU1_Validity && !DhsInput->IMU1_SaturationFlag[0] &&
       !DhsInput->IMU1_SaturationFlag[1] && !DhsInput->IMU1_SaturationFlag[2];

   double xCoMNav[6];
   double xAttNav[6];

   double aAngDer[3];
   double gNED[3];
   GE_Nav.GE_NAV_Exec(DhsInput->IMU1_CumulatedAngle, DhsInput->IMU1_GyrTimeTag,
                      DhsInput->IMU1_CumulatedVelocity,
                      DhsInput->IMU1_AccTimeTag, imu_validity, xCoMNav, xAttNav,
                      aAngDer, gNED);

   static int counter = 0;
   
   counter++;
   if (counter == 10)
   {
      counter = 0;

      double DragLift[2];
      double RhoHatm[2];
      double cNtauN[2];

      double dug;
      double tBrm;

      int dirBrm;
      double xCoMGui[6];
      //GE_Gui.GE_GUI_Exec(xCoMNav,xCoMGui, DragLift, RhoHatm, cNtauN, gNED, xMuGui,
      //                   &uMuGui);

      //GE_Ccn.GE_CCN_Exec(xCoMGui, xCoMNav, BrmStatus, xMuGui, DragLift, RhoHatm,
      //                   gNED, dug, tBrm,
      //                   dirBrm);

      //GE_Acn.GE_ACN_Exec(
      //    dug, tBrm, dirBrm, uMuGui, xMuGui, xAttNav, xCoMNav, aAngDer, cNtauN,
      //    RhoHatm, BrmStatus, DhsOutput->GE_ControlTorque, DhsOutput->GE_CommandDurationTime,
      //    DhsOutput->GE_ControlActivation, DhsOutput->GE_ThrusterActivation);
      
      
      
   }
   
}

void GE_GNC_class::GE_GNC_Exit(void)
{
   GE_Gui.GE_GUI_Exit();    
   GE_Nav.GE_NAV_Exit();
   GE_Ccn.GE_CCN_Exit();
   GE_Acn.GE_ACN_Exit();
}

void GE_GNC_class::GE_GNC_WriteDebugFile(E2E_PrintOutput *outfile)
{
   outfile->E2E_writeVar(TimingInfo->Time, "s", "t", "Simulation Time");
   GE_Gui.GE_GUI_WriteDebugFile(outfile);   
   GE_Nav.GE_NAV_WriteDebugFile(outfile);
   GE_Ccn.GE_CCN_WriteDebugFile(outfile);   
   GE_Acn.GE_ACN_WriteDebugFile(outfile); 
}

/* ME2E CVS footer

Full:85
file history:

$Log: $


*/

