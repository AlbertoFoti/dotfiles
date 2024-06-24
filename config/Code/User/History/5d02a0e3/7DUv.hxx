/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: COMMAND.hxx,v 1.3 2022/09/01 14:49:22 ludovico.garin Exp $

$Name:  $

$State: Exp $

*/

typedef enum{
  START, 
  SUP_PAS_OPEN,
  SUP_LID_REL,
  SUP_PAS_REL,
  SUB_PAS_OPEN,
  FS_REL 
} CMD_ID_type;

typedef struct
{
   DOUBLE Time;
   CMD_ID_type  CmdID;
   INT32  ParNum;
   DOUBLE Param[20];   
}CMD_Type;


typedef struct
{
    INT32   CmdNumber;    
    INT32   CmdOption;
    CMD_Type  CMD[1000];
}COMMAND_Type;


typedef struct
{
   
   INT32  I_SupParachuteOpening;
   INT32  I_SupLidRelease;
   INT32  I_SupParachuteRelease;
   INT32  I_SubParachuteOpening;
   INT32  I_FrontShieldSeparation;
   INT32  I_LandingLegsOpening;
   INT32  I_RJseparation;
 
}CMD_From_GNC_type;



class Command
{
   private:
   
       COMMAND_Type       EC;
       CMD_From_GNC_type  CMD_From_GNC;
  
   
       void  TimeTaggedCommand (void);

       void  GncCommand (void);

       
   public:
       
       buffer_command_dm_type  Public;   

       void  COMMAND_Read (CHAR   IO_FileName[],
                            INT32 *Error, CHAR *Message);

       void  COMMAND_Init (void);

       void  COMMAND_Exec ();

       void  COMMAND_From_Dhs (buffer_dhs_type *Input);

};



/* ME2E CVS footer

Full file history:

$Log: COMMAND.hxx,v $
Revision 1.3  2022/09/01 14:49:22  ludovico.garin
Modified to support GE

Revision 1.1  2022/03/18 16:15:56  ludovico.garin
Copied from ME2E_03_0_DEVEL ExoMars 2020 on 202-03-18

Revision 1.3  2018/08/23 07:51:19  simona.desanctis
- SUP_LID_REL  added in the TimeTagged command list

Revision 1.2  2017/10/26 08:04:07  simona.desanctis
- INT32  I_SupLidRelease added in CMD_From_GNC_type

Revision 1.1.1.1  2015/10/19 12:04:42  EXM2018
ME2E Pre-Release


*/
