/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#ifndef DHS_GE_HXX
#define DHS_GE_HXX

/*
   struct DHS_GE_type
   {
      double P_ErrAttDeg[3];

      double P_ACC_Bias[3];
      double P_GYR_SF[3];
      double P_GYR_SFNL[3];
      double P_AccBiasResidual[3];
      double P_GyrSfResidual[3];

      double P_DhsStep;
      uint8_t P_OutFile_OPT;
      double P_OutFile_SchedRate;
      double P_OutFile_StartTime;
      double P_OutFile_StopTime;

      double D_AttNavigationError[3];
   } DHS_GE;
*/

void DHS_GE_Read(void);
void DHS_GE_Init(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type  *DhsOutput);
void DHS_GE_Exec(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type  *DhsOutput);
void DHS_GE_Exit(void);


#endif // DHS_GE_HXX

/* ME2E CVS footer

Full file history:

$Log: $


*/


