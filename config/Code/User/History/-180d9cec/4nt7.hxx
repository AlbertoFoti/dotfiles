#pragma once

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
   void GE_Grav_Exec(std::array<double, 6> xCoMNav[6],std::array<double, 3> gNED[3]);

   void GE_Grav_Exit(void);
   //void GE_Grav_WriteDebugFile(E2E_PrintOutput *outfile);
};

