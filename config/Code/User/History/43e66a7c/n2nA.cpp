/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: main.cpp,v 1.3 2022/09/01 14:49:22 ludovico.garin Exp $

$Name:  $

$State: Exp $

*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

extern "C" {
	void adainit(void);
	void adafinal(void);
}

#define MAIN

#include "E2E_define.hxx"
#include "E2E_TypeEquiv.hxx"
#include "E2E_inpout.hxx"

/* E2E buffer include: include all the OBJECT buffers and the E2E buffer */
#include "typedefs_E2E.hxx"
#include "timing_E2E.hxx"
#include "SCHEDULER.hxx"

#include "object_public_typedefs.hxx"
#include "COMMAND.hxx"

//using namespace elibspace;

#include "globals_E2E.hxx"

static INT32  TransitionFlag;     
Command       EdlCommand;        //dichiaro l'oggetto EdlCommand di tipo Command
buffer_dhs_type   DhsPublic;    // dichiaro il buffer di output del DHS, che per il momento non è un oggetto


void  SIMULATION_Init    (void);
void  SIMULATION_Manager (void);

/* 
#define BATCH 
*/
INT32 CycleNum      = 0;
INT32 EndOfSimulation = E2E_FALSE;

#include <fenv.h>
int main (void)
{          
   adainit();
   //feenableexcept(FE_DIVBYZERO | FE_INVALID);
	fedisableexcept(FE_ALL_EXCEPT);

   DOUBLE MainTime;

   INT32 Reset         = 1;
   timing_type  TimingVar;
   TimingInfo = &TimingVar;


   SIMULATION_Init();   // inizializzo SimulationPhase a NONE

   SCHEDULER_FirstInit ();
   SCHEDULER_Init ();

   MainTime  = TimingInfo->StartTime;
   TimingInfo->Time = MainTime;

#ifndef BATCH
   WriteTimeOnScreen (Reset,  "Time: ",   1., TimingInfo->Time);
   Reset = 0;
#endif

   do
   {
      SIMULATION_Manager ();

      if (TransitionFlag)
      {
          TRANSITION_Init (); 
          SCHEDULER_Init ();
      }
      SCHEDULER_Exec ();
  
      CycleNum++;
      MainTime =  MainTime + TimingInfo->SatStep;

      MainTime = MainTime*1000.0;
      MainTime = E2E_INT(MainTime);
      MainTime = MainTime/1000.0;

      TimingInfo->Time = MainTime; 

     
// TimingInfo->Time = TimingInfo->CtrStep * (DOUBLE)CycleNum;  
// TimingInfo->Time = TimingInfo->SatStep * (DOUBLE)CycleNum;

#ifndef BATCH
      WriteTimeOnScreen (Reset,  "Time: ",   1., TimingInfo->Time);
#endif
   }
 
   while (((TimingInfo->EndTime - TimingInfo->Time) >= 1.e-6)&& (EndOfSimulation == E2E_FALSE));
          
   SCHEDULER_Exit ();
   adafinal();
  
   exit(0);
}






void  SIMULATION_Init (void)
{
   CHAR Cmm_IO_FileName[]         = "command";

   INT32    Error = false;
   CHAR     Message[256];

   TIMING_Read   (&Error, Message); if (Error) PrintError (Message);
   SCHED_Read    (&Error, Message); if (Error) PrintError (Message);
   TSV_Read      (&Error, Message); if (Error) PrintError (Message);

   //GlbSimulationPhase  = PHASE_0;
   Glb_LP_Landed  = 0;

   SeparationDisturbance_Read (&Error, Message); if (Error) PrintError (Message);

   printf ("\n GlbSimulationPhase  = %d\n",GlbSimulationPhase);

   TransitionFlag      = false;
   
   EdlCommand.COMMAND_Read(Cmm_IO_FileName, &Error, Message); 
   if (Error) PrintError (Message);

   EdlCommand.COMMAND_Init(); 

   return;
}


void  SIMULATION_Manager (void)
{
/*
    OUTPUT:
    - TransitionFlag 
    - SimulationPhase  (statico)
*/
   //static INT32 HibStatus = 0;

   CHAR   Message[256];
   INT32  TransitionCommand;


   TransitionCommand = 0;

   if(DHS_FlagOpt)
     EdlCommand.COMMAND_From_Dhs(&DhsPublic); 

   EdlCommand.COMMAND_Exec();  

     
   if(EdlCommand.Public.TransitionRequired)
   {
       switch (EdlCommand.Public.NextPhase)
       {

         case PHASE_1:

           if(GlbSimulationPhase == PHASE_0)
           {  
               TransitionCommand = 1;
               GlbSimulationPhase = PHASE_1;
               sprintf (Message, "SIMULATION_Manager: Transition Accepted");
               PrintMessage(Message);
               fprintf(SimLog, "\n Transition to PHASE_1 accepted at time \n %lf\n", TimingInfo->Time);
           }
           else 
           {
               sprintf (Message, "SIMULATION_Manager: Transition Rejected");
               PrintWarning(Message);
           }
           break;
   
         case PHASE_2:

           if(GlbSimulationPhase == PHASE_1)
           {  
               TransitionCommand = 1;
               GlbSimulationPhase = PHASE_2;
               sprintf (Message, "SIMULATION_Manager: Transition Accepted");
               PrintMessage(Message);
               fprintf(SimLog, "\n Transition to PHASE_2 accepted at time \n %lf\n", TimingInfo->Time);
           }
           else 
           {
               sprintf (Message, "SIMULATION_Manager: Transition Rejected");
               PrintWarning(Message);
           }
           break;
   
         case PHASE_3:

           if(GlbSimulationPhase == PHASE_2)
           { 
               TransitionCommand = 1;
               GlbSimulationPhase = PHASE_3;
               sprintf (Message, "SIMULATION_Manager: Transition Accepted");
               PrintMessage(Message);
               fprintf(SimLog, "\n Transition to PHASE_3 accepted at time \n %lf\n", TimingInfo->Time);
           }
           else 
           {
               sprintf (Message, "SIMULATION_Manager: Transition Rejected");
               PrintWarning(Message);
           }
           break;
   
         default:
           sprintf (Message, "SIMULATION_Manager: Transition not allowed");
           PrintWarning(Message);
          
       }
   }

   TransitionFlag = TransitionCommand;
   
   // posso ancora aggiungere sezioni dedicate al paracadute o ad altro

     return; 
}




/* ME2E CVS footer

Full file history:

$Log: main.cpp,v $
Revision 1.3  2022/09/01 14:49:22  ludovico.garin
Modified to support GE

Revision 1.1  2022/03/18 16:15:56  ludovico.garin
Copied from ME2E_03_0_DEVEL ExoMars 2020 on 202-03-18

Revision 1.3  2019/11/21 14:44:04  simona.desanctis
- Added call to adainit() and adafinal() (function defined by Ada that perform
  initialization and finalization of Ada parts).

Revision 1.2  2018/08/23 08:10:24  simona.desanctis
- Initialisation of Glb_LP_Landed added

Revision 1.1.1.1  2015/10/19 12:04:42  EXM2018
ME2E Pre-Release


*/
