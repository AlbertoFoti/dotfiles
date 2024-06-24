/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/

#include <cstdlib>
#include <cmath>

//#include "E2E_inpout.hxx"
#include "RW_DHSDM_IF.hxx"
#include "DHS_GE.hxx"
#include "GE_GNC.hxx"

static GE_GNC_class GE_GNC;


static void WriteDebugFile(Initialization_type iniflg)
{
   static E2E_PrintOutput outfile;
   outfile.set_group("GE_GNC_0", iniflg);
   GE_GNC.GE_GNC_WriteDebugFile(&outfile);
}

void DHS_GE_Read(void)
{
   GE_GNC.GE_GNC_Read();
/*   E2E_ReadFile file("INPUTFILES/dhs_ge.DHS"); */

#if 0
   /********************************************************************/
   /*    Error on Attitude Knowledge				        */
   /********************************************************************/
   /* Read Error on Attitude Knowledge  (COASTING_DEEP_SPACE)    [deg] */
   
   file.readReal(DHS_GE.P_ErrAttDeg, 3);
   DHS_GE.D_AttNavigationError[0] = DegToRad(DHS_GE.P_ErrAttDeg[0]);
   DHS_GE.D_AttNavigationError[1] = DegToRad(DHS_GE.P_ErrAttDeg[1]);
   DHS_GE.D_AttNavigationError[2] = DegToRad(DHS_GE.P_ErrAttDeg[2]);

   /********************************************************************/
   /*   IMU Calibration Section 				               */
   /********************************************************************/
   /* Read IMU1 Accelerometer Bias [m/s^2]                             */
   file.readReal(DHS_GE.P_ACC_Bias, 3);

   /* Read IMU1 Gyro Scale Factor                                      */
   file.readReal(DHS_GE.P_GYR_SF, 3);

   /* Read IMU1 Gyro Scale Factor                                      */
   file.readReal(DHS_GE.P_GYR_SFNL, 3);

   /* Read IMU1 Acc  Bias Residual Compensation in DM-GNC axes     [%] */
   file.readReal(DHS_GE.P_AccBiasResidual, 3);

   /* Read IMU1 Gyro SF Residual Compensation in DM-GNC axes       [%] */
   file.readReal(DHS_GE.P_GyrSfResidual, 3);

#endif // 0
/********************************************************************/
/*  Output Files Timing Section 	                             */
/********************************************************************/

#if 0
   /* Read the Control Step*/
   file.readReal(&DHS_GE.P_DhsStep);

   /* Read the Output File1 generation Option, Scheduling Rate , Phase wrt PPS, Start Time, Stop Time */
   file.readInteger(&DHS_GE.P_OutFile_OPT);
   file.readReal(&DHS_GE.P_OutFile_SchedRate);
   file.readReal(&DHS_GE.P_OutFile_StartTime);
   file.readReal(&DHS_GE.P_OutFile_StopTime);
#endif // 0
      
   return;
}

void DHS_GE_Init(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type *DhsOutput)
{
   GE_GNC.GE_GNC_Init(DhsInput, DhsOutput);

   WriteDebugFile(INIFLAG);
   return;
}

/******************************************************************************/
void DHS_GE_Exec(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type *DhsOutput)
{
   GE_GNC.GE_GNC_Exec(DhsInput, DhsOutput);


   // Mettere un downsampling
   WriteDebugFile(EXEFLAG);
}

void DHS_GE_Exit(void)
{
   WriteDebugFile(ENDFLAG);

   GE_GNC.GE_GNC_Exit();
}


/* ME2E CVS footer

Full file history:

$Log: $


*/

