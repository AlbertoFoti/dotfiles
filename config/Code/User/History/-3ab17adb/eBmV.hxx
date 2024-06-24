/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: FAILURES.hxx,v 1.1 2022/03/18 16:15:56 ludovico.garin Exp $

$Name:  $

$State: Exp $

*/

#ifndef FAILURES_HXX
#define FAILURES_HXX

#include "types_def.hxx"

// XYZ Code
// X=1 == IMU1 ; X=2 == IMU2 ; X=3 == RDA
// Y<2 == VALIDITY ; Y>2 == DEGRADED
// Z=1 == INIT  ; Z=0 == END
#define IMU1_NOTVALID_INIT          111
#define IMU1_NOTVALID_END           110
#define IMU2_NOTVALID_INIT          211
#define IMU2_NOTVALID_END           210
#define IMU1_SATURATED_INIT         121
#define IMU1_SATURATED_END          120
#define IMU2_SATURATED_INIT         221
#define IMU2_SATURATED_END          220
#define IMU1_DEGRADED_INIT          131
#define IMU1_DEGRADED_END           130
#define IMU2_DEGRADED_INIT          231
#define IMU2_DEGRADED_END           230
#define IMU1_NULLACCTIMETAG_INIT    141
#define IMU1_NULLACCTIMETAG_END     140
#define IMU1_NULLGYROTIMETAG_INIT   151
#define IMU1_NULLGYROTIMETAG_END    150
#define IMU2_NULLACCTIMETAG_INIT    241
#define IMU2_NULLACCTIMETAG_END     240
#define IMU2_NULLGYROTIMETAG_INIT   251
#define IMU2_NULLGYROTIMETAG_END    250


#define RDA_NOTVALID_INIT       311
#define RDA_NOTVALID_END        310
#define RDA_FROZEN_INIT         361
#define RDA_FROZEN_END          360
#define RDA_SLANTNEG_INIT       371
#define RDA_SLANTNEG_END        370
#define RDA_BEAM0_NOTVALID_INIT 321
#define RDA_BEAM0_NOTVALID_END  320
#define RDA_BEAM1_NOTVALID_INIT 331
#define RDA_BEAM1_NOTVALID_END  330
#define RDA_BEAM2_NOTVALID_INIT 341
#define RDA_BEAM2_NOTVALID_END  340
#define RDA_BEAM3_NOTVALID_INIT 351
#define RDA_BEAM3_NOTVALID_END  350

// LMNP Code
// L=1 : LTE
// M=i : LTE index
// N=0 == OFF; N=1 == ON
// P=1 == INIT  ; P=0 == END


#define LTE1_OFF_INIT            1101          
#define LTE1_OFF_END             1100    
#define LTE1_ON_INIT             1111  
#define LTE1_ON_END              1110  
#define LTE2_OFF_INIT            1201 
#define LTE2_OFF_END             1200 
#define LTE2_ON_INIT             1211 
#define LTE2_ON_END              1210 
#define LTE3_OFF_INIT            1301 
#define LTE3_OFF_END             1300 
#define LTE3_ON_INIT             1311 
#define LTE3_ON_END              1310 
#define LTE4_OFF_INIT            1401 
#define LTE4_OFF_END             1400 
#define LTE4_ON_INIT             1411 
#define LTE4_ON_END              1410 
#define LTE5_OFF_INIT            1501 
#define LTE5_OFF_END             1500 
#define LTE5_ON_INIT             1511 
#define LTE5_ON_END              1510 
#define LTE6_OFF_INIT            1601 
#define LTE6_OFF_END             1600 
#define LTE6_ON_INIT             1611 
#define LTE6_ON_END              1610 
#define LTE7_OFF_INIT            1701 
#define LTE7_OFF_END             1700 
#define LTE7_ON_INIT             1711 
#define LTE7_ON_END              1710 
#define LTE8_OFF_INIT            1801 
#define LTE8_OFF_END             1800 
#define LTE8_ON_INIT             1811 
#define LTE8_ON_END              1810 
#define BRE_FROZEN_COMMAND_INIT  2001
#define BRE_FROZEN_COMMAND_END   2000
#define TRG_PARACHUTEOPENING_INIT        3001 
#define TRG_SECONDPARACHUTEOPENING_INIT  3011 
#define TRG_FRONTSHIELDRELEASE_INIT      3021 
#define TRG_LANDINGLEGSOPENING_INIT      3031 
#define TRG_RJSEPARATION_INIT            3041 

#endif


typedef struct
{
   INT32  FailureCode;
   INT32  NumPar;
   DOUBLE InitTime;
   DOUBLE Param[10];
}FailureEventType;


typedef struct
{
  INT32 FailureNumber; 

  INT32 NextFailure;
  FailureEventType FEV[1000]; 

  INT32  IMU1_InvalidStatus;
  INT32  IMU1_SaturatedStatus;
  INT32  IMU1_DegradedStatus;
  INT32  IMU2_InvalidStatus;
  INT32  IMU2_SaturatedStatus;
  INT32  IMU2_DegradedStatus;
  INT32  IMU1_GyrTimetagNullStatus;
  INT32  IMU1_AccTimetagNullStatus;
  INT32  IMU2_GyrTimetagNullStatus;
  INT32  IMU2_AccTimetagNullStatus;
  INT32  RDA_InvalidStatus;
  INT32  RDA_Frozen;
  INT32  RDA_SlantNeg;
  INT32  RDA_Beam0InvalidStatus;
  INT32  RDA_Beam1InvalidStatus;
  INT32  RDA_Beam2InvalidStatus;
  INT32  RDA_Beam3InvalidStatus;

  INT32  LTE1_OffStatus;
  INT32  LTE1_OnStatus;
  INT32  LTE2_OffStatus;
  INT32  LTE2_OnStatus;
  INT32  LTE3_OffStatus;
  INT32  LTE3_OnStatus;
  INT32  LTE4_OffStatus;
  INT32  LTE4_OnStatus;
  INT32  LTE5_OffStatus;
  INT32  LTE5_OnStatus;
  INT32  LTE6_OffStatus;
  INT32  LTE6_OnStatus;
  INT32  LTE7_OffStatus;
  INT32  LTE7_OnStatus;
  INT32  LTE8_OffStatus;
  INT32  LTE8_OnStatus;

  INT32  BRE_FrozenStatus;
  INT32  BRE_FirstFrozenStatus;

  INT32  TRG_ParachuteOpeningStatus;
  INT32  TRG_SecondParachuteOpeningStatus;
  INT32  TRG_FrontShieldReleaseStatus;
  INT32  TRG_LandingLegsOpeningStatus;
  INT32  TRG_RJSeparationStatus;



  DOUBLE Param0; 
  DOUBLE Param1; 

}FAILURE_Type;


void FAILURE_Read (CHAR IO_FileName[], INT32 *Error, CHAR *Message);

void FAILURE_Init (void);

void FAILURE_Exec (void);

void FAILURE_Apply (DHS_DM_INPUT_type *DhsInput);

void FAILURE_Apply (DHS_DM_OUTPUT_type *DhsPublic);

/* ME2E CVS footer

Full file history:

$Log: FAILURES.hxx,v $
Revision 1.1  2022/03/18 16:15:56  ludovico.garin
Copied from ME2E_03_0_DEVEL ExoMars 2020 on 202-03-18

Revision 1.4  2022/02/17 10:09:59  ludovico.garin
Added failure for accelerometer and gyroscope null time tag.

Revision 1.3  2021/03/08 08:27:40  ludovico.garin
Added all failures used for the robustness

Revision 1.2  2021/01/07 16:49:27  ludovico.garin
Added failure of trigger acknowledgment

Revision 1.1  2019/11/21 14:45:20  simona.desanctis
- New files for new FAILURE model


*/


