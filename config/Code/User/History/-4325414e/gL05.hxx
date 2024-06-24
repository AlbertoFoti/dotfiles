/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: timing_E2E.hxx,v 1.5 2021/05/03 07:59:04 ludovico.garin Exp $

$Name:  $

$State: Exp $

*/

#ifndef TIMING_E2E_HXX
#define TIMING_E2E_HXX


#ifdef MAIN
#define EXT 
#else
#define EXT extern
#endif

#define DOUBLE double
#define CHAR char
#define INT32 int32_t


typedef struct
{
   DOUBLE    Time,
             StartTime,
             EndTime,
             ItgStep,
             ItgStep0,
             ItgStep1,
             ItgStep2,
             ItgStep3,
             CtrStep,
             SatStep,
             PrintStep,
             PrintStep0,
             PrintStep1,
             PrintStep2,
             PrintStep3,
             PrintStartTime;

   CHAR      IntegType[10];

   INT32     ItgID;
   INT32     ItgID0;
   INT32     ItgID1;
   INT32     ItgID2;
   INT32     ItgID3;

   INT32     SatCtrRatio;
   INT32     CtrItgRatio;
   
   INT32     Cycle;
   INT32     PPS_Flag;

   DOUBLE    ZeroOBTJulianDate2000; 
   DOUBLE    InitJulianDate2000;
   DOUBLE    JulianDate2000;
   DOUBLE    RefMeridianAngle; 
   DOUBLE    MissionTimeRatio;
   DOUBLE    CMDMSepJulianDate2000;
   DOUBLE    CMLauncherSepJulianDate2000;

} timing_type;



EXT timing_type *TimingInfo;
EXT timing_type  TimingVar;


#endif // TIMING_E2E_HXX


/* ME2E CVS footer

Full file history:

$Log: timing_E2E.hxx,v $
Revision 1.5  2021/05/03 07:59:04  ludovico.garin
Distinguish between zero OBT and launch date

Revision 1.4  2019/11/26 11:05:31  simona.desanctis
- Add new variables:
  LaunchJulianDate2000, InitJulianDate2000, JulianDate2000,
  MissionTimeRatio, CMDMSepJulianDate2000

Revision 1.3  2017/01/10 16:01:49  simona.desanctis
- include guard introduced

Revision 1.2  2016/03/08 15:57:54  EXM2018
- Obsolete ItgStepHibbernation deleted

Revision 1.1.1.1  2015/10/19 12:04:42  EXM2018
ME2E Pre-Release


*/
