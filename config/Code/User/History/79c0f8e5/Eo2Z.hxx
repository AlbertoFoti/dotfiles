/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: THR_TASI.hxx,v 1.2 2022/09/01 14:35:20 ludovico.garin Exp $

$Name:  $

$State: Exp $

*/

#include "E2E_TypeEquiv.hxx"

class Rk4;
class Configuration;

class Thruster
{

   private:
      // Model internal data type
      typedef enum ThrPhaseTyp {Rise, Decay} ThrPhaseType;
      enum ThrOnOff
      {
         ON = 1,
         OFF = 0
      };

      static constexpr INT  MAX_THR_NUM = 9;
      
      typedef struct
      {
      // THR_TASI instantiation input for each thruster of the assembly
         INT            P_OnOffFlag;
      
         DOUBLE         P_NomMountPoint[3],
                        P_NominalAxis[3],
                        P_ErrMountPoint[3],
                        P_Theta,
                        P_Phi;
      
         DOUBLE         P_MaxForce,
                        P_MinForce,
                        P_NullCommandForce,
                        P_SpecificImpulse;
      
         INT            P_QuantLevel;
      
         DOUBLE         P_MinTOn;
      
         DOUBLE         P_RiseDelay,
                        P_DecayDelay,
                        P_ValveOnDelay,
                        P_ValveOffDelay;
      
         DOUBLE         P_RiseTimeConst,
                        P_DecayTimeConst;
      
         DOUBLE         P_RisePulse,
                        P_RiseDamp,
                        P_DecayPulse,
                        P_DecayDamp,
                        P_RiseSlewRate,
                        P_DecaySlewRate;
      
         CHAR           P_RiseABCD_FileName[80],
                        P_DecayABCD_FileName[80];
      
         INT            P_NoiseShapeType;
      
         DOUBLE         P_Bias,
                        P_FrLow,
                        P_FrHigh,
                        P_NoiseSD,
                        P_NoiseShapingFactor;
      
         INT            P_RandGenID,
                        P_Seed;
      
      // THR_TASI cyclic input for each thruster of the assembly
         INT            I_OnOffFlag;
      
      //   unsigned INT    I_Command;           // Quantised command
         DOUBLE         I_Command;              // DOUBLE to allow quantisation skipping 
         DOUBLE         I_CommandTimeTag,
                        I_CommandDurationTime;  //ABO
      
      // THR_TASI internal data for each thruster of the assembly
         DOUBLE         D_MountPoint_GRF[3],
                        D_ActuatorAxis_GRF[3];
      
         INT            D_OnOffFlag;
      
         DOUBLE         D_NormFeedPressure;
      
         ThrPhaseType   D_Phase;
      
         TimerType      D_RiseDelay,
                        D_DecayDelay,
                        D_ValveOnDelay,
                        D_ValveOffDelay;
      
         TimerType      D_ThrustTimeTag,
                        D_ThrustDurationTime;
      
         DOUBLE         D_RiseKp,  D_RiseKv,
                        D_DecayKp, D_DecayKv,
                        D_Resolution;
      
         DOUBLE         D_T_exp,
                        D_T_sinexp;
      
      //   INT            D_Command,
      //                  D_CurrentCommand,
      //                  D_Command2;
         DOUBLE         D_Command,     // DOUBLE to allow quantisation skipping 
                        D_CurrentCommand,
                        D_Command2;
      
         DOUBLE         D_CommandTimeTag,
                        D_CommandDurationTime,  //ABO
                        D_CurrentCommandTimeTag,
                        D_CurrentTimeConst,
                        D_CurrentKp,
                        D_CurrentKv,
                        D_CurrentSlewRate;
      
         DOUBLE         D_State[4],
                        D_StateDot[4];
      
         INT            D_PrevCommand;
      
         DOUBLE         D_NoiseStDev,
                        D_NoiseGain[3],
                        D_NoiseState[2],
                        D_NoiseForce;
      
      // THR_TASI cyclic output for each thruster of the assembly
         DOUBLE         O_ForceTH,
                        O_Force[3],
                        O_Torque[3];
      
         DOUBLE         O_FuelMassFlow,
                        O_ConsumedFuelMass;
      
         INT            O_OnOff;
      
      } ThrActType;
      
      
      
      
      
      typedef struct
      {
      // THR_TASI instantiation input for the assembly
         INT            P_THRNum,
                        P_PosErrMisFlag,
                        P_QuantisationFlag,
                        P_NoiseFlag;
                        
         DOUBLE         P_O_URFn_Pos_GRF[3],
                        P_URFn_tm_GRF[3][3],
                        P_O_URFm_Pos_URFn[3],
                        P_URFm_tm_URFn[3][3];
                     
         DOUBLE         P_CommandDelay;
                      
         INT            P_DynModel;
                      
         DOUBLE         P_DeltaT;
      
       
      // THR_TASI cyclic input for the assembly
         DOUBLE         I_ItgStep,
                        I_CtrStep;
      
      // THR_TASI internal data for the assembly
         INT            D_NoiseDec,
                        D_NoiseCounter;
      
         TimerType      D_CommandDelay,
                        D_DiscreteExec;
      
         INT            D_OutVarNum;
      
      // THR_TASI cyclic output for the assembly
         DOUBLE         O_TotForce[3],
                        O_TotTorque[3];
      
	 // For nodes
	 CHAR P_NodeID_assembly[80];
	 INT O_NodeIndex_assembly;
         INT P_NodeNum;
	 INT P_TankNum;

         ThrActType    *Act;

#ifdef E2E_VIRTUAL
	 Rk4       *D_rk4;
#endif //E2E_VIRTUAL

	 E2E_PrintOutput outfile;
      
      } THR_type;
      // End model internal data type

      // Private data
      THR_type THR;

      void AllocateThruster                (void);

      void CommandAcquisition              (void);

      void CommandApplication              (void);

      void ConsumedFuel                    (void);

      void NoiseUpdate                     (void);

      void StateDerivative                 (void);

      void ForceTorqueComputation          (void);

      void LoadHeader                      (CHAR VariableName[][31], CHAR Dimension[][16], INT32 *TotVarNum);

      void LoadData                        (DOUBLE *Data, INT32 *VarNum);


   public:
      // Public data
      static int THR_TASI_Num,
                 THR_TASI_EqNum;

      Thruster ()                    { THR_TASI_Num++; };  // constructor

      buffer_thruster_type Public;

      // Public entries
      void THR_TASI_Read                   (const CHAR   IO_FileName[]);
                                           

      void THR_TASI_Init                   (void);

      void THR_TASI_ExecCtrl               (sched_state_type *sched_state);

      void THR_TASI_ExecCont               (sched_state_type *sched_state); 

      void THR_TASI_ExecIntg               (sched_state_type *sched_state);

      void THR_TASI_Exit                   (void);

#ifdef E2E_OLD
      void THR_TASI_InitInteg              (int *ptr, DOUBLE *Vector);
      void THR_TASI_To_Integ               (int *ptr, DOUBLE *VectorDot);
      void THR_TASI_From_Integ             (int *ptr, DOUBLE *Vector);
#endif // E2E_OLD
#ifdef E2E_VIRTUAL
      void THR_TASI_InitInteg              (void);
      void THR_TASI_To_Integ               (void);
      void THR_TASI_From_Integ             (void);
#endif // E2E_VIRTUAL


      void THR_TASI_From_Timing            (sched_state_type *sched_state,
                                            timing_type      *Input);

      template <typename T>
      void THR_TASI_From_Control(sched_state_type *sched_state, const T *Input)
      {

         switch (*sched_state)
         {
            case INIT:
            case S_CTR:

               assert(THR.P_THRNum == Input->RCS_num);
               for (INT ID = 0; ID < THR.P_THRNum; ID++)
               {  
		       // Da sistemare l'onoff Input->RcsOnOff;
                  THR.Act[ID].I_OnOffFlag = Input->RcsOnOff;
                  THR.Act[ID].I_Command = Input->RCS_Command[ID];
                  THR.Act[ID].I_CommandTimeTag = Input->RCS_CommandTimeTag[ID];
                  THR.Act[ID].I_CommandDurationTime =
                      Input->RCS_CommandDurationTime[ID];
               }
               break;

            default:
               PrintError("Switch case not foreseen!");
               break;
         }

         return;
      }
#ifdef E2E_VIRTUAL
      void THR_TASI_From_Nodes             (sched_state_type      *sched_state, 
                                            const Configuration *Config);

#endif // E2E_VIRTUAL


      void THR_TASI_From_Control           (sched_state_type    *sched_state,
                                            const double        *Command, 
                                            const double        *CommandTimeTag, 
                                            const double        *CommandDurationTime);

      void THR_TASI_To_Scheduler           (sched_state_type         *sched_state,
                                            double                   *ForceTH,
                                            double                   *TotForce,
                                            double                   *TotTorque);

      void THR_TASI_To_Scheduler(sched_state_type *sched_state,
                                 buffer_thruster_type *Output);

      void THR_TASI_WriteDebugFile(Initialization_type status,
                                   const CHAR IO_GroupName[]);
};

/* ME2E CVS footer

Full file history:

$Log: THR_TASI.hxx,v $
Revision 1.2  2022/09/01 14:35:20  ludovico.garin
Imported model in new instantiation with some changes

Revision 1.1  2022/03/18 15:11:53  ludovico.garin
Copied from NUMES master on 2022-03-18

Revision 1.2  2021/04/01 08:19:30  ludovico.garin
Upgrade of the model from Pippo THR_TASI with latest numes features

Revision 1.1  2020/11/05 11:45:30  ludovico.garin
First NUMES commit (Situation left by Simona)


*/
