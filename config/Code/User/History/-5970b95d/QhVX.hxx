/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: RW_DHSDM_IF.hxx,v 1.2 2021/01/07 16:49:18 ludovico.garin Exp $

$Name:  $

$State: Exp $

*/
#include <cstdint>

struct DHS_DM_INPUT_type
{
   double Time;
   double JD2000;
   double LaunchJD2000;

   /* IMU1 */
   unsigned int   IMU1_CumulatedVelocity[3]; 
   unsigned int   IMU1_CumulatedAngle[3]; 
   unsigned char  IMU1_Validity;
   unsigned char  IMU1_SaturationFlag[3];
   unsigned int   IMU1_AccTimeTag;
   unsigned int   IMU1_GyrTimeTag;

   /* IMU2 */
   unsigned int   IMU2_CumulatedVelocity[3]; 
   unsigned int   IMU2_CumulatedAngle[3]; 
   unsigned char  IMU2_Validity;
   unsigned char  IMU2_SaturationFlag[3];
   unsigned int   IMU2_AccTimeTag;
   unsigned int   IMU2_GyrTimeTag;

   /* RDA */
   //unsigned char  RDA_Validity;      //uint8_t
   //unsigned char  RDA_BeamActive;    //uint8_t
   //unsigned char  RDA_Refresh;       //uint8_t
   unsigned int  RDA_Validity;      //uint32_t
   unsigned int  RDA_BeamActive;    //uint32_t
   unsigned int  RDA_Refresh;       //uint32_t
   double RDA_Slant;
   double RDA_SlantVelocity; 

   /* CMGNC EstQuaternion */
   double  InitQuaternion[4];

   /* Contact Sensor */
   unsigned char  ContactDetected; 

   int TRG_ParachuteOpening;
   int TRG_SecondParachuteOpening;
   int TRG_FrontShieldRelease;
   int TRG_LandingLegsOpening;
   int TRG_RJSeparation;
}; 


struct DHS_DM_OUTPUT_type
{
   /* Rivedere i tipi */
   int TRG_ParachuteOpening;
   int TRG_SecondParachuteOpening;
   int TRG_FrontShieldRelease;
   int TRG_LandingLegsOpening;
   int TRG_RJSeparation;


   // Events passed to dynamic subject to CU delays
   int    Pas1Opening;
   int    Pas1LidRelease;  
   int    Pas1Release;  
   int    Pas2Opening;
   int    FrontShieldSeparation;
   int    LandingLegsOpening;
   int    RJseparation;
   
   int    LTE_Command[8];   //UCHAR
   double LTE_CommandDurationTime[8];             
   int    BRE_ValveCommand[3];  // RIVEDERE IL TIPO

   //int    LTE_OnOff; //UCHAR  // mi serve per spegnerli 
   int    BRE_OnOff;          // da BEWU in poi 
   
   double GE_CommandDurationTime[4];
   uint8_t GE_ControlActivation;
   double GE_ThrusterActivation[4];
   double GE_ControlTorque[3];
}; 


typedef struct
{
   double Position[3]; 
   double Velocity[3]; 
   double Quaternion[4]; 
   double Omega[3]; 
   double SurfHeight; 
}DYN_STATE_type; 


void DHS_DM_Read (void);

void DHS_DM_Init(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type  *DhsOutput);

void DHS_DM_Exec(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type  *DhsOutput);

void DHS_DM_Exit(void);

void DHS_DM_Patch (DYN_STATE_type *Input);



/* ME2E CVS footer

Full file history:

$Log: RW_DHSDM_IF.hxx,v $
Revision 1.2  2021/01/07 16:49:18  ludovico.garin
Added failure of trigger acknowledgment

Revision 1.1  2019/11/26 10:54:56  simona.desanctis
- New files


*/
