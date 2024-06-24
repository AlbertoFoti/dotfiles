/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#ifndef GE_NAVIGATION_HXX
#define GE_NAVIGATION_HXX
//#include "E2E_inpout.hxx"
#include "GE_IMUConv01.hxx"
#include "GE_Grav01.hxx"
#include "GE_CoMNav01.hxx"
#include "GE_AttNav02.hxx"

class GE_Navigation_class
{
 private:
   GE_IMUConv01_class GE_IMUConv01;
   GE_Grav01_class GE_Grav01;
   GE_CoMNav01_class GE_CoMNav01;
   GE_AttNav02_class GE_AttNav02;

   struct NAV_type
   {

      double xAttNav_prev[6];
      double xCoMNav_prev[6];

      double angder[5];
      double xAtt[3];
      double xAtt_prev[3];

      double P_xAttNav0[6];
      double P_xCoMNav0[6];

      double O_xComNav[6];
      double O_xAttNav[6];

   } NAV;

 public:
   void GE_NAV_Read(void);

   void GE_NAV_Init(const uint32_t gyr_angle[3], uint32_t gyr_timetag,
                    const uint32_t acc_vel[3], uint32_t acc_timetag);

   void GE_NAV_Exec(const uint32_t gyr_angle[3], uint32_t gyr_timetag,
                    const uint32_t acc_vel[3], uint32_t acc_timetag, bool imu_validity, 
                    double *xCoMNav, double *xAttNav, double *aAngDer, double *gNED);

   void GE_NAV_Exit(void);

   void GE_NAV_WriteDebugFile(E2E_PrintOutput *outfile);
};

#endif // GE_NAVIGATION_HXX
/* ME2E CVS footer

Full file history:

$Log: $


*/

