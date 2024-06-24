/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#ifndef GE_Grav01_HXX
#define GE_Grav01_HXX

class GE_Grav01_class
{
 private:
   struct Grav_type
   {
    double P_MU;	
    double P_J2;
    double P_J3;
    double P_J4;
    double P_REQ;
    
    int P_GRAVID;

    double O_gNED[3];	

   } Grav;

 public:
   void GE_Grav_Init();
   void GE_Grav_Exec(const double xCoMNav[6],double gNED[3]);

   void GE_Grav_Exit(void);
   //void GE_Grav_WriteDebugFile(E2E_PrintOutput *outfile);
};

#endif // GE_Grav01_HXX
/* ME2E CVS footer

Full file history:

$Log: $


*/

