/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: object_public_typedefs.hxx,v 1.9 2020/05/30 07:52:36 ludovico.garin Exp $

$Name:  $

$State: Exp $

*/


#ifndef OBJECT_PUBLIC_TYPEDEFS_HXX
#define OBJECT_PUBLIC_TYPEDEFS_HXX
#include "E2E_TypeEquiv.hxx"
#include "typedefs_E2E.hxx"

#include "../Utils/types_def.hxx"

// Initial Condition Structure 
struct InitialCondition_type
{  
   INT32   FrameOpt,
           InputOpt;
   DOUBLE  Position[3];
   DOUBLE  Velocity[3];
   DOUBLE  Omega[3];
   DOUBLE  Quaternion[4];

   INT32   Year,
           Month,
           Day,
           Hour,
           Min;
   DOUBLE  Sec;
   DOUBLE  InitJulianDate; 


   DOUBLE  DeltaVel_1_CRF[10][3],
           DeltaVel_2_CRF[10][3];
   DOUBLE  DeltaOmg_1_CRF[10][3],
           DeltaOmg_2_CRF[10][3];

   DOUBLE  ThrMoog_initial_propellant_mass;

};



// satdyn Model public data type
struct buffer_satdyn_type
{
      INT32  ID;

      DOUBLE Mass,
             CRF_Pos_GRF[3],
             CRF_Quat_GRF[4],
             Inertia[6],
             TankNum,
             FuelTankMass[4];

      DOUBLE CRF_Position[3],
             CRF_Velocity[3],
             CRF_Acceleration[3];

      DOUBLE GRF_Position[3],
             GRF_Velocity[3],
             GRF_Acceleration[3],
             GRF_NoGravAccel[3];
             
      DOUBLE Quaternion_IRF[4],
             Omega[3],
             OmegaDot[3];

      DOUBLE ExternalForceCRF[3];
      DOUBLE ExternalTorquesCRF[3];

      DOUBLE IRF2CRF[3][3];

      INT32    NodeNum;
      NodeType Node[10]; 

};

// End satdyn model (RIGDYN and POINTDYN) public data type

struct buffer_dcapdyn_type
{
   buffer_satdyn_type Body[10];
};

// End satdyn model public data type



// OUTSIDEWORLD Model public data type
struct buffer_outsideworld_type
{
   INT32  BodyName;             //????
   INT32  SunEclipseFlag;
   INT32  LandingFlag;          
   INT32  LandingContact;       // output of contact model; ID of the impacting leg
   INT32  SensorLandingContact;    

   DOUBLE JulianDate2000;
   DOUBLE Illumination;

   DOUBLE SunEarthVector[4],   // Earth wrt Sun  in EME2000 - available in NEP,IPP 
	   SunMarsVector[4],    // Mars  wrt Sun  in EME2000 - available in IPP,NMP
          MarsEarthVector[4];  // Earth wrt Mars in EME2000 - available in NMP 

   DOUBLE SunVector[4],        // Sun   vector wrt S/C in IRF frame (EME2000/MMED)
          EarthVector[4],      // Earth vector wrt S/C in IRF frame (EME2000/MMED)  //CM only 
          MarsVector[4],       // Mars  vector wrt S/C in IRF frame (EME2000/MMED)  //CM only 
          MoonVector[4];       // Moon  vector wrt S/C in IRF frame (EME2000/MMED)  //CM only 

   DOUBLE EarthSunVelocity[4], // Earth velocity wrt Sun : used for the transition to IPP  //CM only 
          MarsSunVelocity[4];  // Mars  velocity wrt Sun : used for the transition to NMP  //CM only 


   DOUBLE MJ2000toMMED[9];      //CM only 
   DOUBLE GravityGradient[6];
   DOUBLE GravitationalAccel[3]; // Sum on geopotential and third body accelerations 	   

   DOUBLE EarthOccultAngle;    // DM only : DA ELIMINARE

   DOUBLE RefMeridianAngle,
          Longitude,
          Latitude,
          RightAscension,
          SurfHeight,
          AreoidHeight,
          SolarLongitude, 
          LocalSolarTime;

   DOUBLE AtmDensity,
          AtmTemperature,
          AtmPressure,
          SoundVelocity,
          MeanFreePath,
          AirViscosity,
          Gamma_ratioSpecificHeats,
          DustMassMixingRatio,
	   MolecularGasConstant,
          WindVelocity_IRF[3],
          WindMCD_NED[3],
          PlaneNormal_IRF[3];

//   DOUBLE MaxSlope,
//	   SlopeAzimuth,
//	   SlopedPlaneOrigin[3];


};



// ENVIRONMENT Model public data type
struct buffer_environment_type
{
   // for RIGDYN
   DOUBLE Force_GRF[3];   
   DOUBLE Torque_GRF[3];   
   
   // for NODES
   static const INT32 FnodesNum = 1;
   INT32 FnodesIndex[1];
   DOUBLE Force_NRF[1][3];
   DOUBLE Torque_NRF[1][3];

   DOUBLE Mach;
   DOUBLE SuttGravFlux;

   DOUBLE SunAspectAngle;  
   DOUBLE EarthAspectAngle;

};
// End ENVIRONMENT model public data type


struct buffer_aerodynamic_type
{
   // for RIGDYN
   DOUBLE Force_GRF[3];
   DOUBLE Torque_GRF[3];

   // for NODES
   static const INT32 FnodesNum = 1;
   INT32 FnodesIndex[1];
   DOUBLE Force_NRF[1][3];
   DOUBLE Torque_NRF[1][3];

   DOUBLE Mach;
   DOUBLE SuttGravFlux;

} ;
// End AERODYNAMIC model public data type



// PARACHUTE Model public data type
struct buffer_parachute_type
{
 // PARACHUTE model
   INT32 configuration_id;

   //DOUBLE Force_GRF[3];   
   //DOUBLE Torque_GRF[3];   

   DOUBLE Force_BRF[3];   
   DOUBLE Torque_BRF[3];   

   // for NODES
   static const INT32 FnodesNum = 1;
   INT32 FnodesIndex[1];
   DOUBLE Force_NRF[1][3];
   DOUBLE Torque_NRF[1][3];
 

};
// End PAS amd PMB model public data type


#if 0
// GYR_TASI Model public data type
typedef struct
{
   INT32   GYRNum;

   DOUBLE *MeasuredOmega;

   DOUBLE  *MeasuredIntegratedOmega;
   DOUBLE  *TotalAngle;

   DOUBLE  *ScaleFactor;

   INT32    AngRateFlag[3];
    
} buffer_gyr_type;
// End GYR_TASI model public data type




// ACC_TASI Model public data type
typedef struct
{
   INT32   ACCNum;

   DOUBLE  *MeasuredAcceleration;
   DOUBLE  *MeasuredIntegratedAcc;
   DOUBLE  *TotalVelocity;
    
} buffer_acc_type;
// End ACC_TASI model public data type
#else
// ACCELEROMETER  Model public data type
struct buffer_acc_type
{
   INT32   ACCNum;

   UINT32  **IntCumulatedVelocity;   // Nsamples x GyrNum 
   UCHAR   **SaturationFlag;         // Nsamples x AccNum
   UCHAR    *ValidityFlag;           // Nsamples
   UINT32   *AccTimeTag;             // Nsamples  

   DOUBLE  **CumulatedVelocity;      // Nsamples x AccNum

};
// End ACC model public data type


// GYRO Model public data type
struct buffer_gyr_type
{
   INT32   GYRNum;

   UINT32  **IntCumulatedAngle;  // Nsamples x GyrNum 
   UCHAR   **SaturationFlag;     // Nsamples x GyrNum  
   UCHAR    *ValidityFlag;       // Nsamples  
   UINT32   *GyroTimeTag;        // Nsamples  

   DOUBLE  **CumulatedAngle;     // Nsamples x GyrNum  
   
};
// End GYRO model public data type
#endif //0


// STAR TRACKER model public data type
struct buffer_str_type
{

    INT32  *OperativeMode;
    INT32  *MeasOk;
    DOUBLE *TimeTag;    

    DOUBLE **Q_Measured;
    DOUBLE **w_Measured;

};
// End STAR TRACKER model public data type



struct buffer_sds_type
{
    //SDS_MOOG 
    INT32   *Avail;
    INT16  **QuantCurrents;       //Nsamples x 4  
    DOUBLE **Currents;           //Nsamples x 4  
 
};
// End SDS model public data type


// MODEL_TEMPLATE Model public data type
struct buffer_rda_type
{

    INT32 OnOff;
    INT32 Avail;
    INT32 AntennaIndex;
    INT32 Refresh; 

    DOUBLE Slant[4];
    DOUBLE SlantVelocity[4];
    DOUBLE Velocity[3];   // for consistency with old algorithm

};
// End RDA_ALS and RDA_HF model public data type





// Thruster  Model public data type
struct buffer_thruster_type
{
   DOUBLE  Force_GRF[3],
           Torque_GRF[3];

   // for NODES
   INT32  FnodesNum;
   INT32  *FnodesIndex;
   DOUBLE (*Force_NRF)[3];    // il contenuto di Force_NRF è un vettore di DOUBLE [3]
   DOUBLE (*Torque_NRF)[3];

   // for PointMass variation in node
   INT32   MnodesNum;
   INT32   *MnodesIndex;
   DOUBLE  *MassFlow_node;

   DOUBLE *THR_Force;
   //INT32  *THR_OnOff;
   //INT32  *THR_Active;

   INT32  THR_Active; 

   INT32   THRTankNum;
   DOUBLE *THR_TankMassFlow;
   DOUBLE *THR_ConsumedTankMass;

   DOUBLE  THR_TankPressure;
   DOUBLE  THR_TankTemperature;

   // for THR_MOOG 
   DOUBLE (*THR_Tank_ToTdeltaCoG_GRF)[3];
   DOUBLE (*THR_Tank_ToTdeltaICoG_GRF)[6];
   INT32   THRNum;

};
// End  Thruster model public data type


// Plume Model public data type
struct buffer_plume_type
{
   DOUBLE Force_BRF[3];
   DOUBLE Torque_BRF[3]; 

   // for NODES
   static const INT32 FnodesNum = 1;
   INT32 FnodesIndex[1];
   DOUBLE Force_NRF[1][3];
   DOUBLE Torque_NRF[1][3];

};

// End Plume model public data type

template <size_t N>
struct buffer_thr_type
{
   static constexpr size_t RCS_num = N;
   DOUBLE RCS_Command[RCS_num];
   DOUBLE RCS_CommandTimeTag[RCS_num];
   DOUBLE RCS_CommandDurationTime[RCS_num];

   DOUBLE RCS_ControlForce[3];
   DOUBLE RCS_ControlTorque[3];

   INT32 RcsOnOff;
};

static constexpr size_t SH_num = 6;
static constexpr size_t BP_num = 4;
static constexpr size_t GE_num = 4;

// DHS Model public data type
struct buffer_dhs_type
{       
   INT32  Pas1Opening;
   INT32  Pas1LidRelease;  
   INT32  Pas1Release;  
   INT32  Pas2Opening;
   INT32  FrontShieldSeparation;
   INT32  LandingLegsOpening;
   INT32  RJseparation;
   INT32  Drop;
   
   buffer_thr_type<GE_num>  GE; 
   buffer_thr_type<SH_num>  SH; 
   buffer_thr_type<BP_num>  BP; 
   INT32  BRE_WarmingUp;   // not used
   INT32  BRE_OnOff;
   //DOUBLE BRE_PRTValve[3];    // no more used 
   INT32  BRE_ValveCommand[3];

   INT32  RcsOnOff;

};
// End DHS model public data type






// COMMAND Model public data type
struct buffer_command_dm_type
{

   INT32  TransitionRequired;
   INT32  NextPhase;
   INT32  SupParachuteOpening;  
   INT32  SupLidRelease;  
   INT32  SupParachuteRelease;  
   INT32  SubParachuteOpening;    
   INT32  FrontShieldSeparation;
   INT32  LandingLegsOpening;
   INT32  RJseparation;              


//} buffer_command_type;
};



// COMMAND_CM Model public data type
struct buffer_command_cm_type
{

   INT32  TransitionRequired;
   INT32  NextPhase;

   INT32  RcsOn;
   INT32  RcsOff;

   DOUBLE RCS_Command[9],
          RCS_CommandTimeTag[9];

};
// End COMMAND CM model public data type




// MODEL_TEMPLATE Model public data type
typedef struct
{


} buffer_model_template_type;



typedef struct
{


} buffer_xxxxxxx_type;

// End MODEL_TEMPLATE model public data type

using namespace std;

#endif // OBJECT_PUBLIC_TYPEDEFS_HXX


/* ME2E CVS footer
Full file history:

$Log: object_public_typedefs.hxx,v $
Revision 1.9  2020/05/30 07:52:36  ludovico.garin
Struct in C++ style to avoid anonymous function asign error
     in view of C++11 transition

Revision 1.8  2020/01/31 09:01:23  simona.desanctis
- in buffer_outsideworld_type added PlaneNormal_IRF
- new buffer_plume_type

Revision 1.7  2019/11/26 11:24:08  simona.desanctis
- in InitialCondition_type add ThrMoog_initial_propellant_mass
- unused buffer_slugdyn_type and buffer_configuration_type removed
- in buffer_acc_type and buffer_gyr_type
  SaturationFlag and ValidityFlag defined as UCHAR instaed of INT32
  AccTimeTag and GyroTimeTag added
- buffer_str_type aligned to STR_TDI model output
- buffer_sds_type aligned to SDS_MOOG model output
- in buffer_rda_type INT32 Refresh added
- buffer_thruster_type aligned to the current models used
- in buffer_dhs_type remove DOUBLE BRE_PRTValve[3]
- buffer_dhs_cm_type rewritten

Revision 1.6  2018/08/24 08:24:20  simona.desanctis
- In section buffer_satdyn_type
   dimension of FuelTankMass updated
- In section outsideworld_dm
   MolecularGasConstant and Gamma_ratioSpecificHeats added
   SensorLandingContact added
- In section buffer_environment_type
   specific output for nodes added
- In section buffer_aerodynamic_type
   specific output for nodes added
- In section buffer_parachute_type
   specific output for nodes added
   Force_GRF and Torque_GRF  removed
- In section buffer_thruster_type
   specific output for nodes added
   THRTankNum added
- removed not used code.

Revision 1.5  2018/01/25 10:50:37  simona.desanctis
- In buffer_dhs_type added INT32 BRE_ValveCommand replacing DOUBLE BRE_PRTValve[3];

Revision 1.4  2017/10/25 13:06:24  simona.desanctis
- in buffer_outsideworld_type
     new LandingContact, ID of the impacting leg
     rename WindVelocity_NED --> WindMCD_NED
- in buffer_parachute_type
     delta_Mass replaced by configuration_id
- in buffer_acc_type
     new **SaturationFlag and *ValidityFlag
     remove GlobalSaturationFlag
- in buffer_dhs_type
     new Pas1LidRelease
- in buffer_command_dm_type
     new SupLidRelease

Revision 1.3  2017/01/11 08:32:50  simona.desanctis
- include guard introduced
- buffer_outsideworld_intpl_type merged in buffer_outsideworld_type;
- modified buffer_environment_type
- new buffer_aerodynamic_type
- modified buffer_str_tasi_type renamed ad buffer_str_type;
- modified buffer_sds_type

Revision 1.2  2016/08/30 13:48:31  simona.desanctis
- remove buffer_imu_type
- update buffer_acc_type
- update and rename buffer_gyr_type
- remove  mach, qbar, TotalAngleOfAttack, AerodynRoll from outsideworld_dm buffer

Revision 1.1.1.1  2015/10/19 12:04:42  EXM2018
ME2E Pre-Release


*/
