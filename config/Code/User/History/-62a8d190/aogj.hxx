/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: typedefs_E2E.hxx,v 1.5 2019/11/26 11:08:32 simona.desanctis Exp $

$Name:  $

$State: Exp $

*/

#ifndef TYPEDEFS_E2E_HXX
#define TYPEDEFS_E2E_HXX

#include "E2E_TypeEquiv.hxx"
#include "E2E_enum.hxx"
#include "E2E_types.hxx"

/* typedef  dell'ME2E  */
typedef enum {INIT, I1ST, S_SAT, E_SAT, S_CTR, E_CTR, S_ITG, ITG, E_ITG, SHD} sched_state_type;

E2E_ENUM(Initialization_type, INIFLAG, EXEFLAG, ENDFLAG);

typedef enum {EARTH, SUN, MARS} CentralBodyType;

typedef enum { SUN_P, EARTH_P, INERTIAL_P } PointingOptionType;

typedef enum {FULL_DYNAMICS, IDEAL_ATTITUDE, OPEN_LOOP} SimType;

#if 0
typedef struct
{
   TrajectoryPhaseType   TrajectoryPhase;
   CentralBodyType       CentralBody;
   PointingOptionType    PointingOption;
   DOUBLE                PointingDirection[3]; 
}OrbitPhaseType;


typedef struct
{
   DOUBLE         Time;
   OrbitPhaseType OrbitPhase;
   DOUBLE         DeltaV[3];
   INT32          TrajectoryOverride;
   INT32          AttitudeOverride;
   DOUBLE         Position[3];
   DOUBLE         Velocity[3];
   DOUBLE         Quaternion[4];
} buffer_simcommand_type;
#endif //0


/* typedef del DM */
typedef enum {PHASE_0, PHASE_1, PHASE_2, PHASE_3} SimulationPhase_type;


/* typedef generici  */

typedef enum ThrPhaseTyp {Rise, Decay} ThrPhaseType;

typedef enum {EQUIDISTANT_CYLINDRICAL, SINUSOIDAL} Projection_type;




typedef struct
{
   DOUBLE Position_GRF[3];
   DOUBLE Attitude_GRF[4];
  
} NodeType;


typedef struct
{
   INT32         NodeNum;
   NodeType      Node[10];

} GEOMETRY_type;



#endif // TYPEDEFS_E2E_HXX



/* ME2E CVS footer

Full file history:

$Log: typedefs_E2E.hxx,v $
Revision 1.5  2019/11/26 11:08:32  simona.desanctis
- typedef definition for CM simulator added

Revision 1.4  2018/08/24 08:16:05  simona.desanctis
- Definition of the new structure DYN_STATE_type

Revision 1.3  2017/10/25 13:00:05  simona.desanctis
- typedef enum of Projection_type added

Revision 1.2  2017/01/10 16:01:49  simona.desanctis
- include guard introduced

Revision 1.1.1.1  2015/10/19 12:04:42  EXM2018
ME2E Pre-Release


*/
