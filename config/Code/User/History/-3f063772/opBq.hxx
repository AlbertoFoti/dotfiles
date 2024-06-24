/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: globals_E2E.hxx,v 1.4 2019/11/26 10:58:39 simona.desanctis Exp $

$Name:  $

$State: Exp $

*/



#ifndef GLOBALS_E2E_HXX
#define GLOBALS_E2E_HXX
#include <cstdio>
#include "E2E_types.hxx"

#ifdef MAIN
#define EXT 
#else
#define EXT extern
#endif


EXT   SimulationPhase_type      GlbSimulationPhase;

EXT   INT32  GlbLandingExitOption;
EXT   INT32  Glb_LP_Landed;
EXT   INT32  Glb_THRBP_Active;

EXT   CentralBodyType       GlbCentralBody;	
EXT   CentralBodyType       GlbPreviousCentralBody;	
EXT   INT32		       GlbTransitionOption;

EXT   INT32  REF_FRAME_OPT;
EXT   INT32  DYN_OutOption;
EXT   INT32  COF_OutOption;
EXT   INT32  OSW_OutOption;
EXT   INT32  ENV_OutOption;
EXT   INT32  ARD_OutOption;
EXT   INT32  IMU_OutOption;
EXT   INT32  STR_OutOption;
EXT   INT32  SDS_OutOption;
EXT   INT32  RDA_OutOption;
EXT   INT32  PAS_OutOption;
EXT   INT32  RCS_OutOption;
EXT   INT32  SH_OutOption;
EXT   INT32  BP_OutOption;
EXT   INT32  PIM_OutOption;
EXT   INT32  IDM_OutOption;
EXT   INT32  RCT_OutOption;
EXT   INT32  HFR_OutOption; // Hight Frequency output after MP1 and MP2 inflation start

EXT   INT32  IMU_FlagOpt;
EXT   INT32  STR_FlagOpt;
EXT   INT32  SDS_FlagOpt;
EXT   INT32  RDAHF_FlagOpt;
EXT   INT32  PAS_1_FlagOpt;
EXT   INT32  PAS_2_FlagOpt;
EXT   INT32  PAS_FlagOpt;
EXT   INT32  PASMB_FlagOpt;
EXT   INT32  RCS_FlagOpt;
EXT   INT32  SH_FlagOpt;
EXT   INT32  BP_FlagOpt;
EXT   INT32  PIM_FlagOpt;
EXT   INT32  IDM_FlagOpt;
EXT   INT32  FAILURE_FlagOpt;

EXT   INT32  DHS_FlagOpt;

EXT   FILE    *SimLog; 

EXT   DOUBLE PLANET_GRAVITY_CONST_VAR;
EXT   DOUBLE PLANET_RADIUS_VAR;
EXT   DOUBLE J2_VAR;
EXT   DOUBLE FLATTENING_VAR;
EXT   DOUBLE MERIDIAN_ANGLE_2000_VAR;
EXT   DOUBLE PLANET_ROT_RATE_VAR;
EXT   DOUBLE PLANET_ROT_RATE_DEG_DAY_VAR;
EXT   DOUBLE PLANET_ROT_ACC_VAR;

EXT   DOUBLE SOLAR_FLUX_VAR;

#include "release.hxx"


#endif //GLOBALS_E2E_HXX



/* ME2E CVS footer

Full file history:

$Log: globals_E2E.hxx,v $
Revision 1.4  2019/11/26 10:58:39  simona.desanctis
- add the new flags FAILURE_FlagOpt and HFR_OutOption
- Glb_THRBP_Active added
- add GlbCentralBody, GlbPreviousCentralBody, GlbTransitionOption for CM simulation
  and remove TrajectoryPhase

Revision 1.3  2018/08/24 08:14:18  simona.desanctis
- New global variables GlbLandingExitOption and Glb_LP_Landed
- SLG_OutOption removed
- 'KRO' renamed as 'PIN'
- RCT_OutOption added

Revision 1.2  2017/01/10 16:00:30  simona.desanctis
- include guard introduced
- SDSTNO --> SDS
- new flag ARD_OutOption
- new global variable  orbit_state_type  TrajectoryPhase;
- HIB_Flag removed

Revision 1.1.1.1  2015/10/19 12:04:42  EXM2018
ME2E Pre-Release


*/
